@echo off

set "psScriptPath1=%~dp0releaseConnectorVersion.ps1"
set "psScriptPath2=%~dp0debugConnectorVersion.ps1"

net session >nul 2>&1 || (
    powershell -NoProfile -ExecutionPolicy Bypass -Command ^
        "Start-Process -Verb RunAs -FilePath '%~f0' -WorkingDirectory '%cd%'; exit"
)

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%psScriptPath1%" %*
if errorlevel 1 exit /b 1

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%psScriptPath2%" %*

exit /b