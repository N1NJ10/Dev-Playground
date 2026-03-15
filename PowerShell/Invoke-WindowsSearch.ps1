function Invoke-WindowsSearch {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory=$false)]
        [string]$TargetHost,        

        [Parameter(Mandatory=$false)]
        [string]$SearchString,      

        [Parameter(Mandatory=$false)]
        [string]$WordList,         

        [Parameter(Mandatory=$false)]
        [string]$Scope              
    )

    if (-not $SearchString -and -not $WordList) {
        Write-Error "[-] Tradecraft error: You must provide either -SearchString or -WordList."
        return
    }

    $CleanKeywords = @()

    if ($SearchString) {
        $CleanKeywords += $SearchString.Trim()
    }

    if ($WordList) {
        if (-not (Test-Path $WordList)) {
            Write-Error "[-] Wordlist not found at $WordList"
            return
        }
        $RawWords = Get-Content $WordList | Where-Object { $_ -match '\S' }
        foreach ($Word in $RawWords) {
            $Cleaned = $Word -replace "[^a-zA-Z0-9\*\.\-_ ]", ""
            if ($Cleaned.Trim().Length -gt 2) {
                $CleanKeywords += $Cleaned.Trim()
            }
        }
    }

    $CleanKeywords = $CleanKeywords | Select-Object -Unique

    if ($CleanKeywords.Count -eq 0) {
        Write-Error "[-] No valid keywords to search after sanitization."
        return
    }

    $Catalog = "SystemIndex"
    $DisplayTarget = "localhost"
    if (-not [string]::IsNullOrWhiteSpace($TargetHost) -and $TargetHost -ne "localhost" -and $TargetHost -ne $env:COMPUTERNAME) {
        $Catalog = "$TargetHost.SystemIndex"
        $DisplayTarget = $TargetHost
    }

    $connectionString = "Provider=Search.CollatorDSO.1;Extended Properties='Application=Windows'"
    $MasterResults = @()

    $BatchSize = 10
    $TotalBatches = [math]::Ceiling($CleanKeywords.Count / $BatchSize)

    for ($i = 0; $i -lt $TotalBatches; $i++) {
        $Chunk = $CleanKeywords | Select-Object -Skip ($i * $BatchSize) -First $BatchSize
        
        $ContainsClauses = @()
        foreach ($Word in $Chunk) {
            $ContainsClauses += "CONTAINS(*, '`"$Word`"')"
        }
        $WhereCondition = $ContainsClauses -join " OR "

        $query = @"
            SELECT System.ItemName, System.ItemPathDisplay, System.Size, System.DateModified
            FROM $Catalog
            WHERE ($WhereCondition)
            $(if ($Scope) { "AND SCOPE='$Scope'" })
"@
        
        try {
            $adapter = New-Object System.Data.OleDb.OleDbDataAdapter($query, $connectionString)
            $results = New-Object System.Data.DataSet
            $null = $adapter.Fill($results)

            if ($results.Tables.Count -gt 0 -and $results.Tables[0].Rows.Count -gt 0) {
                $MasterResults += $results.Tables[0]
            }
        }
        catch {
            Write-Host "[-] Database choked on a chunk. Moving to the next." -ForegroundColor DarkGray
        }
    }

    if ($MasterResults.Count -eq 0) {
        Write-Host "[-] No matches found on $DisplayTarget" -ForegroundColor DarkGray
    }
    else {
        Write-Host "`n[+] Hits confirmed on $DisplayTarget!" -ForegroundColor Green
        $MasterResults | Select-Object "System.ItemName", "System.ItemPathDisplay", "System.Size", "System.DateModified" -Unique | Format-Table -AutoSize
    }
}
