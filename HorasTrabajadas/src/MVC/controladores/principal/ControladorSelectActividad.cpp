#include "ControladorSelectActividad.h"
#include "ControladorActividad.h"
#include "Actividad.h"
#include "common.h"
#include <utility>

ControladorSelectActividad::ControladorSelectActividad()
{
	conector = GestorConexion::instanciar();
	modelo = GestorActividades::instanciar();
	vista = new VistaSelectActividad(this);

	ejecutarLogica();
}

ControladorSelectActividad::~ControladorSelectActividad()
{
	delete vista;
}

size_t ControladorSelectActividad::cantidadActividades()
{
	return modelo->cantidadActividades();
}

Actividad& ControladorSelectActividad::obtenerActividadPorId(int idActividad)
{
	return modelo->obtenerActividadPorId(idActividad);
}

Actividad& ControladorSelectActividad::obtenerActividadPorIndice(int index)
{
	return modelo->obtenerActividadPorIndice(index);
}

void ControladorSelectActividad::ejecutarLogica()
{
	char* opcionString;
	int opcion;
	do
	{
		do
		{
			vista->limpiar();
			vista->MenuSeleccionarActividad();
			opcionString = vista->ingresar_opcion_salir(12);
			if (opcionString[0] == 0x1B)
				return;
		} while (!es_numero(opcionString));

		opcion = atoi(opcionString);

		Actividad& actividadSeleccionada = obtenerActividadPorId(opcion);
		if (actividadSeleccionada.esActividadNula())
			continue;

		ControladorActividad ca(std::move(actividadSeleccionada));

	} while (1);
}