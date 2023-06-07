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

	try {
		sql::ResultSet* res = ga->CrearActividad(nombreActividad);
		sql::SQLString mensaje = res->getString(1);
		const char* mensajeMostrado = utf8_to_ascii(mensaje.c_str());
#ifdef FUNCIONA_CHARACTER_SET_LATIN
		vista->mostrar(mensaje.c_str());
#else
		vista->mostrar(mensajeMostrado);
#endif
		vista->ingresar(0);
	}
	catch (ConnectionException ce) {
		std::cout << ce.what() << std::endl;
		std::cin.get();
	}
}