<#
.SYNOPSIS
    Universal Fileless WMI Process Monitor (Local & Remote) with Zebra Striping and Logging.
.DESCRIPTION
    Dynamically deploys in-memory WMI process monitors. Stays resident in the foreground.
    Includes Try/Catch exception routing, Pass-Through Auth, and absolute-path output logging.
#>
[CmdletBinding(PositionalBinding=$false)]
Param (
    [Parameter(Mandatory=$false, HelpMessage="Target IP or Hostname. Default is localhost.")]
    [string]$TargetHost = "localhost",

    [Parameter(Mandatory=$false, HelpMessage="Authentication protocol for WinRM.")]
    [ValidateSet("Kerberos", "Negotiate", "Default")]
    [string]$AuthMode = "Default",

    [Parameter(Mandatory=$false, HelpMessage="Tap Architecture Mode")]
    [ValidateSet("Polling", "Extrinsic", "Hybrid")]
    [string]$Mode = "Polling",

    [Parameter(Mandatory=$false, HelpMessage="Polling interval in seconds for 'Polling' mode.")]
    [ValidateRange(1, 300)]
    [int]$PollingInterval = 1,

    [Parameter(Mandatory=$false, HelpMessage="Username (e.g., DOMAIN\User or Host\User)")]
    [string]$Username,

    [Parameter(Mandatory=$false, HelpMessage="Plaintext Password (WARNING: OPSEC RISK)")]
    [string]$Password,

    [Parameter(Mandatory=$false, HelpMessage="Filename or path to save the captured telemetry.")]
    [string]$Log
)

# ==========================================
# 1. SETUP: LOGGING, CREDENTIALS & SESSIONS
# ==========================================
$global:Session = $null
$global:IsRemote = ($TargetHost -ne "localhost" -and $TargetHost -ne $env:COMPUTERNAME)

# OPSEC Path Resolution: Force absolute paths so background WMI runspaces don't drop files in System32.
if ($Log) {
    if ([System.IO.Path]::IsPathRooted($Log)) {
        $global:LogFile = $Log
    } else {
        $global:LogFile = [System.IO.Path]::Combine((Get-Location).Path, $Log)
    }
    Write-Host "[*] Logging enabled. Telemetry will write to: $global:LogFile" -ForegroundColor DarkGray
} else {
    $global:LogFile = $null
}

if ($global:IsRemote) {
    Write-Host "[*] Remote target specified ($TargetHost)." -ForegroundColor DarkGray
    
    if ($Username -and $Password) {
        Write-Host "[!] OPSEC WARNING: Headless plaintext credentials detected." -ForegroundColor DarkRed
        $SecurePass = ConvertTo-SecureString $Password -AsPlainText -Force
        $Cred = New-Object System.Management.Automation.PSCredential ($Username, $SecurePass)
        Write-Host "[*] Building WinRM Tunnel using provided credentials ($AuthMode authentication)..." -ForegroundColor DarkGray
        
        try {
            if ($AuthMode -eq "Default") {
                $global:Session = New-CimSession -ComputerName $TargetHost -Credential $Cred -ErrorAction Stop
            } else {
                $global:Session = New-CimSession -ComputerName $TargetHost -Credential $Cred -Authentication $AuthMode -ErrorAction Stop
            }
            Write-Host "[+] Remote Tunnel Established!" -ForegroundColor Green
        }
        catch {
            Write-Host "[-] FATAL ERROR: Failed to establish WinRM session." -ForegroundColor Red
            Write-Host "    [DEBUG] Exception: $($_.Exception.Message)" -ForegroundColor Red
            return
        }
    } else {
        Write-Host "[*] No CLI credentials detected. Using current user session context (Pass-Through)..." -ForegroundColor DarkGray
        Write-Host "[*] Building WinRM Tunnel using $AuthMode authentication..." -ForegroundColor DarkGray
        
        try {
            if ($AuthMode -eq "Default") {
                $global:Session = New-CimSession -ComputerName $TargetHost -ErrorAction Stop
            } else {
                $global:Session = New-CimSession -ComputerName $TargetHost -Authentication $AuthMode -ErrorAction Stop
            }
            Write-Host "[+] Remote Tunnel Established!" -ForegroundColor Green
        }
        catch {
            Write-Host "[-] FATAL ERROR: Failed to establish WinRM session." -ForegroundColor Red
            Write-Host "    [DEBUG] Exception: $($_.Exception.Message)" -ForegroundColor Red
            return
        }
    }
}

# ==========================================
# 2. DEFINING THE HOOK ARCHITECTURE
# ==========================================
if ($Mode -eq "Polling") {
    Write-Host "[*] Architecture: Intrinsic Polling (__InstanceCreationEvent)" -ForegroundColor DarkCyan
    $Query = "SELECT * FROM __InstanceCreationEvent WITHIN $PollingInterval WHERE TargetInstance ISA 'Win32_Process'"
} else {
    Write-Host "[*] Architecture: Extrinsic Kernel Trace ($Mode Mode)" -ForegroundColor DarkMagenta
    if ($global:IsRemote) { Write-Host "[!] WARNING: Extrinsic traces over remote tunnels are highly unstable." -ForegroundColor DarkYellow }
    $Query = "SELECT * FROM Win32_ProcessStartTrace"
}

