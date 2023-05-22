#include "ControladorFiltroDescr.h"

char* ControladorFiltroDescr::descripcion_busqueda;
bool ControladorFiltroDescr::filtroAplicado = false;

ControladorFiltroDescr::ControladorFiltroDescr()
{
	vista = new VistaFiltroDescr();
}

ControladorFiltroDescr::~ControladorFiltroDescr()
{
}

void ControladorFiltroDescr::ejecutarLogica()
{
	char* descripcion = (char*)malloc(256);
	vista->mostrar("Ingresa la descripción de filtrado: ");
	descripcion = vista->ingresar_opcion_salir(255);
	if (descripcion[0] == 0x1B)
		return;
	descripcion_busqueda = descripcion;
	filtroAplicado = true;
}

void ControladorFiltroDescr::limpiarFiltro()
{
	filtroAplicado = false;
	free(descripcion_busqueda);
}

char* ControladorFiltroDescr::getFiltro()
{
	return descripcion_busqueda;
}

bool ControladorFiltroDescr::hayFiltro()
{
	return filtroAplicado;
}