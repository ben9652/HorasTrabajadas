#ifndef __CONTROLADOR_AGREGAR_ACTIVIDAD_
#define __CONTROLADOR_AGREGAR_ACTIVIDAD_
#include "GestorActividades.h"
#include "VistaAActividad.h"
#include "GestorConexion.h"

class ControladorAActividad
{
private:
	GestorConexion* conector;
	GestorActividades* modelo;
	VistaAActividad* vista;
public:
	ControladorAActividad();
	~ControladorAActividad();

	void ejecutarLogica();
};

#endif