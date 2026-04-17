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
    param($Paragraph)

    if ($null -eq $Paragraph) {
        return ''
    }

    if ($Paragraph -isnot [System.Xml.XmlNode] -and $Paragraph.PSObject.Properties['Node']) {
        $Paragraph = $Paragraph.Node
    }

    if ($Paragraph -isnot [System.Xml.XmlNode]) {
        return ''
    }

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
    return $normalized -match '^(chuong 8:|chon dap an chinh xac nhat:?$|trinh bay nguyen nhan su co va cach khac phuc\?)'
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

    $body = $DocXml.DocumentElement.SelectSingleNode('//*[local-name()="body"]')
    $bodyChildren = @(
        $body.ChildNodes |
            Where-Object { $_.NodeType -eq [System.Xml.XmlNodeType]::Element }
    )

    $paragraphs = [System.Collections.Generic.List[object]]::new()
    for ($i = 0; $i -lt $bodyChildren.Count; $i++) {
        $node = $bodyChildren[$i]
        if ($node.LocalName -eq 'p') {
            [void]$paragraphs.Add([pscustomobject]@{
                BodyIndex = $i
                Node      = $node
            })
        }
    }

    $starts = [System.Collections.Generic.List[int]]::new()

    for ($i = 0; $i -lt $paragraphs.Count; $i++) {
        $text = (Get-ParagraphText $paragraphs[$i].Node).Trim()
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
        $startParagraphIndex = $starts[$i]
        $startBodyIndex = $paragraphs[$startParagraphIndex].BodyIndex
        $endBodyIndex = if ($i -lt $starts.Count - 1) {
            $paragraphs[$starts[$i + 1]].BodyIndex - 1
        } else {
            if ($bodyChildren[-1].LocalName -eq 'sectPr') {
                $bodyChildren.Count - 2
            } else {
                $bodyChildren.Count - 1
            }
        }

        $nodeClones = [System.Collections.Generic.List[System.Xml.XmlNode]]::new()
        for ($j = $startBodyIndex; $j -le $endBodyIndex; $j++) {
            [void]$nodeClones.Add($bodyChildren[$j].CloneNode($true))
        }

        $blocks.Add([pscustomobject]@{
            Index              = $blocks.Count + 1
            StartBodyIndex     = $startBodyIndex
            EndBodyIndex       = $endBodyIndex
            FirstLine          = (Get-ParagraphText $paragraphs[$startParagraphIndex].Node).Trim()
            FirstParagraphNode = $nodeClones | Where-Object { $_.LocalName -eq 'p' } | Select-Object -First 1
            NodeClones         = $nodeClones
        })
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

    $firstParagraph = $Block.FirstParagraphNode
    $firstText = Get-ParagraphText $firstParagraph
    Remove-QuestionPrefix -Paragraph $firstParagraph -FullText $firstText
    $questionLabel = 'C' + [char]0x00E2 + 'u'
    Prepend-QuestionPrefix -DocXml $DocXml -Paragraph $firstParagraph -Prefix ("{0} {1}: " -f $questionLabel, $NewNumber)
}

$docxPath = 'TNChuong8.docx'
$backupPath = 'TNChuong8.backup-before-reorder.docx'

if (-not (Test-Path -LiteralPath $backupPath)) {
    Copy-Item -LiteralPath $docxPath -Destination $backupPath
}

$docXml = Get-ZipXml -DocxPath $docxPath -EntryName 'word/document.xml'
$blocks = Get-QuestionBlocks -DocXml $docXml

$desiredOrder = @(
    51, 5, 9, 7, 10,
    4, 25, 29, 22, 19, 18, 31, 50, 14, 1, 3, 33, 2, 8, 28, 27, 45, 26, 12,
    11, 15, 30, 38, 20, 16, 21, 48, 36, 52, 17, 39, 32, 44, 37, 46,
    43, 42, 23, 34, 24, 49, 40, 47, 53,
    35, 41, 13, 6
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
$bodyChildren = @(
    $body.ChildNodes |
        Where-Object { $_.NodeType -eq [System.Xml.XmlNodeType]::Element }
)
$firstQuestionIndex = $blocks[0].StartBodyIndex
$lastQuestionIndex = $blocks[-1].EndBodyIndex

$insertAfter = if ($firstQuestionIndex -gt 0) { $bodyChildren[$firstQuestionIndex - 1] } else { $null }

for ($i = $lastQuestionIndex; $i -ge $firstQuestionIndex; $i--) {
    [void]$body.RemoveChild($bodyChildren[$i])
}

for ($i = 0; $i -lt $desiredOrder.Count; $i++) {
    $block = $blocks[$desiredOrder[$i] - 1]
    Renumber-Block -DocXml $docXml -Block $block -NewNumber ($i + 1)

    foreach ($nodeClone in $block.NodeClones) {
        $imported = $docXml.ImportNode($nodeClone, $true)
        if ($insertAfter) {
            $insertAfter = $body.InsertAfter($imported, $insertAfter)
        } else {
            $firstChild = $body.FirstChild
            if ($firstChild) {
                [void]$body.InsertBefore($imported, $firstChild)
            } else {
                [void]$body.AppendChild($imported)
            }
            $insertAfter = $imported
        }
    }
}

Set-ZipStringEntry -DocxPath $docxPath -EntryName 'word/document.xml' -Content (Save-XmlDocument -XmlDocument $docXml)

Write-Output ("Reordered and renumbered {0} question blocks in {1}." -f $blocks.Count, $docxPath)
Write-Output ("Backup: {0}" -f $backupPath)
