#include "VistaListarRegistros.h"
#include "common.h"

VistaListarRegistros::VistaListarRegistros()
{
	SetConsoleBufferSize(1000, 20000);
	tabla = new TextTable('-','|','+');
	tabla->add("ID");
	tabla->add("Tiempo consumido");
	tabla->add("Fecha de creación");
	tabla->add("Descripción");
	tabla->endOfRow();

	tabla->setAlignment(2, TextTable::Alignment::LEFT);

	tablaConElementos = false;
}

bool VistaListarRegistros::tablaTieneElementos()
{
	return tablaConElementos;
}

void VistaListarRegistros::limpiarTabla()
{
	if(tabla != nullptr && tablaConElementos)
		delete tabla;

	if (tablaConElementos)
	{
		tabla = new TextTable('-', '|', '+');
		tabla->add("ID");
		tabla->add("Tiempo consumido");
		tabla->add("Fecha de creación");
		tabla->add("Descripción");
		tabla->endOfRow();

		tabla->setAlignment(2, TextTable::Alignment::LEFT);
	}

	tablaConElementos = false;
}

void VistaListarRegistros::addFila(const char* ID, const char* tiempoConsumido, const char* fechaCreacion, const char* descripcion)
{
	if (!tablaConElementos)
		tablaConElementos = true;

	tabla->add(ID);
	tabla->add(tiempoConsumido);
	tabla->add(fechaCreacion);
	tabla->add(utf8_to_ascii((char*)descripcion));
	tabla->endOfRow();
}

void VistaListarRegistros::mostrarTabla()
{
	std::cout << *tabla << std::endl;
}
