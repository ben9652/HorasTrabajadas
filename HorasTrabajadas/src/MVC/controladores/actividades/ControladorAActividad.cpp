#include "ControladorAActividad.h"
#include "ConnectionException.h"
#include "VistaAActividad.h"
#include <string>
#include <Windows.h>
#include "common.h"

ControladorAActividad::ControladorAActividad()
{
	conector = GestorConexion::instanciar();
	modelo = GestorActividades::instanciar();
	vista = new VistaAActividad();

	ejecutarLogica();
}

ControladorAActividad::~ControladorAActividad()
{
	delete vista;
}

void ControladorAActividad::ejecutarLogica()
{
	GestorActividades* ga = GestorActividades::instanciar();
	vista->limpiar();
	vista->MenuAgregarActividad();
	
	char* nombreActividad = (char*)malloc(100);
	
	nombreActividad = vista->ingresar_opcion_salir(99);
	if (nombreActividad[0] == 0x1B)
		return;

	vista->mostrar("\n");

	sql::ResultSet* res = ga->CrearActividad(ascii_to_utf8(nombreActividad));
	sql::SQLString mensaje = res->getString(1);
	vista->mostrar(mensaje.c_str());
	vista->ingresar(0);
}