Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

Add-Type -AssemblyName System.IO.Compression.FileSystem

function Remove-Diacritics {
    param([string]$Text)

    if (-not $Text) {
        return ''
    }

    $normalized = $Text.Normalize([Text.NormalizationForm]::FormD)
    $builder = [System.Text.StringBuilder]::new()
    foreach ($char in $normalized.ToCharArray()) {
        $category = [Globalization.CharUnicodeInfo]::GetUnicodeCategory($char)
        if ($category -ne [Globalization.UnicodeCategory]::NonSpacingMark) {
            [void]$builder.Append($char)
        }
    }

    $result = $builder.ToString().Normalize([Text.NormalizationForm]::FormC)
    $result = $result.Replace([string][char]273, 'd')
    $result = $result.Replace([string][char]272, 'D')
    return $result
}

function Get-ZipXml {
    param(
        [string]$DocxPath,
        [string]$EntryName
    )

    $zip = [System.IO.Compression.ZipFile]::OpenRead((Resolve-Path -LiteralPath $DocxPath))
    try {
        $entry = $zip.GetEntry($EntryName)
        if (-not $entry) {
            throw "$EntryName not found in $DocxPath"
        }

        $reader = [System.IO.StreamReader]::new($entry.Open())
        try {
            return [xml]$reader.ReadToEnd()
        } finally {
            $reader.Dispose()
        }
    } finally {
        $zip.Dispose()
    }
}

function Set-ZipStringEntry {
    param(
        [string]$DocxPath,
        [string]$EntryName,
        [string]$Content
    )

    $fileStream = [System.IO.File]::Open((Resolve-Path -LiteralPath $DocxPath), [System.IO.FileMode]::Open, [System.IO.FileAccess]::ReadWrite)
    try {
        $zip = [System.IO.Compression.ZipArchive]::new($fileStream, [System.IO.Compression.ZipArchiveMode]::Update)
        try {
            $existing = $zip.GetEntry($EntryName)
            if ($existing) {
                $existing.Delete()
            }

            $entry = $zip.CreateEntry($EntryName)
            $writer = [System.IO.StreamWriter]::new($entry.Open(), [System.Text.UTF8Encoding]::new($false))
            try {
                $writer.Write($Content)
            } finally {
                $writer.Dispose()
            }
        } finally {
            $zip.Dispose()
        }
    } finally {
        $fileStream.Dispose()
    }
}

function Save-XmlDocument {
    param([xml]$XmlDocument)

    $settings = [System.Xml.XmlWriterSettings]::new()
    $settings.Encoding = [System.Text.UTF8Encoding]::new($false)
    $settings.Indent = $false
    $settings.OmitXmlDeclaration = $false

    $stringWriter = [System.IO.StringWriter]::new()
    $xmlWriter = [System.Xml.XmlWriter]::Create($stringWriter, $settings)
    try {
        $XmlDocument.WriteTo($xmlWriter)
        $xmlWriter.Flush()
        return $stringWriter.ToString()
    } finally {
        $xmlWriter.Dispose()
        $stringWriter.Dispose()
    }
}

function Get-ParagraphText {
    param([System.Xml.XmlNode]$Paragraph)

    $parts = foreach ($node in $Paragraph.SelectNodes('.//*[local-name()="t"]')) {
        $node.InnerText
    }

    return ($parts -join '')
}

function Get-NextNonEmptyParagraphText {
    param(
        [object[]]$Paragraphs,
        [int]$StartIndex
    )

    for ($i = $StartIndex + 1; $i -lt $Paragraphs.Count; $i++) {
        $text = (Get-ParagraphText $Paragraphs[$i]).Trim()
        if ($text) {
            return $text
        }
    }

    return ''
}

function Is-OptionLine {
    param([string]$Text)

    return $Text.Trim() -match '^[A-Da-d]\s*[:\.\)]'
}

function Is-NoteLine {
    param([string]$Text)

    $normalized = (Remove-Diacritics $Text).ToLowerInvariant().Trim()
    return $normalized -match '^(chuong 4:|-?\s*ghi chu:|ghi chu:|answer:|chon dap an chinh xac nhat:?$)'
}

function Is-ExplicitQuestionStart {
    param([string]$Text)

    $normalized = (Remove-Diacritics $Text).Trim().ToLowerInvariant()
    return $normalized -match '^(cau(\s*[0-9,]+)?|\d{1,3})\s*[:\.\-\)]'
}

function Is-ImplicitQuestionStart {
    param(
        [string]$Text,
        [string]$NextText
    )

    $trimmed = $Text.Trim()
    if (-not $trimmed) {
        return $false
    }

    if (Is-NoteLine $trimmed) {
        return $false
    }

    if (Is-OptionLine $trimmed) {
        return $false
    }

    return (Is-OptionLine $NextText)
}

function Get-QuestionBlocks {
    param([xml]$DocXml)

    $paragraphs = @($DocXml.DocumentElement.SelectNodes('//*[local-name()="body"]/*[local-name()="p"]'))
    $starts = [System.Collections.Generic.List[int]]::new()

    for ($i = 0; $i -lt $paragraphs.Count; $i++) {
        $text = (Get-ParagraphText $paragraphs[$i]).Trim()
        if (-not $text) {
            continue
        }

        $nextText = Get-NextNonEmptyParagraphText -Paragraphs $paragraphs -StartIndex $i
        if ((Is-ExplicitQuestionStart $text) -or (Is-ImplicitQuestionStart -Text $text -NextText $nextText)) {
            $starts.Add($i)
        }
    }

    $blocks = [System.Collections.Generic.List[object]]::new()
    for ($i = 0; $i -lt $starts.Count; $i++) {
        $startIndex = $starts[$i]
        $endIndex = if ($i -lt $starts.Count - 1) { $starts[$i + 1] - 1 } else { $paragraphs.Count - 1 }

        $paragraphClones = [System.Collections.Generic.List[System.Xml.XmlNode]]::new()
        for ($j = $startIndex; $j -le $endIndex; $j++) {
            [void]$paragraphClones.Add($paragraphs[$j].CloneNode($true))
        }

        $blocks.Add([pscustomobject]@{
            Index           = $blocks.Count + 1
            StartParagraph  = $startIndex
            EndParagraph    = $endIndex
            FirstLine       = (Get-ParagraphText $paragraphs[$startIndex]).Trim()
            ParagraphClones = $paragraphClones
        }) | Out-Null
    }

    return $blocks
}

