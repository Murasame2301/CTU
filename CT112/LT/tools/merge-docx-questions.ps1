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

function Normalize-Text {
    param([string]$Text)

    if (-not $Text) {
        return ''
    }

    $text = Remove-Diacritics($Text).ToLowerInvariant()
    $text = [regex]::Replace($text, '^cau\s*\d+\s*[:\.\-\)]?\s*', '')
    $text = [regex]::Replace($text, '^\d+\s*[:\.\-\)]\s*', '')
    $text = [regex]::Replace($text, '^[a-d]\s*[:\.\)]\s*', '')
    $text = [regex]::Replace($text, '\s+', ' ')
    $text = [regex]::Replace($text, '[^\p{L}\p{N}\s]', ' ')
    $text = [regex]::Replace($text, '\s+', ' ').Trim()
    return $text
}

function Get-Tokens {
    param([string]$Text)

    $normalized = Normalize-Text $Text
    if (-not $normalized) {
        return @()
    }

    return @(
        $normalized -split '\s+' |
            Where-Object { $_.Length -gt 1 } |
            Sort-Object -Unique
    )
}

function Get-QuestionScore {
    param(
        [string[]]$LeftTokens,
        [string[]]$RightTokens
    )

    $LeftTokens = @($LeftTokens | Where-Object { $_ })
    $RightTokens = @($RightTokens | Where-Object { $_ })

    if ( (($LeftTokens | Measure-Object).Count -eq 0) -or (($RightTokens | Measure-Object).Count -eq 0) ) {
        return 0.0
    }

    $leftMap = @{}
    foreach ($token in $LeftTokens) {
        $leftMap[$token] = $true
    }

    $rightMap = @{}
    foreach ($token in $RightTokens) {
        $rightMap[$token] = $true
    }

    $intersection = 0
    $union = @{}
    foreach ($token in $leftMap.Keys) {
        $union[$token] = $true
        if ($rightMap.ContainsKey($token)) {
            $intersection++
        }
    }
    foreach ($token in $rightMap.Keys) {
        $union[$token] = $true
    }

    if ($union.Count -eq 0) {
        return 0.0
    }

    return [Math]::Round($intersection / $union.Count, 4)
}

