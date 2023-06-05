#include "ControladorMDescr.h"
#include "ConnectionException.h"
#include "common.h"
#include <string>

char* ControladorMDescr::descripcionString = (char*)malloc(256);
size_t ControladorMDescr::index_descripcionString = 0;
size_t ControladorMDescr::teclas_apretadas_descripcion = 0;
bool ControladorMDescr::texto_escrito_descr = false;

ControladorMDescr::ControladorMDescr(Registro&& _modelo, Actividad&& _actividad)
{
	conector = GestorConexion::instanciar();
	modelo = new Registro();
	modelo = &_modelo;
	actividad = new Actividad();
	actividad = &_actividad;
	vista = new VistaMTiempo();

	ejecutarLogica();
}

ControladorMDescr::~ControladorMDescr()
{
	delete vista;
}

void ControladorMDescr::ejecutarLogica()
{
	char resultado;
	do
	{
		vista->limpiar();
		vista->mostrar("Descripción actual: ");
		vista->mostrar(modelo->getDescripcion());
		vista->mostrar("\nDescripción nueva: ");
		if (texto_escrito_descr)
			vista->mostrar(descripcionString);
		else
		{
			memset(descripcionString, 0, 10);
			index_descripcionString = 0;
			teclas_apretadas_descripcion = 0;
		}

		resultado = vista->ingresar_con_memoria(255, descripcionString, index_descripcionString, teclas_apretadas_descripcion);

		if (resultado == 0x1B)
		{
			texto_escrito_descr = true;
			return;
		}

		if (resultado == 0)
		{
			texto_escrito_descr = false;
			break;
		}

	} while (true);

	if(strlen(descripcionString) > 0)
		modelo->ModificarDescripcion(descripcionString);
}
