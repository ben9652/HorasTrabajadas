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
		modelo->listaRegistrosActualizada = false;
	}
	
	std::vector<ConjuntoRegistros> conjuntos = modelo->getConjuntosRegistros();
	size_t cantConjuntos = conjuntos.size();
	if (cantConjuntos == 0)
		vista->mostrar("Aún no se filtraron los registros.");

	for (int i = 0; i < cantConjuntos; i++)
	{
		std::cout << "---------- CONJUNTO " << i + 1 << " ----------\n\n";

		// Obtengo el conjunto
		ConjuntoRegistros conjunto = conjuntos[i];

		// Obtengo la cantidad de registros del conjunto
		size_t cantRegistros = conjunto.getConjuntoRegistros().size();
		for (int j = 0; j < cantRegistros; j++)
		{
			// Obtengo el registro
			Registro registro = conjunto.getConjuntoRegistros()[j];
			char* idRegistro = (char*)malloc(20);
			char* fechaCreacion = (char*)malloc(20);
			strcpy_s(idRegistro, 20, registro.getIdRegistroString());
			strcpy_s(fechaCreacion, 20, registro.getFechaCreacionString());
			vista->mostrarRegistro(idRegistro, registro.getTiempoConsumido(), fechaCreacion, registro.getDescripcion());
			vista->mostrar("\n");
		}

		std::cout << "------------------------------------------------\n\n" << std::endl;
	}

	vista->ingresar(0);
}