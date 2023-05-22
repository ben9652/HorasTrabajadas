#include "ControladorFiltroID.h"
#include "GestorRegistros.h"
#include "common.h"

int ControladorFiltroID::id_busqueda;
bool ControladorFiltroID::filtroAplicado = false;

ControladorFiltroID::ControladorFiltroID(Actividad&& _modelo)
{
	vista = new VistaFiltroID();
	modelo = new Actividad();
	*modelo = _modelo;
}

ControladorFiltroID::ControladorFiltroID()
{
	vista = new VistaFiltroID();
	modelo = nullptr;
}

ControladorFiltroID::~ControladorFiltroID()
{

}

void ControladorFiltroID::ejecutarLogica()
{
	GestorRegistros* gr = GestorRegistros::instanciar();
	size_t cantidadRegistrosEnActividad = gr->cantidadRegistrosPorActividad(modelo->getIdActividad());
	size_t digitos;

	for (digitos = 0; cantidadRegistrosEnActividad != 0; cantidadRegistrosEnActividad /= 10)
		digitos++;

	char* IDString;
	int ID;
	do
	{
		vista->limpiar();
		vista->mostrar("Ingresar el ID por el que quiere buscar: ");
		IDString = vista->ingresar_opcion_salir(digitos);
		if (IDString[0] == 0x1B)
			return;
	} while (!es_numero(IDString));

	ID = atoi(IDString);

	id_busqueda = ID;
	filtroAplicado = true;
}

void ControladorFiltroID::limpiarFiltro()
{
	filtroAplicado = false;
}

int ControladorFiltroID::getFiltro()
{
	return id_busqueda;
}

bool ControladorFiltroID::hayFiltro()
{
	return filtroAplicado;
}