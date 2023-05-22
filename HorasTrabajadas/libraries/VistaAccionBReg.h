#ifndef __VISTA_ACCION_BUSCAR_REGISTRO_
#define __VISTA_ACCION_BUSCAR_REGISTRO_
#include "VistaBase.h"
#include <TextTable.h>

class VistaAccionBReg : public VistaBase
{
private:
	TextTable* resultado_busqueda;
	bool tablaConElementos;
public:
	VistaAccionBReg();
	~VistaAccionBReg();

	bool tablaTieneElementos();
	void limpiarTabla();
	void addFila(const char* ID, const char* tiempoConsumido, const char* fechaCreacion, const char* descripcion);
	void mostrarTabla();
};

#endif