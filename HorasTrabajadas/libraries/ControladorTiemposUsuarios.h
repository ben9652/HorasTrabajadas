#ifndef __CONTROLADOR_TIEMPOS_USUARIOS
#define __CONTROLADOR_TIEMPOS_USUARIOS
#include <vector>
#include <TextTable.h>
#include "Actividad.h"
#include "GestorConexion.h"
#include "VistaTiemposUsuarios.h"

class ControladorTiemposUsuarios
{
public:
	ControladorTiemposUsuarios(Actividad&& _actividad);

	void ejecutarLogica();
private:
	GestorConexion* conector;
	Actividad* actividad;
	VistaTiemposUsuarios* vista;
};

#endif