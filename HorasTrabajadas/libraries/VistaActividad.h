#ifndef __VISTA_ACTIVIDADES_
#define __VISTA_ACTIVIDADES_
#include "VistaBase.h"
#include "ControladorActividad.h"
#include "GestorVistas.h"

class VistaActividad : public VistaBase
{
private:
	ControladorActividad* controlador;
public:
	VistaActividad(ControladorActividad* controlador);

	void MenuActividad();
};

#endif