#ifndef __CONTROLADOR_INGRESAR_TIEMPO_AGRUPACION_
#define __CONTROLADOR_INGRESAR_TIEMPO_AGRUPACION_
#include "VistaIngresarTA.h"
#include "Actividad.h"

class ControladorIngresarTA
{
private:
	VistaIngresarTA* vista;
	Actividad* modelo;
public:
	ControladorIngresarTA(Actividad&& actividad);
	void ejecutarLogica();
};

#endif