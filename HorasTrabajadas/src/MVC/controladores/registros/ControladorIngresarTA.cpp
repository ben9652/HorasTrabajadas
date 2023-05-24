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
			vista->mostrar("\nFormato incorrecto.\nEl formato puede ser:\n- <numero>(s): se expresa simplemente en segundos\n- <numero>m: se expresa en minutos\n- <numero>m<numero>s: se expresa en minutos y segundos");
			vista->ingresar(0);
			continue;
		}

		modelo->agruparRegistros(tiempoFiltro);
		modelo->listaRegistrosActualizada = true;
		break;
	} while (true);
}