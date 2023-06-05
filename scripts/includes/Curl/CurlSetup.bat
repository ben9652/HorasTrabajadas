@echo off

set "psScriptPath=%~dp0agregadoRuta.ps1"

pushd %~dp0\..\..\..\vendor
IF NOT EXIST curl (
    git clone https://github.com/curl/curl.git
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    echo Comandos de VC++ disponibles
    pushd curl\winbuild
    nmake /f Makefile.vc mode=dll VC=14 MACHINE=x64
    popd
    popd
    powershell.exe -ExecutionPolicy Bypass -File "%psScriptPath%"
)