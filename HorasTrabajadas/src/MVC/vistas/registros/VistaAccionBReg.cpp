#include "VistaAccionBReg.h"
#include "common.h"

VistaAccionBReg::VistaAccionBReg()
{
	SetConsoleBufferSize(1000, 20000);
	resultado_busqueda = new TextTable('-', '|', '+');
	resultado_busqueda->add("ID");
	resultado_busqueda->add("Tiempo consumido");
	resultado_busqueda->add("Fecha de creación");
	resultado_busqueda->add("Descripción");
	resultado_busqueda->endOfRow();

	resultado_busqueda->setAlignment(2, TextTable::Alignment::LEFT);
}

VistaAccionBReg::~VistaAccionBReg()
{
	delete resultado_busqueda;
}

bool VistaAccionBReg::tablaTieneElementos()
{
	return tablaConElementos;
}

void VistaAccionBReg::limpiarTabla()
{
	if (resultado_busqueda != nullptr && tablaConElementos)
		delete resultado_busqueda;

	if (tablaConElementos)
	{
		resultado_busqueda = new TextTable('-', '|', '+');
		resultado_busqueda->add("ID");
		resultado_busqueda->add("Tiempo consumido");
		resultado_busqueda->add("Fecha de creación");
		resultado_busqueda->add("Descripción");
		resultado_busqueda->endOfRow();

		resultado_busqueda->setAlignment(2, TextTable::Alignment::LEFT);
	}

	tablaConElementos = false;
}

void VistaAccionBReg::addFila(const char* ID, const char* tiempoConsumido, const char* fechaCreacion, const char* descripcion)
{
	if (!tablaConElementos)
		tablaConElementos = true;

	resultado_busqueda->add(ID);
	resultado_busqueda->add(tiempoConsumido);
	resultado_busqueda->add(fechaCreacion);
	resultado_busqueda->add(utf8_to_ascii((char*)descripcion));
	resultado_busqueda->endOfRow();
}

void VistaAccionBReg::mostrarTabla()
{
	std::cout << *resultado_busqueda << std::endl;
}
