#ifndef __CONTROLADOR_BORRAR_ACTIVIDAD
#define __CONTROLADOR_BORRAR_ACTIVIDAD
#include "VistaDelActividad.h"
#include "Actividad.h"

class ControladorDelActividad
{
private:
	VistaDelActividad* vista;
	Actividad* modelo;
public:
	ControladorDelActividad(Actividad&& _modelo);

	bool ejecutarLogica();
};

#endif