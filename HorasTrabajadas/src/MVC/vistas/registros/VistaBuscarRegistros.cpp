#include "VistaBuscarRegistros.h"
#include "common.h"
#include <iostream>

VistaBuscarRegistros::VistaBuscarRegistros()
{
	SetConsoleBufferSize(1000, 20000);
}

void VistaBuscarRegistros::MenuBuscarRegistros()
{
	std::cout << "1- ID del registro\n"
			  << "2- Tiempo consumido\n"
			  << "3- Fecha\n"
			  << "4- Descripción\n"
			  << "5- Limpiar filtros\n"
			  << "6- Buscar\n"
			  << std::endl;
}
