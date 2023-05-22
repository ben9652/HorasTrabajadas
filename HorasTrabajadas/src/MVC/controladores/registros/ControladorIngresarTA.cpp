#include "ControladorIngresarTA.h"
#include "ConjuntoRegistros.h"
#include "common.h"

ControladorIngresarTA::ControladorIngresarTA(Actividad&& actividad)
{
	vista = new VistaIngresarTA();
	modelo = &actividad;

	ejecutarLogica();
}

void ControladorIngresarTA::ejecutarLogica()
{
	char* tiempoFiltroString;
	int tiempoFiltro;
	do
	{
		vista->limpiar();
		vista->mostrar("Ingresar el tiempo de filtro deseado: ");
		tiempoFiltroString = vista->ingresar_opcion_salir(20);
		if (tiempoFiltroString[0] == 0x1B)
			return;
		if ((tiempoFiltro = tiempoIngresadoCorrectamente(tiempoFiltroString)) == -1)
		{
			vista->limpiar();
			vista->mostrar("El formato del tiempo ingresado no es correcto.");
			vista->ingresar(0);
			continue;
		}

		modelo->agruparRegistros(tiempoFiltro);
		modelo->listaRegistrosActualizada = true;
		break;
	} while (true);
}