function Remove-QuestionPrefix {
    param(
        [System.Xml.XmlNode]$Paragraph,
        [string]$FullText
    )

    $match = [regex]::Match($FullText, '^(C\S*u(\s*[0-9,]+)?|\d{1,3})\s*[:\.\-\)]\s*', [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)
    if (-not $match.Success) {
        return
    }

    $remaining = $match.Length
    foreach ($textNode in $Paragraph.SelectNodes('.//*[local-name()="t"]')) {
        if ($remaining -le 0) {
            break
        }

        $current = $textNode.InnerText
        if (-not $current) {
            continue
        }

        if ($current.Length -le $remaining) {
            $textNode.InnerText = ''
            $remaining -= $current.Length
        } else {
            $textNode.InnerText = $current.Substring($remaining)
            $remaining = 0
        }
    }
}

function Prepend-QuestionPrefix {
    param(
        [xml]$DocXml,
        [System.Xml.XmlNode]$Paragraph,
        [string]$Prefix
    )

    $namespaceUri = $DocXml.DocumentElement.NamespaceURI
    $xmlNamespace = 'http://www.w3.org/XML/1998/namespace'

    $run = $DocXml.CreateElement('w', 'r', $namespaceUri)
    $text = $DocXml.CreateElement('w', 't', $namespaceUri)
    [void]$text.SetAttribute('space', $xmlNamespace, 'preserve')
    $text.InnerText = $Prefix
    [void]$run.AppendChild($text)

    $paragraphProperties = $Paragraph.SelectSingleNode('./*[local-name()="pPr"]')
    if ($paragraphProperties) {
        [void]$Paragraph.InsertAfter($run, $paragraphProperties)
    } else {
        [void]$Paragraph.PrependChild($run)
    }
}

function Renumber-Block {
    param(
        [xml]$DocXml,
        [object]$Block,
        [int]$NewNumber
    )

    $firstParagraph = $Block.ParagraphClones[0]
    $firstText = Get-ParagraphText $firstParagraph
    Remove-QuestionPrefix -Paragraph $firstParagraph -FullText $firstText
    $questionLabel = 'C' + [char]0x00E2 + 'u'
    Prepend-QuestionPrefix -DocXml $DocXml -Paragraph $firstParagraph -Prefix ("{0} {1}: " -f $questionLabel, $NewNumber)
}

$docxPath = 'TNChuong4.docx'
$backupPath = 'TNChuong4.backup-before-reorder.docx'

if (-not (Test-Path -LiteralPath $backupPath)) {
    Copy-Item -LiteralPath $docxPath -Destination $backupPath
}

$docXml = Get-ZipXml -DocxPath $docxPath -EntryName 'word/document.xml'
$blocks = Get-QuestionBlocks -DocXml $docXml

$desiredOrder = @(
    1, 2, 3, 4, 5,
    6, 7, 8, 9,
    10, 11, 12, 13, 14,
    15, 16, 17, 18,
    19, 20, 22,
    23, 24, 25, 26, 27,
    28, 29, 30, 31, 32, 33, 34, 35, 36,
    51,
    37, 38, 39, 40,
    45, 41, 43, 42, 44, 46, 47,
    48,
    21, 49, 50
)

if ($blocks.Count -ne $desiredOrder.Count) {
    throw "Expected $($desiredOrder.Count) question blocks but found $($blocks.Count)."
}

$sortedOrder = @($desiredOrder | Sort-Object)
for ($i = 0; $i -lt $sortedOrder.Count; $i++) {
    if ($sortedOrder[$i] -ne ($i + 1)) {
        throw 'Desired order does not contain a complete 1..N permutation.'
    }
}

$body = $docXml.DocumentElement.SelectSingleNode('//*[local-name()="body"]')
$paragraphs = @($body.SelectNodes('./*[local-name()="p"]'))
$firstQuestionIndex = $blocks[0].StartParagraph
$lastQuestionIndex = $blocks[-1].EndParagraph

$insertAfter = $paragraphs[$firstQuestionIndex - 1]
if (-not $insertAfter) {
    throw 'Could not find insertion anchor before the first question.'
}

for ($i = $lastQuestionIndex; $i -ge $firstQuestionIndex; $i--) {
    [void]$body.RemoveChild($paragraphs[$i])
}

for ($i = 0; $i -lt $desiredOrder.Count; $i++) {
    $block = $blocks[$desiredOrder[$i] - 1]
    Renumber-Block -DocXml $docXml -Block $block -NewNumber ($i + 1)

    foreach ($paragraphClone in $block.ParagraphClones) {
        $imported = $docXml.ImportNode($paragraphClone, $true)
        $insertAfter = $body.InsertAfter($imported, $insertAfter)
    }
}

Set-ZipStringEntry -DocxPath $docxPath -EntryName 'word/document.xml' -Content (Save-XmlDocument -XmlDocument $docXml)

Write-Output ("Reordered and renumbered {0} question blocks in {1}." -f $blocks.Count, $docxPath)
Write-Output ("Backup: {0}" -f $backupPath)