# ==========================================
# 3. THE ACTION BLOCK (TELEMETRY ENGINE)
# ==========================================
$Action = {
    $EventData = $Event.SourceEventArgs.NewEvent
    $ActiveMode = $Event.MessageData 
    
    # [THE TRICK] Determine if the Event ID is Even or Odd for Zebra Striping
    $IsEven = ($Event.EventIdentifier % 2 -eq 0)
    $OutputString = $null
    
    try {
        # SCENARIO A: Polling Mode
        if ($ActiveMode -eq "Polling") {
            $PID = $EventData.TargetInstance.ProcessId
            $Name = $EventData.TargetInstance.Name
            $CmdLine = $EventData.TargetInstance.CommandLine
            
            $Color = if ($IsEven) { "Green" } else { "Magenta" }
            if ($CmdLine) { $OutputString = "[PSPW] Caught: $Name (PID: $PID) -> $CmdLine" }
        } 
        # SCENARIO B: Hybrid Mode
        elseif ($ActiveMode -eq "Hybrid") {
            $PID = $EventData.ProcessID
            $Name = $EventData.ProcessName
            
            if ($global:IsRemote -and $global:Session) {
                $RealProcess = Get-CimInstance -CimSession $global:Session -ClassName Win32_Process -Filter "ProcessId=$PID" -ErrorAction Stop
            } else {
                $RealProcess = Get-CimInstance -ClassName Win32_Process -Filter "ProcessId=$PID" -ErrorAction Stop
            }
            
            $CmdLine = $RealProcess.CommandLine
            $Color = if ($IsEven) { "Green" } else { "Magenta" }
            if ($CmdLine) { $OutputString = "[PSPW] Caught: $Name (PID: $PID) -> $CmdLine" }
        }
        # SCENARIO C: Strict Extrinsic 
        elseif ($ActiveMode -eq "Extrinsic") {
            $PID = $EventData.ProcessID
            $Name = $EventData.ProcessName
            
            $Color = if ($IsEven) { "Gray" } else { "DarkGray" }
            $OutputString = "[PSPW] Caught: $Name (PID: $PID)"
        }

        # Render to Screen and Disk
        if ($OutputString) {
            Write-Host $OutputString -ForegroundColor $Color
            
            if ($global:LogFile) {
                $Timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
                "[$Timestamp] $OutputString" | Out-File -FilePath $global:LogFile -Append -Encoding UTF8
            }
        }
    } 
    catch {
        # Silently catch errors in the action block
    }
}

# ==========================================
# 4. DEPLOYMENT & OPSEC LOOP
# ==========================================
try {
    Write-Host "[*] Deploying Tap into memory..." -ForegroundColor DarkGray

    try {
        if ($global:IsRemote) {
            Register-CimIndicationEvent -CimSession $global:Session -Query $Query -SourceIdentifier "PSPW_Event" -Action $Action -MessageData $Mode -ErrorAction Stop | Out-Null
        } elseif ($Mode -eq "Hybrid" -or $Mode -eq "Extrinsic") {
            Register-WmiEvent -Query $Query -SourceIdentifier "PSPW_Event" -Action $Action -MessageData $Mode -ErrorAction Stop | Out-Null
        } else {
            Register-CimIndicationEvent -Query $Query -SourceIdentifier "PSPW_Event" -Action $Action -MessageData $Mode -ErrorAction Stop | Out-Null
        }
    } 
    catch {
        Write-Host "[-] FATAL ERROR: WMI Event Registration Failed." -ForegroundColor Red
        Write-Host "    [DEBUG] Exception: $($_.Exception.Message)" -ForegroundColor Red
        Write-Host "    [DEBUG] Did you forget to 'Run as Administrator' for an Extrinsic hook?" -ForegroundColor Red
        return
    }

    Write-Host "[+] ACTIVE: PSPW is live." -ForegroundColor Yellow
    Write-Host "[!] Press [Ctrl + C] at any time to kill the tap and erase the signature." -ForegroundColor White -BackgroundColor DarkRed

    while ($true) {
        Start-Sleep -Milliseconds 500
    }
}
finally {
    # ==========================================
    # 5. THE CLEANUP ROUTINE
    # ==========================================
    Write-Host "`n[*] Interrupt received. Executing OPSEC Cleanup..." -ForegroundColor DarkYellow
    
    $ActiveTap = Get-EventSubscriber -SourceIdentifier "PSPW_Event" -ErrorAction SilentlyContinue
    if ($ActiveTap) {
        Unregister-Event -SourceIdentifier "PSPW_Event" -Force
        Write-Host "    [+] In-memory WMI subscription destroyed." -ForegroundColor Green
    }

    if ($global:Session) {
        Remove-CimSession -CimSession $global:Session
        Write-Host "    [+] WinRM tunnel collapsed." -ForegroundColor Green
    }
    
    Remove-Variable -Name Session -Scope Global -ErrorAction SilentlyContinue
    Remove-Variable -Name IsRemote -Scope Global -ErrorAction SilentlyContinue
    Remove-Variable -Name LogFile -Scope Global -ErrorAction SilentlyContinue

    Write-Host "[+] Cleanup complete. Ghosting the network." -ForegroundColor DarkGray
}