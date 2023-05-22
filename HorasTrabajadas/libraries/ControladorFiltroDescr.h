#ifndef __CONTROLADOR_FILTRO_DESCRIPCION_
#define __CONTROLADOR_FILTRO_DESCRIPCION_
#include "Actividad.h"
#include "GestorConexion.h"

class VistaFiltroDescr;

class ControladorFiltroDescr
{
private:
	VistaFiltroDescr* vista;

	static char* descripcion_busqueda;
	static bool filtroAplicado;

public:
	ControladorFiltroDescr();
	~ControladorFiltroDescr();

	void ejecutarLogica();
	void limpiarFiltro();
	char* getFiltro();
	bool hayFiltro();
};

#include "VistaFiltroDescr.h"

#endif