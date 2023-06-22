#include "ControladorDelActividad.h"
#include "GestorActividades.h"
#include "common.h"

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
#ifdef FUNCIONA_CHARACTER_SET_LATIN
	if (mensaje_devuelto == "¡Actividad eliminada con éxito!")
		resultado_operacion_borrado = true;
	vista->mostrar(mensaje_devuelto.c_str());
#else
	const char* mensaje_exito = utf8_to_ascii("¡Actividad eliminada con éxito!");
	if (!strcmp(utf8_to_ascii(mensaje_devuelto.c_str()), mensaje_exito))
		resultado_operacion_borrado = true;
	vista->mostrar(utf8_to_ascii(mensaje_devuelto.c_str()));
#endif
	
	vista->ingresar(0);

	return resultado_operacion_borrado;
}