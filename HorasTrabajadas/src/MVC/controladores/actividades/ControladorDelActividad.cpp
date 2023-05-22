#include "ControladorDelActividad.h"
#include "GestorActividades.h"

ControladorDelActividad::ControladorDelActividad(Actividad&& _modelo)
{
	vista = new VistaDelActividad();
	modelo = &_modelo;
}

bool ControladorDelActividad::ejecutarLogica()
{
	GestorActividades* ga = GestorActividades::instanciar();

	bool resultado_operacion_borrado = false;
	sql::ResultSet* resultado;

	vista->limpiar();
	resultado = ga->BorrarActividad(modelo->getIdActividad());
	sql::SQLString mensaje_devuelto = resultado->getString(1);
	if (mensaje_devuelto == "¡Actividad eliminada con éxito!")
		resultado_operacion_borrado = true;
	
	vista->mostrar(mensaje_devuelto.c_str());
	vista->ingresar(0);

	return resultado_operacion_borrado;
}