#ifndef __CONTROLADOR_ELIMINAR_REGISTRO
#define __CONTROLADOR_ELIMINAR_REGISTRO
#include "Registro.h"
#include "VistaDelRegistro.h"

class ControladorDelRegistro
{
private:
	Registro* modelo;
	VistaDelRegistro* vista;
public:
	ControladorDelRegistro(Registro&& _modelo);
	~ControladorDelRegistro();

	void ejecutarLogica();
};

#endif