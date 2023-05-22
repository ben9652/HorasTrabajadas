#ifndef __CONTROLADOR_FILTRO_ID_
#define __CONTROLADOR_FILTRO_ID_
#include "Actividad.h"
#include "GestorConexion.h"

class VistaFiltroID;

class ControladorFiltroID
{
private:
	VistaFiltroID* vista;
	Actividad* modelo;

	static int id_busqueda;
	static bool filtroAplicado;

public:
	ControladorFiltroID(Actividad&& _modelo);
	ControladorFiltroID();
	~ControladorFiltroID();

	void ejecutarLogica();
	void limpiarFiltro();
	int getFiltro();
	bool hayFiltro();

};

#include "VistaFiltroID.h"

#endif