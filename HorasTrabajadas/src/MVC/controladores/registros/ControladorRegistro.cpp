#include "ControladorRegistro.h"
#include "ControladorMTiempo.h"
#include "ControladorMDescr.h"
#include "ControladorDelRegistro.h"
#include "common.h"
#include <string>
#include <sstream>
#include <ctype.h>
#include <utility>

char* ControladorRegistro::descripcionString = (char*)malloc(256);
size_t ControladorRegistro::index_descripcionString = 0;
size_t ControladorRegistro::teclas_apretadas_descripcion = 0;
bool ControladorRegistro::texto_escrito_descr = false;

ControladorRegistro::ControladorRegistro(Registro&& _modelo, Actividad&& _actividad)
{
	conector = GestorConexion::instanciar();
	modelo = new Registro();
	modelo = &_modelo;
	actividad = new Actividad();
	actividad = &_actividad;
	vista = new VistaRegistro();

	ejecutarLogica();
}

ControladorRegistro::~ControladorRegistro()
{
	delete vista;
}

void ControladorRegistro::ejecutarLogica()
{
	char* opcionString;
	int opcion;
	do
	{
		do
		{
			vista->limpiar();
			vista->MenuRegistro();
			opcionString = vista->ingresar_opcion_salir(1);
			if (opcionString[0] == 0x1B)
				return;
		} while (!es_numero(opcionString));

		opcion = atoi(opcionString);
		
		if (opcion == 1)
			ControladorMTiempo cmt(std::move(*modelo), std::move(*actividad));
		else if (opcion == 2)
			ControladorMDescr cmd(std::move(*modelo), std::move(*actividad));
		else if (opcion == 3)
		{
			ControladorDelRegistro cdr(std::move(*modelo));
			modelo = nullptr;
			break;
		}

	} while (1);
}
