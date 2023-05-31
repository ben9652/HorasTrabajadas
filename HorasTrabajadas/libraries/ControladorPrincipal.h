#include "GestorConexion.h"
#include "VistaPrincipal.h"

#ifndef __CONTROLADOR_PRINCIPAL
#define __CONTROLADOR_PRINCIPAL

extern char* user;
extern char* password;

class ControladorPrincipal
{
private:
	GestorConexion* conexion;
	VistaPrincipal* u;
public:
	ControladorPrincipal(const char* servidor = "localhost");
	ControladorPrincipal(char* usuario, char* contrasenia, const char* servidor = "localhost");
	~ControladorPrincipal();

	int iniciarSesion(const char* servidor = "localhost", char* usuario = nullptr, char* contrasenia = nullptr);
	void ejecutarLogica(const char* servidor);
};

#endif