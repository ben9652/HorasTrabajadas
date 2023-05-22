#include "ControladorDelRegistro.h"
#include "common.h"
#include "GestorConexion.h"
#include "GestorRegistros.h"

ControladorDelRegistro::ControladorDelRegistro(Registro&& _modelo)
{
	modelo = new Registro();
	*modelo = _modelo;
	vista = new VistaDelRegistro();

	ejecutarLogica();
}

ControladorDelRegistro::~ControladorDelRegistro()
{
	delete vista;
}

void ControladorDelRegistro::ejecutarLogica()
{
	GestorConexion* gc = GestorConexion::instanciar();
	GestorRegistros* gr = GestorRegistros::instanciar();
	char* resultado;
	do
	{
		vista->limpiar();
		vista->mostrar("¿Está seguro/a que desea eliminar el registro? ");
		resultado = vista->ingresar_opcion_salir(2);
		if (resultado[0] == 0x1B)
			return;
		
		if (_strcmpi(resultado, "sí") && _strcmpi(resultado, "sÍ") && _strcmpi(resultado, "no"))
			continue;

		gr->EliminarRegistro(modelo->getIdRegistro(), modelo->getIdActividad());
		break;

	} while (true);
}
