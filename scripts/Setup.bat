@echo off

call "%~dp0\includes\MySQL\MySQLsetup.bat"
call "%~dp0\includes\Curl\CurlSetup.bat"
call "%~dp0\includes\Servers\configServers.bat"

pushd ..
vendor\bin\premake5.exe vs2022
popd