@echo off

pushd .\includes\Servers
echo localhost > MySQLServer.txt
echo localhost > ApacheServer.txt
popd

call "%~dp0\includes\MySQL\MySQLsetup.bat"
call "%~dp0\includes\Curl\CurlSetup.bat"

pushd ..
vendor\bin\premake5.exe vs2022
popd