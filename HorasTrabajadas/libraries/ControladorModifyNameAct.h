#ifndef __CONTROLADOR_MODIFICAR_NOMBRE_DE_ACTIVIDAD
#define __CONTROLADOR_MODIFICAR_NOMBRE_DE_ACTIVIDAD
#include "VistaModifyNameAct.h"
#include "Actividad.h"

class ControladorModifyNameAct
{
private:
	VistaModifyNameAct* vista;
	Actividad* modelo;
public:
	ControladorModifyNameAct(Actividad&& _modelo);

	void ejecutarLogica();
};

#endif