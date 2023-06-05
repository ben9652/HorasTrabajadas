@echo off
setlocal

REM Leer la dirección IP de MySQLServer.txt
set /p mysqlip=<"%~dp0/MySQLServer.txt"

REM Leer la dirección IP de ApacheServer.txt
set /p apacheip=<"%~dp0/ApacheServer.txt"

cd %~dp0\..\..\..
mkdir servers
cd servers
for /f "delims=" %%i in ('cd') do set CURRENT_DIR=%%i

REM Escribir las direcciones IP en servers.h
(
    echo #include ^<string^>
    echo #define MYSQL_IP "%mysqlip%"
    echo #define APACHE_IP "%apacheip%"
    echo const std::string mysql_ip = MYSQL_IP;
    echo const std::string apache_ip = APACHE_IP;
) > "%CURRENT_DIR%\servers.h"

endlocal