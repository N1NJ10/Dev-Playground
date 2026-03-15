function Invoke-WindowsSearch {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory=$false)]
        [string]$SearchString = "password",
        
        [Parameter(Mandatory=$false)]
        [string]$Scope = "file:",   # Can limit to specific paths, e.g., "file:///C:/Users"
        
        [Parameter(Mandatory=$false)]
        [switch]$IncludeProperties  # Return more metadata
    )

    # Correct connection string
    $connectionString = "Provider=Search.CollatorDSO.1;Extended Properties='Application=Windows'"
    
    # Build query with optional SCOPE restriction
    $query = @"
        SELECT system.itemname, system.itempathdisplay, system.size, system.datecreated, system.datemodified
        FROM systemindex 
        WHERE contains('$SearchString') 
        $(if ($Scope) { "AND SCOPE='$Scope'" })
"@

    try {
        $adapter = New-Object System.Data.OleDb.OleDbDataAdapter($query, $connectionString)
        $results = New-Object System.Data.DataSet
        $null = $adapter.Fill($results)
        
        if ($results.Tables[0].Rows.Count -eq 0) {
            Write-Verbose "No matches found for '$SearchString'"
        }
        else {
            $results.Tables[0]
        }
    }
    catch {
        Write-Error "Query failed: $_"
    }
    finally {
        $adapter.Dispose()
        $results.Dispose()
    }
}
