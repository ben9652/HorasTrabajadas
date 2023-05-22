#include "ControladorMostrarConjuntos.h"
#include <utility>

ControladorMostrarConjuntos::ControladorMostrarConjuntos(Actividad&& _modelo)
{
	vista = new VistaMostrarConjuntos();
	modelo = new Actividad();
	modelo = &_modelo;

	ejecutarLogica();
}

void ControladorMostrarConjuntos::ejecutarLogica()
{
	vista->limpiar();
	if (modelo->listaRegistrosActualizada)
	{
		modelo->actualizarTablas();
		modelo->listaRegistrosActualizada = false;
	}

	const std::vector<TextTable>& tablas = modelo->getTablasConjuntos();

	size_t cantConjuntos = tablas.size();
	if (cantConjuntos == 0)
		vista->mostrar("Aún no se filtraron los registros.");

	for (int i = 0; i < cantConjuntos; i++)
	{
		std::cout << "---------- CONJUNTO " << i + 1 << " ----------\n";

		std::cout << tablas[i] << "\n" << std::endl;
	}

	vista->ingresar(0);
}