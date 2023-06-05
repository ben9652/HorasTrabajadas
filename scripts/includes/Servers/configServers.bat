@echo off
setlocal

REM Leer la dirección IP de MySQLServer.txt
set /p mysqlip=<%~dp0/MySQLServer.txt

REM Leer la dirección IP de ApacheServer.txt
set /p apacheip=<%~dp0/ApacheServer.txt

REM Escribir las direcciones IP en servers.h
(
    echo #define MYSQL_IP "%mysqlip%"
    echo #define APACHE_IP "%apacheip%"
    echo const std::string mysql_ip = MYSQL_IP;
    echo const std::string apache_ip = APACHE_IP;
) > ..\..\..\servers\servers.h

endlocal