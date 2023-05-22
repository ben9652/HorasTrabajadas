#ifndef __VISTA_SELECT_ACTIVIDAD_
#define __VISTA_SELECT_ACTIVIDAD_
#include "ControladorSelectActividad.h"
#include "VistaBase.h"
#include "GestorVistas.h"
#include <stdlib.h>

class VistaSelectActividad : public VistaBase
{
private:
	ControladorSelectActividad* controlador;
public:
	VistaSelectActividad(ControladorSelectActividad* controlador);

	void MenuSeleccionarActividad();
};

#endif