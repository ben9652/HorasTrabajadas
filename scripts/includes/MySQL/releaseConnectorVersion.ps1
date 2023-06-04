# Salgo del script si no se está ejecutando como Administrador
if(-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    exit
}

Write-Host "Process for the release version of MySQL Connector C++"

# Define la ruta del directorio MySQL Connector
$mysql_path = "C:\Program Files\MySQL\Connector C++ 8.0"

# Si el directorio Connector C++ no existe
if(!(Test-Path -path $mysql_path)) {
    # Define la URL del archivo y la carpeta de destino
    $url = "https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.0.33-winx64.zip"
    $destination = "C:\Program Files\MySQL\mysql-connector-c++-8.0.33-winx64.zip"

    # Descarga el archivo si aún no se ha descargado
    if(!(Test-Path -path $destination)) {
        # Crea la carpeta de destino si no existe
        New-Item -ItemType directory -Force -Path $mysql_path

        # Descarga el archivo
        Invoke-WebRequest -Uri $url -OutFile $destination
    }

    # Descomprime el archivo
    Expand-Archive -Path $destination -DestinationPath $mysql_path

    # Mueve todos los archivos del directorio descomprimido al directorio Connector C++
    Get-ChildItem -Path "$mysql_path\mysql-connector-c++-8.0.33-winx64" -Recurse | Move-Item -Destination $mysql_path

    # Elimina el directorio descomprimido
    Remove-Item -Path "$mysql_path\mysql-connector-c++-8.0.33-winx64" -Recurse -Force

    # Elimina el archivo .zip
    Remove-Item -Path $destination -Force

    # Creo dentro de la carpeta lib64 las carpetas Debug y Release
    New-Item -ItemType directory -Force -Path "$mysql_path\lib64\Release"
    New-Item -ItemType directory -Force -Path "$mysql_path\lib64\Debug"

    # Paso todos los archivos dentro de lib64, exceptuando las carpetas Release y Debug, a la carpeta Release
    Get-ChildItem -Path "$mysql_path\lib64" -Exclude "Release", "Debug" | Move-Item -Destination "$mysql_path\lib64\Release"
}
else {
    throw "El directorio Connector C++ ya existe"
}