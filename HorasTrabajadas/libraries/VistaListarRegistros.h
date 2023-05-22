#ifndef __VISTA_LISTAR_REGISTROS_
#define __VISTA_LISTAR_REGISTROS
#include "GestorVistas.h"
#include "VistaBase.h"
#include <TextTable.h>
#include <stdlib.h>

class VistaListarRegistros : public VistaBase
{
private:
	TextTable* tabla;
	bool tablaConElementos;
public:
	VistaListarRegistros();

	bool tablaTieneElementos();
	void limpiarTabla();
	void addFila(const char* ID, const char* tiempoConsumido, const char* fechaCreacion, const char* descripcion);
	void mostrarTabla();
};

#endif