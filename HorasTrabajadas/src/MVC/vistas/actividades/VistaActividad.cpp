#include "VistaActividad.h"
#include "GestorActividades.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "common.h"

VistaActividad::VistaActividad(ControladorActividad* controlador)
{
	SetConsoleBufferSize(1000, 20000);
	this->controlador = controlador;
}

void VistaActividad::MenuActividad()
{
	std::cout << "Nombre de actividad: " << controlador->getNombreActividad() << "\n";
	std::cout << "Tiempo total consumido: " << controlador->getTiempoTotal() << "\n\n";
	std::cout << "1- Ingresar tiempo\n"
			  << "2- Listar registros\n"
			  << "3- Buscar registros\n"
			  << "4- Tiempo de trabajo de cada usuario\n"
			  << "5- Ingresar un tiempo en el que agrupar los registros\n"
			  << "6- Mostrar registros agrupados\n"
			  << "7- Modificar nombre de la actividad\n"
			  << "8- Eliminar esta actividad\n"
			  << std::endl;
}