#ifndef __CONTROLADOR_BUSCAR_REGISTROS_
#define __CONTROLADOR_BUSCAR_REGISTROS_
#include "Actividad.h"
#include "GestorConexion.h"

class VistaBuscarRegistros;

class ControladorBuscarRegistros
{
private:
	GestorConexion* conector;
	Actividad* modelo;
	VistaBuscarRegistros* vista;

public:
	ControladorBuscarRegistros(Actividad&& _modelo);
	~ControladorBuscarRegistros();

	void ejecutarLogica();
};

#include "VistaBuscarRegistros.h"

#endif