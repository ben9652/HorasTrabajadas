#include "GestorConexion.h"
#include "VistaPrincipal.h"

#ifndef __CONTROLADOR_PRINCIPAL
#define __CONTROLADOR_PRINCIPAL

class ControladorPrincipal
{
private:
	GestorConexion* conexion;
	VistaPrincipal* u;
public:
	ControladorPrincipal(const char* servidor = "localhost");
	~ControladorPrincipal();

	void ejecutarLogica(const char* servidor);
};

#endif