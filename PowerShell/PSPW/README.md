# 🛡️ PSPW
**The Fileless WMI Process Monitor**

PSPW is in-memory Windows process monitor designed for Red Team operators. It dynamically deploys WMI (Windows Management Instrumentation) event subscriptions to track process creation and extract command-line arguments in real-time, leaving zero artifacts on disk. 

It supports local and remote execution, headless authentication, thread-safe zebra-striped terminal output, and automated OPSEC cleanup.

## Features
* **100% Fileless:** Operates entirely in memory via WMI and CIM cmdlets. No `.exe` or `.dll` drops.
* **Tri-Mode Architecture:** Choose between Intrinsic Polling, Extrinsic Kernel Traces, or a Hybrid extraction method depending on your OPSEC requirements.
* **Remote WinRM Tunnels:** Attack remote domain machines via Kerberos or local administrator accounts via NTLM (Negotiate).
* **Automated OPSEC Cleanup:** Safely unregisters WMI subscriptions and collapses network tunnels the exact second you press `Ctrl+C`.
* **Pass-Through & Headless Auth:** Automatically use your current session token, or explicitly pass credentials to bypass the Windows Double-Hop restriction.

---

## ⚙️ The Three Architectures (`-Mode`)

PSPW bypasses the standard limitations of WMI by offering three distinct monitoring engines:

### 1. `Polling` (The Default)
* **Under the hood:** Uses `__InstanceCreationEvent` to poll the OS every 1 second.
* **Pros:** Standard user compatible. Accurately captures full command-line arguments. Highly stable over remote network jumps.
* **Cons:** Causes a slight, periodic CPU spike in `WmiPrvSE.exe` which mature EDRs may detect. 

### 2. `Extrinsic` (The Ghost)
* **Under the hood:** Wiretaps the Windows Kernel's ETW feed using `Win32_ProcessStartTrace`.
* **Pros:** Absolute stealth. Zero CPU polling overhead. Completely event-driven.
* **Cons:** Requires Local Administrator privileges. **Cannot capture command-line arguments** (the Windows kernel does not include them in this specific trace). 

### 3. `Hybrid` (The God Mode)
* **Under the hood:** Uses the silent Extrinsic kernel trace as a tripwire, then instantly fires a secondary CIM query to steal the command line before the process dies.
* **Pros:** Zero CPU polling + Full Command Lines.
* **Cons:** Requires Local Administrator privileges. Can be network-intense over WinRM if hundreds of processes spawn simultaneously.

---

## Usage & Examples

[https://www.youtube.com/watch?v=lXYq36AYDM0](https://www.youtube.com/watch?v=lXYq36AYDM0)


### Prerequisites
* Windows PowerShell 5.1+
* If using `Extrinsic` or `Hybrid` modes locally, the terminal **must** be Run as Administrator.
* If running remotely, the target must have WinRM enabled (`Port 5985`).

### Basic Examples

**Local Stealth Trace (Requires Admin)**
Deploys the tap locally using the zero-CPU Hybrid trace. Extracts command lines silently.
> .\PSPW.ps1 -Mode Hybrid

**Remote Domain Attack (Interactive)**
Attacks a remote Domain machine (`Win-102`) using Pass-Through authentication (uses your current Kerberos ticket). Deploys the standard Polling tap.
> .\PSPW.ps1 -TargetHost "Win-102" -Mode Polling

**Low & Slow EDR Evasion (Remote)**
Attacks a remote machine via NTLM (Local Admin). Slows the polling interval down to 5 seconds to blend in with background noise and evade anomalous WMI resource consumption alerts.
> .\PSPW.ps1 -TargetHost "Win-102" -AuthMode Negotiate -PollingInterval 5

**Headless Automation / Double-Hop Bypass (WARNING: Read OPSEC Notes)**
Executes without GUI prompts. Essential for deploying via C2 frameworks or bypassing WinRM's Pass-Through restrictions when operating from a `psexec` shell. 
> .\PSPW.ps1 -TargetHost "Win-102" -Username "DOMAIN\User" -Password "Password123!" -Mode Hybrid

---

## OPSEC Considerations

### 1. The Headless Password Trap (`PSReadLine`)
If you use the `-Username` and `-Password` parameters directly in an interactive PowerShell console, your plaintext password will be permanently saved to the hard drive in the `PSReadLine` history file.

**Remediation:** After running a headless command, instantly burn your PowerShell history by running:
> Remove-Item (Get-PSReadLineOption).HistorySavePath -ErrorAction SilentlyContinue

### 2. Manual Cleanup
PSPW is designed to self-destruct when you interrupt it with `Ctrl+C`. However, if your terminal crashes or your C2 beacon dies before you can gracefully exit, the WMI event will remain permanently stuck in memory. 

To manually hunt down and kill an orphaned PSPW listener, open an elevated PowerShell window and run:
> Get-EventSubscriber -SourceIdentifier "PSPW_Event" -ErrorAction SilentlyContinue | Unregister-Event -Force
 
