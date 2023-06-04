# HorasTrabajadas
Programa que lleva un conteo de las horas trabajadas en distintas actividades.

# MySQL Connector C++
Para este proyecto debe descargarse:
- https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.0.33-winx64.zip
- https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.0.33-winx64-debug.zip

# cURL
Para compilar libcurl desde su código fuente para una arquitectura de 64 bits utilizando nmake, necesitarás tener las herramientas de compilación apropiadas instaladas en tu máquina. En este caso, necesitarás una instalación de Visual Studio que incluya las herramientas de línea de comandos para C++ y nmake.

Puedes seguir los siguientes pasos para compilar libcurl:

Clona el repositorio de libcurl desde GitHub

Puedes clonar el repositorio oficial de libcurl desde GitHub utilizando git. Abre una terminal y ejecuta el siguiente comando:
```
git clone https://github.com/curl/curl.git
```
Este comando clonará el repositorio de libcurl en una carpeta llamada curl en tu directorio actual.

Abre la terminal de desarrollador de Visual Studio

Ahora necesitas abrir una terminal de desarrollador de Visual Studio para 64 bits. Puedes hacer esto desde el menú de inicio de Windows - busca "x64 Native Tools Command Prompt for VS 20XX" (donde XX es el año de tu versión de Visual Studio), y ábrelo.

Compila libcurl con nmake

Navega al directorio que contiene el código fuente de libcurl (la carpeta curl que creaste al clonar el repositorio de GitHub). Dentro de la carpeta curl, navega a la carpeta winbuild.

Una vez estés en el directorio winbuild, puedes ejecutar el siguiente comando para compilar libcurl:
```
nmake /f Makefile.vc mode=dll VC=14 MACHINE=x64
```
Aquí, mode=dll indica que quieres compilar libcurl como una biblioteca de enlace dinámico (DLL), VC=14 especifica la versión del compilador de Visual C++ que estás utilizando (puede ser necesario ajustar este valor según tu versión de Visual Studio), y MACHINE=x64 especifica que estás compilando para una arquitectura de 64 bits.

nmake debería comenzar a compilar libcurl. Esto puede tardar algunos minutos.

Utiliza la biblioteca compilada en tu proyecto

Una vez que libcurl se ha compilado con éxito, puedes encontrar las bibliotecas compiladas y los archivos de encabezado en las carpetas builds del directorio curl. Asegúrate de utilizar la versión de libcurl compilada para 64 bits en tu proyecto de Visual Studio.