function Find-DocxByNormalizedName {
    param([string]$ExpectedName)

    $expected = (Remove-Diacritics $ExpectedName).ToLowerInvariant()
    $matches = @(
        Get-ChildItem -LiteralPath . -File -Filter *.docx |
            Where-Object {
                (Remove-Diacritics $_.Name).ToLowerInvariant() -eq $expected
            }
    )

    if ($matches.Count -ne 1) {
        throw "Could not uniquely resolve DOCX file for: $ExpectedName"
    }

    return $matches[0].FullName
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

function Get-ZipEntryText {
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
            return $reader.ReadToEnd()
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

function Copy-ZipEntry {
    param(
        [string]$SourceDocxPath,
        [string]$SourceEntryName,
        [string]$TargetDocxPath,
        [string]$TargetEntryName
    )

    $sourceZip = [System.IO.Compression.ZipFile]::OpenRead((Resolve-Path -LiteralPath $SourceDocxPath))
    try {
        $sourceEntry = $sourceZip.GetEntry($SourceEntryName)
        if (-not $sourceEntry) {
            throw "$SourceEntryName not found in $SourceDocxPath"
        }

        $targetStream = [System.IO.File]::Open((Resolve-Path -LiteralPath $TargetDocxPath), [System.IO.FileMode]::Open, [System.IO.FileAccess]::ReadWrite)
        try {
            $targetZip = [System.IO.Compression.ZipArchive]::new($targetStream, [System.IO.Compression.ZipArchiveMode]::Update)
            try {
                $existingTarget = $targetZip.GetEntry($TargetEntryName)
                if ($existingTarget) {
                    $existingTarget.Delete()
                }

                $targetEntry = $targetZip.CreateEntry($TargetEntryName)
                $input = $sourceEntry.Open()
                $output = $targetEntry.Open()
                try {
                    $input.CopyTo($output)
                } finally {
                    $output.Dispose()
                    $input.Dispose()
                }
            } finally {
                $targetZip.Dispose()
            }
        } finally {
            $targetStream.Dispose()
        }
    } finally {
        $sourceZip.Dispose()
    }
}

function Get-ParagraphText {
    param([System.Xml.XmlNode]$Paragraph)

    $parts = foreach ($node in $Paragraph.SelectNodes('.//*[local-name()="t"]')) {
        $node.InnerText
    }
    return ($parts -join '')
}

function Get-ParagraphStyleId {
    param([System.Xml.XmlNode]$Paragraph)

    $styleNode = $Paragraph.SelectSingleNode('./*[local-name()="pPr"]/*[local-name()="pStyle"]')
    if (-not $styleNode) {
        return ''
    }

    foreach ($attribute in $styleNode.Attributes) {
        if ($attribute.LocalName -eq 'val') {
            return $attribute.Value
        }
    }

    return ''
}

function Is-QuestionStart {
    param([string]$Text)

    $normalized = Remove-Diacritics($Text).ToLowerInvariant().Trim()
    return $normalized -match '^(cau(\s*\d+)?|\d{1,2})\s*[:\.\-\)]'
}

function Is-OptionLine {
    param([string]$Text)

    $normalized = Remove-Diacritics($Text).ToLowerInvariant().Trim()
    return $normalized -match '^[a-d]\s*[:\.\)]'
}

function Get-ManualSourceChapterMap {
    return @{
        1 = 5; 2 = 5; 3 = 8; 4 = 7; 5 = 7; 6 = 7; 7 = 8; 8 = 8; 9 = 5; 10 = 8;
        11 = 6; 12 = 7; 13 = 7; 14 = 8; 15 = 7; 16 = 6; 17 = 7; 18 = 7; 19 = 7; 20 = 7;
        21 = 8; 22 = 8; 23 = 7; 24 = 1; 25 = 7; 26 = 7; 27 = 6; 28 = 8; 29 = 8; 30 = 8;
        31 = 7; 32 = 8; 33 = 7; 34 = 8; 35 = 6; 36 = 5; 37 = 1; 38 = 1; 39 = 5; 40 = 7;
        41 = 7; 42 = 7; 43 = 6; 44 = 7;
        45 = 3; 46 = 6; 47 = 2; 48 = 6; 49 = 5; 50 = 6; 51 = 5; 52 = 4; 53 = 6; 54 = 6;
        55 = 6; 56 = 6; 57 = 1; 58 = 4; 59 = 1; 60 = 4; 61 = 6; 62 = 6; 63 = 6; 64 = 1;
        65 = 6; 66 = 4; 67 = 6; 68 = 6; 69 = 6; 70 = 6; 71 = 6; 72 = 8; 73 = 6; 74 = 6;
        75 = 6; 76 = 6; 77 = 6; 78 = 6; 79 = 6; 80 = 6; 81 = 6; 82 = 6; 83 = 6; 84 = 6;
        85 = 6; 86 = 1; 87 = 6; 88 = 6; 89 = 6; 90 = 5; 91 = 6; 92 = 6
    }
}

function Get-ManualStemMap {
    return @{
        17 = 'tcp data transmission identify k and z'
        40 = 'tcp data transmission identify x and y'
        58 = 'hdlc i frame identify x and y'
    }
}

function Get-QuestionBlocks {
    param(
        [xml]$DocXml,
        [switch]$TrackChapters,
        [hashtable]$ManualChapterMap = @{},
        [hashtable]$ManualStemMap = @{}
    )

    $paragraphs = @($DocXml.DocumentElement.SelectNodes('//*[local-name()="body"]/*[local-name()="p"]'))
    $blocks = [System.Collections.Generic.List[object]]::new()
    $chapterIndex = 0
    $questionIndex = 0

    $i = 0
    while ($i -lt $paragraphs.Count) {
        $paragraph = $paragraphs[$i]
        $styleId = Get-ParagraphStyleId $paragraph
        $text = (Get-ParagraphText $paragraph).Trim()

        if ($TrackChapters -and $styleId -eq 'Heading1') {
            $chapterIndex++
            $i++
            continue
        }

        if (-not (Is-QuestionStart $text)) {
            $i++
            continue
        }

        $questionIndex++
        $startIndex = $i
        $outerXmlList = [System.Collections.Generic.List[string]]::new()
        $textList = [System.Collections.Generic.List[string]]::new()
        $hasDrawing = $false
        $embedIds = [System.Collections.Generic.List[string]]::new()

        while ($i -lt $paragraphs.Count) {
            $candidate = $paragraphs[$i]
            $candidateStyle = Get-ParagraphStyleId $candidate
            $candidateText = (Get-ParagraphText $candidate).Trim()

            if ($i -gt $startIndex) {
                if ($TrackChapters -and $candidateStyle -eq 'Heading1') {
                    break
                }
                if (Is-QuestionStart $candidateText) {
                    break
                }
            }

            $outerXml = $candidate.OuterXml
            $outerXmlList.Add($outerXml)
            if ($outerXml -match '(drawing|pict)') {
                $hasDrawing = $true
            }

            foreach ($match in [regex]::Matches($outerXml, 'r:embed="([^"]+)"')) {
                $embedId = $match.Groups[1].Value
                if (-not $embedIds.Contains($embedId)) {
                    $embedIds.Add($embedId)
                }
            }

            if ($candidateText) {
                $textList.Add($candidateText)
            }

            $i++
        }

        $stemParts = [System.Collections.Generic.List[string]]::new()
        foreach ($line in $textList) {
            if (Is-OptionLine $line) {
                break
            }
            $stemParts.Add($line)
        }

        $rawStem = ($stemParts -join ' ')
        $syntheticStem = ''
        if ($ManualStemMap.ContainsKey($questionIndex)) {
            $syntheticStem = $ManualStemMap[$questionIndex]
        }

        $effectiveStem = if ($syntheticStem) { $syntheticStem } elseif ($rawStem) { $rawStem } else { ($textList -join ' ') }
        $normalizedStem = Normalize-Text $effectiveStem

        $chapterValue = if ($ManualChapterMap.ContainsKey($questionIndex)) { $ManualChapterMap[$questionIndex] } else { $chapterIndex }

        $blocks.Add([pscustomobject]@{
            SourceIndex     = $questionIndex
            ChapterIndex    = $chapterValue
            StartIndex      = $startIndex
            OuterXmlList    = $outerXmlList
            TextList        = $textList
            RawStem         = $rawStem
            EffectiveStem   = $effectiveStem
            NormalizedStem  = $normalizedStem
            Tokens          = Get-Tokens $effectiveStem
            HasDrawing      = $hasDrawing
            EmbedIds        = @($embedIds)
        })
    }

    return $blocks
}

function Get-ChapterBoundaries {
    param([xml]$DocXml)

    $paragraphs = @($DocXml.DocumentElement.SelectNodes('//*[local-name()="body"]/*[local-name()="p"]'))
    $boundaries = [System.Collections.Generic.List[object]]::new()

    for ($i = 0; $i -lt $paragraphs.Count; $i++) {
        if ((Get-ParagraphStyleId $paragraphs[$i]) -eq 'Heading1') {
            $boundaries.Add([pscustomobject]@{
                ChapterIndex = $boundaries.Count + 1
                HeadingIndex = $i
                EndIndex     = $null
            })
        }
    }

    for ($i = 0; $i -lt $boundaries.Count; $i++) {
        if ($i -lt $boundaries.Count - 1) {
            $boundaries[$i].EndIndex = $boundaries[$i + 1].HeadingIndex - 1
        } else {
            $boundaries[$i].EndIndex = $paragraphs.Count - 1
        }
    }

    return $boundaries
}

function Get-NextRelationId {
    param([xml]$RelationshipsXml)

    $max = 0
    foreach ($node in $RelationshipsXml.DocumentElement.ChildNodes) {
        if ($node.LocalName -ne 'Relationship') {
            continue
        }
        $idValue = $node.GetAttribute('Id')
        if ($idValue -match '^rId(\d+)$') {
            $number = [int]$Matches[1]
            if ($number -gt $max) {
                $max = $number
            }
        }
    }

    return "rId$($max + 1)"
}

function Get-RelationshipMap {
    param([xml]$RelationshipsXml)

    $map = @{}
    foreach ($node in $RelationshipsXml.DocumentElement.ChildNodes) {
        if ($node.LocalName -ne 'Relationship') {
            continue
        }
        $map[$node.GetAttribute('Id')] = [pscustomobject]@{
            Type   = $node.GetAttribute('Type')
            Target = $node.GetAttribute('Target')
        }
    }

    return $map
}

function Get-UniqueMediaName {
    param(
        [string]$ExistingNamesJoined,
        [string]$PreferredBaseName
    )

    $candidate = $PreferredBaseName
    $counter = 1
    while ($ExistingNamesJoined.Contains("|$candidate|")) {
        $extension = [System.IO.Path]::GetExtension($PreferredBaseName)
        $stem = [System.IO.Path]::GetFileNameWithoutExtension($PreferredBaseName)
        $candidate = '{0}-{1}{2}' -f $stem, $counter, $extension
        $counter++
    }
    return $candidate
}

function Ensure-ContentTypeDefault {
    param(
        [xml]$ContentTypesXml,
        [string]$Extension,
        [string]$ContentType
    )

    foreach ($node in $ContentTypesXml.DocumentElement.ChildNodes) {
        if ($node.LocalName -eq 'Default' -and $node.GetAttribute('Extension') -eq $Extension) {
            return
        }
    }

    $newNode = $ContentTypesXml.CreateElement('Default', $ContentTypesXml.DocumentElement.NamespaceURI)
    [void]$newNode.SetAttribute('Extension', $Extension)
    [void]$newNode.SetAttribute('ContentType', $ContentType)
    [void]$ContentTypesXml.DocumentElement.AppendChild($newNode)
}

function Replace-EmbedIds {
    param(
        [string]$OuterXml,
        [hashtable]$EmbedMap
    )

    $updated = $OuterXml
    foreach ($oldId in $EmbedMap.Keys) {
        $updated = $updated.Replace('r:embed="{0}"' -f $oldId, 'r:embed="{0}"' -f $EmbedMap[$oldId])
    }
    return $updated
}

function Find-AnchorStartIndex {
    param(
        $Block,
        [object[]]$TargetBlocks,
        $ChapterBoundary
    )

    $chapterBlocks = @($TargetBlocks | Where-Object { $_.ChapterIndex -eq $Block.ChapterIndex })
    if (-not $chapterBlocks.Count) {
        return $ChapterBoundary.HeadingIndex
    }

    $bestBlock = $null
    $bestScore = -1.0
    foreach ($targetBlock in $chapterBlocks) {
        $score = Get-QuestionScore -LeftTokens $Block.Tokens -RightTokens $targetBlock.Tokens
        if ($score -gt $bestScore) {
            $bestScore = $score
            $bestBlock = $targetBlock
        }
    }

    if ($bestBlock -and $bestScore -ge 0.12) {
        return $bestBlock.StartIndex
    }

    return $chapterBlocks[-1].StartIndex
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

$targetPath = Find-DocxByNormalizedName 'TN theo chuong.docx'
$sourcePath = Find-DocxByNormalizedName 'Dap an thi thu MMT_Pass_LVThuong.docx'
$backupPath = Join-Path -Path (Split-Path -Parent $targetPath) -ChildPath 'TN-theo-chuong.backup-before-merge.docx'

if (-not (Test-Path -LiteralPath $backupPath)) {
    Copy-Item -LiteralPath $targetPath -Destination $backupPath
}

$manualChapterMap = Get-ManualSourceChapterMap
$manualStemMap = Get-ManualStemMap

$targetDocXml = Get-ZipXml -DocxPath $targetPath -EntryName 'word/document.xml'
$sourceDocXml = Get-ZipXml -DocxPath $sourcePath -EntryName 'word/document.xml'
$targetRelsXml = Get-ZipXml -DocxPath $targetPath -EntryName 'word/_rels/document.xml.rels'
$sourceRelsXml = Get-ZipXml -DocxPath $sourcePath -EntryName 'word/_rels/document.xml.rels'
$contentTypesXml = Get-ZipXml -DocxPath $targetPath -EntryName '[Content_Types].xml'

$targetBlocks = Get-QuestionBlocks -DocXml $targetDocXml -TrackChapters
$sourceBlocks = Get-QuestionBlocks -DocXml $sourceDocXml -ManualChapterMap $manualChapterMap -ManualStemMap $manualStemMap
$chapterBoundaries = Get-ChapterBoundaries -DocXml $targetDocXml

$targetJoinedNormalized = (
    @($targetBlocks | ForEach-Object { $_.NormalizedStem } | Where-Object { $_ }) -join ' | '
)

$seenSourceKeys = @{}
$missingBlocks = [System.Collections.Generic.List[object]]::new()
foreach ($block in $sourceBlocks) {
    $key = if ($block.NormalizedStem) {
        $block.NormalizedStem
    } elseif ($block.HasDrawing) {
        'drawing:' + (($block.EmbedIds | Sort-Object) -join ',') + ':' + $block.SourceIndex
    } else {
        'block:' + $block.SourceIndex
    }

    if ($seenSourceKeys.ContainsKey($key)) {
        continue
    }
    $seenSourceKeys[$key] = $true

    if ($block.NormalizedStem -and $targetJoinedNormalized.Contains($block.NormalizedStem)) {
        continue
    }

    $missingBlocks.Add($block)
}

if (-not $missingBlocks.Count) {
    Write-Output 'No missing question blocks detected.'
    exit 0
}

$sourceRelMap = Get-RelationshipMap -RelationshipsXml $sourceRelsXml
$targetRelMap = Get-RelationshipMap -RelationshipsXml $targetRelsXml
$existingMediaNames = '|'
foreach ($rel in $targetRelMap.Values) {
    if ($rel.Type -like '*/image') {
        $existingMediaNames += ([System.IO.Path]::GetFileName($rel.Target)) + '|'
    }
}

$neededEmbedIds = @{}
foreach ($block in $missingBlocks) {
    foreach ($embedId in $block.EmbedIds) {
        $neededEmbedIds[$embedId] = $true
    }
}

$embedReplacementMap = @{}
$imageRelationshipType = 'http://schemas.openxmlformats.org/officeDocument/2006/relationships/image'
foreach ($oldEmbedId in ($neededEmbedIds.Keys | Sort-Object)) {
    if (-not $sourceRelMap.ContainsKey($oldEmbedId)) {
        continue
    }

    $sourceTarget = $sourceRelMap[$oldEmbedId].Target
    $sourceEntryName = 'word/' + $sourceTarget.Replace('\', '/')
    $extension = [System.IO.Path]::GetExtension($sourceTarget)
    $preferredName = 'merged-source-{0}{1}' -f $oldEmbedId.ToLowerInvariant(), $extension
    $targetMediaName = Get-UniqueMediaName -ExistingNamesJoined $existingMediaNames -PreferredBaseName $preferredName
    $existingMediaNames += $targetMediaName + '|'

    $newEmbedId = Get-NextRelationId -RelationshipsXml $targetRelsXml
    $embedReplacementMap[$oldEmbedId] = $newEmbedId

    $newRelationshipNode = $targetRelsXml.CreateElement('Relationship', $targetRelsXml.DocumentElement.NamespaceURI)
    [void]$newRelationshipNode.SetAttribute('Id', $newEmbedId)
    [void]$newRelationshipNode.SetAttribute('Type', $imageRelationshipType)
    [void]$newRelationshipNode.SetAttribute('Target', 'media/' + $targetMediaName)
    [void]$targetRelsXml.DocumentElement.AppendChild($newRelationshipNode)

    Copy-ZipEntry -SourceDocxPath $sourcePath -SourceEntryName $sourceEntryName -TargetDocxPath $targetPath -TargetEntryName ('word/media/' + $targetMediaName)
}

Ensure-ContentTypeDefault -ContentTypesXml $contentTypesXml -Extension 'jpg' -ContentType 'image/jpeg'
Ensure-ContentTypeDefault -ContentTypesXml $contentTypesXml -Extension 'jpeg' -ContentType 'image/jpeg'

$insertPlans = [System.Collections.Generic.List[object]]::new()
foreach ($block in $missingBlocks) {
    $chapterBoundary = $chapterBoundaries | Where-Object { $_.ChapterIndex -eq $block.ChapterIndex } | Select-Object -First 1
    if (-not $chapterBoundary) {
        throw "Chapter $($block.ChapterIndex) does not exist in target document."
    }

    $anchorStartIndex = Find-AnchorStartIndex -Block $block -TargetBlocks $targetBlocks -ChapterBoundary $chapterBoundary
    $insertPlans.Add([pscustomobject]@{
        Block            = $block
        AnchorStartIndex = $anchorStartIndex
    })
}

$bodyNode = $targetDocXml.DocumentElement.SelectSingleNode('//*[local-name()="body"]')
$bodyParagraphs = @($targetDocXml.DocumentElement.SelectNodes('//*[local-name()="body"]/*[local-name()="p"]'))
$lastInsertedByAnchor = @{}

$orderedPlans = @(
    $insertPlans |
        Sort-Object -Property @(
            @{ Expression = { $_.AnchorStartIndex }; Descending = $true },
            @{ Expression = { $_.Block.SourceIndex }; Descending = $false }
        )
)
foreach ($plan in $orderedPlans) {
    $anchorIndex = $plan.AnchorStartIndex
    $afterNode = if ($lastInsertedByAnchor.ContainsKey($anchorIndex)) {
        $lastInsertedByAnchor[$anchorIndex]
    } else {
        $bodyParagraphs[$anchorIndex]
    }

    $lastNode = $afterNode
    foreach ($outerXml in $plan.Block.OuterXmlList) {
        $updatedOuterXml = Replace-EmbedIds -OuterXml $outerXml -EmbedMap $embedReplacementMap
        $tempXml = [xml]("<root>" + $updatedOuterXml + "</root>")
        $importedNode = $targetDocXml.ImportNode($tempXml.DocumentElement.FirstChild, $true)
        $lastNode = $bodyNode.InsertAfter($importedNode, $lastNode)
    }

    $lastInsertedByAnchor[$anchorIndex] = $lastNode
}

Set-ZipStringEntry -DocxPath $targetPath -EntryName 'word/document.xml' -Content (Save-XmlDocument -XmlDocument $targetDocXml)
Set-ZipStringEntry -DocxPath $targetPath -EntryName 'word/_rels/document.xml.rels' -Content (Save-XmlDocument -XmlDocument $targetRelsXml)
Set-ZipStringEntry -DocxPath $targetPath -EntryName '[Content_Types].xml' -Content (Save-XmlDocument -XmlDocument $contentTypesXml)

Write-Output ("Inserted {0} question blocks into {1}." -f $missingBlocks.Count, [System.IO.Path]::GetFileName($targetPath))
($missingBlocks |
    Group-Object ChapterIndex |
    Sort-Object Name |
    ForEach-Object {
        "Chapter {0}: {1} blocks" -f $_.Name, $_.Count
    })
