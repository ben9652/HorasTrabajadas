#ifndef __CONTROLADOR_ACTIVIDADES_
#define __CONTROLADOR_ACTIVIDADES_
#include "Actividad.h"
#include "GestorConexion.h"

class VistaActividad;

class ControladorActividad
{
private:
	GestorConexion* conector;
	Actividad* modelo;
	VistaActividad* vista;

public:
	ControladorActividad(Actividad&& _modelo);
	~ControladorActividad();

	const char* getNombreActividad() const;
	const char* getTiempoTotal() const;

	void ejecutarLogica();
};

#include "VistaActividad.h"

#endif