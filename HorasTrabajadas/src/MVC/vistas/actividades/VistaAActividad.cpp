#include "VistaAActividad.h"
#include "GestorVistas.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "common.h"

VistaAActividad::VistaAActividad()
{
	SetConsoleBufferSize(1000, 20000);
}

void VistaAActividad::MenuAgregarActividad()
{
	std::cout << "A continuación, escriba el nombre de la actividad. Si desea volver, escriba \"volver\"\n" << std::endl;

	std::cout << "Ingresar nombre de actividad: ";
}
