# HorasTrabajadas
Programa que lleva un conteo de las horas trabajadas en distintas actividades.

## Instalación
Solo debes ejecutar el archivo Setup.bat que se encuentra dentro de la carpeta scripts.
Este archivo se encargará de instalar las dependencias necesarias para el funcionamiento del programa.
Particularmente instalará la librería de MySQL Connector C++ en el sistema y la librería de Curl en esta misma solución.

## Configuración de direccionamiento de servidores
El archivo anterior creó unos archivos de texto los cuales debes modificar según tus necesidades. Son las direcciones IP de los servidores, y se deben escribir en los archivos ApacheServer.txt y MySQLServer.txt que se encuentran en la carpeta scripts/includes/Servers. De esta manera se podrá direccionar el programa a los servidores que desees.
El servidor Apache sirve para realizar las actualizaciones del programa si es que hay disponibles, y el servidor MySQL tiene los datos de los usuarios y sus horas trabajadas.