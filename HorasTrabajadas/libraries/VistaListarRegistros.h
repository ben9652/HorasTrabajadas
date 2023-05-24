#ifndef __VISTA_LISTAR_REGISTROS_
#define __VISTA_LISTAR_REGISTROS_
#include "GestorVistas.h"
#include "VistaBase.h"
#include "Registro.h"
#include <stdlib.h>

class VistaListarRegistros : public VistaBase
{
private:
	const char* formatear_texto(const char* input);
public:
	void mostrarRegistro(const char* ID, const char* tiempoConsumido, const char* fechaCreacion, const char* descripcion);
};

#endif