@echo off

cd C:\
git clone https://github.com/curl/curl.git
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
echo Comandos de VC++ disponibles
cd curl\winbuild
nmake /f Makefile.vc mode=dll VC=14 MACHINE=x64

powershell.exe -ExecutionPolicy Bypass -File "%~dp0/agregadoRuta.ps1"