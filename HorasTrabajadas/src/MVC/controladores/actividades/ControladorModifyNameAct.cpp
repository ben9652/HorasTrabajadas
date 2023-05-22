#include "ControladorModifyNameAct.h"
#include "GestorActividades.h"

ControladorModifyNameAct::ControladorModifyNameAct(Actividad&& _modelo)
{
	vista = new VistaModifyNameAct();
	modelo = &_modelo;
	
	ejecutarLogica();
}

void ControladorModifyNameAct::ejecutarLogica()
{
	GestorActividades* ga = GestorActividades::instanciar();

	char* resultado;

	vista->limpiar();
	vista->mostrar("Ingrese un nuevo nombre para la actividad: ");
	resultado = vista->ingresar_opcion_salir(100);
	if (resultado[0] == 0x1B)
		return;

	sql::ResultSet* res = ga->ModificarActividad(modelo->getIdActividad(), resultado);

	vista->mostrar("\n");
	vista->mostrar(res->getString(1).c_str());
	vista->ingresar(0);
}