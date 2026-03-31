# Invoke-WindowsSearch

Brief manual for `Invoke-WindowsSearch.ps1`.

## What It Does

`Invoke-WindowsSearch.ps1` queries the Windows Search index to look for files and indexed content that match one keyword or a list of keywords. It supports local use and remote querying, plus optional output filtering and export.

## Main Parameters

- `-SearchString`: search for one keyword.
- `-WordList`: path to a text file with multiple keywords.
- `-TargetHost`: remote host to query.
- `-Scope`: limit the search to a specific path or indexed scope.
- `-Credential`: use explicit credentials for remote execution.
- `-IncludePattern`: only keep matching filenames.
- `-ExcludePattern`: filter out matching filenames.
- `-OutputFormat`: `Table`, `CSV`, or `JSON`.
- `-OutputPath`: save `CSV` or `JSON` output to a file.
- `-MaxResults`: stop after a specific number of results.

## Basic Usage

Load the script into the current PowerShell session:

```powershell
. .\Invoke-WindowsSearch.ps1
```

Search locally with a single keyword:

```powershell
Invoke-WindowsSearch -SearchString "keepass" -Scope "file:///C:/Users"
```

Search a remote host with a wordlist:

```powershell
Invoke-WindowsSearch -TargetHost "WIN-102" -WordList ".\searchstrings.txt"
```

Export results as JSON:

```powershell
Invoke-WindowsSearch -TargetHost "WIN-102" -WordList ".\searchstrings.txt" -OutputFormat JSON -OutputPath ".\results.json"
```

## Notes

- You must provide either `-SearchString` or `-WordList`.
- The wordlist is sanitized and deduplicated before querying.
- Windows Server systems may return no results if the `WSearch` service is disabled.
- Filename filters do not search file content; they only filter the returned file names.
