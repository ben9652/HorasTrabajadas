#ifndef __CONTROLADOR_FILTRO_TIEMPO_
#define __CONTROLADOR_FILTRO_TIEMPO_
#include "Actividad.h"
#include "GestorConexion.h"

class VistaFiltroTiempo;

namespace {
	struct TiemposFiltro
	{
		unsigned int tiempoInicio;
		unsigned int tiempoFin;
	};
}

class ControladorFiltroTiempo
{
public:
	ControladorFiltroTiempo();
	~ControladorFiltroTiempo();

	enum Tiempo { SIN_CRITERIO = -1, IGUAL, MENOR, MENOR_O_IGUAL, MAYOR, MAYOR_O_IGUAL, ENTRE };

	void ejecutarLogica();
	unsigned int escribirTiempoFiltro();

	void limpiarFiltro();
	unsigned int getTiempoFiltroInicio();
	unsigned int getTiempoFiltroFin();
	Tiempo getCriterio();
	bool hayFiltro();

private:
	VistaFiltroTiempo* vista;

	static TiemposFiltro tiempo_busqueda;
	static Tiempo criterio;
	static bool filtroAplicado;
};

#include "VistaFiltroTiempo.h"

#endif