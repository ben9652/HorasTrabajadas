# Salgo del script si no se está ejecutando como Administrador
if(-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    exit
}

Write-Host "Process for the debug version of MySQL Connector C++"

$mysql_path = "C:\Program Files\MySQL\Connector C++ 8.0"

# Ahora defino la URL del archivo para la parte de depuración
$url = "https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.0.33-winx64-debug.zip"
$destination = "C:\Program Files\MySQL\mysql-connector-c++-8.0.33-winx64-debug.zip"

# Descargo el conjunto de archivos que servirán para depurar el código de MySQL Connector C++
Invoke-WebRequest -Uri $url -OutFile $destination

# Descomprimo el archivo
Expand-Archive -Path $destination -DestinationPath $mysql_path

# Muevo los contenidos de la carpeta $mysql_path/mysql-connector-c++-8.0.33-winx64/lib64 a la carpeta Debug
Get-ChildItem -Path "$mysql_path\mysql-connector-c++-8.0.33-winx64\lib64" -Recurse | Move-Item -Destination "$mysql_path\lib64\Debug"

# Elimino el directorio descomprimido
Remove-Item -Path "$mysql_path\mysql-connector-c++-8.0.33-winx64" -Recurse -Force

# Elimino el archivo .zip
Remove-Item -Path $destination -Force

# Muevo los archivos contenidos en la carpeta $mysql_path\lib64\Debug\debug a la carpeta $mysql_path\lib64\Debug
Get-ChildItem -Path "$mysql_path\lib64\Debug\debug" -Recurse | Move-Item -Destination "$mysql_path\lib64\Debug"

# Elimino el directorio $mysql_path\lib64\Debug\debug
Remove-Item -Path "$mysql_path\lib64\Debug\debug" -Recurse -Force

# Muevo los archivos contenidos en la carpeta $mysql_path\lib64\Debug\vs14\debug a la carpeta $mysql_path\lib64\Debug\vs14
Get-ChildItem -Path "$mysql_path\lib64\Debug\vs14\debug" -Recurse | Move-Item -Destination "$mysql_path\lib64\Debug\vs14"

# Elimino el directorio $mysql_path\lib64\Debug\vs14\debug
Remove-Item -Path "$mysql_path\lib64\Debug\vs14\debug" -Recurse -Force

# Creo la carpeta $SolutionDir\bin\Debug
$SolutionDir = Split-Path (Split-Path (Split-Path $PSScriptRoot))
New-Item -ItemType directory -Force -Path "$SolutionDir\bin"
New-Item -ItemType directory -Force -Path "$SolutionDir\bin\Debug"

# Copio el archivo $mysql_path\lib64\Debug\mysqlcppconn-9-vs14.dll a la carpeta $SolutionDir\bin\Debug\
Copy-Item -Path "$mysql_path\lib64\Debug\mysqlcppconn-9-vs14.dll" -Destination "$SolutionDir\bin\Debug\"

# Agregar las rutas correspondientes a la variable PATH
function Add-Path($Path) {
    $Path = [Environment]::GetEnvironmentVariable("Path", "User") + [IO.Path]::PathSeparator + $Path
    [Environment]::SetEnvironmentVariable( "Path", $Path, "User" )
}

$new_path = "C:\Program Files\MySQL\Connector C++ 8.0\lib64\Release"
$current_path = [Environment]::GetEnvironmentVariable("Path", "User")
if($current_path -notlike "*$new_path*") {
    Add-Path($new_path)
}