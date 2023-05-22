#include "VistaSelectActividad.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "common.h"

VistaSelectActividad::VistaSelectActividad(ControladorSelectActividad* controlador)
{
	this->controlador = controlador;
}

void VistaSelectActividad::MenuSeleccionarActividad()
{
	std::cout << "Instrucciones:\n";
	std::cout << "  En este menú se muestran todas las actividades existentes actualmente. Al entrar en cualquiera de\n"
		<< "estas, se puede realizar diferentes acciones sobre cada una de ellas.\n\n";

	for (int i = 0; i < controlador->cantidadActividades(); i++)
	{
		std::cout << "  " << controlador->obtenerActividadPorIndice(i).getIdActividad() << "- ";
		std::cout << controlador->obtenerActividadPorIndice(i).getNombre() << "\n";
	}

	std::cout << std::endl;

	if (controlador->cantidadActividades() == 0)
		std::cout << "  No hay actividades creadas.\n";
}
