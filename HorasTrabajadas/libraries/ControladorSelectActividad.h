#ifndef __CONTROLADOR_SELECT_ACTIVIDAD_
#define __CONTROLADOR_SELECT_ACTIVIDAD_
#include "ControladorPrincipal.h"
#include "GestorActividades.h"

class VistaSelectActividad;

class ControladorSelectActividad
{
private:
	GestorConexion* conector;
	GestorActividades* modelo;
	VistaSelectActividad* vista;
public:
	ControladorSelectActividad();
	~ControladorSelectActividad();

	size_t cantidadActividades();
	Actividad& obtenerActividadPorId(int idActividad);
	Actividad& obtenerActividadPorIndice(int index);

	void ejecutarLogica();
};

#include "VistaSelectActividad.h"

#endif