#include "GestorConexion.h"
#include "VistaPrincipal.h"
#include "servers.h"

#ifndef __CONTROLADOR_PRINCIPAL
#define __CONTROLADOR_PRINCIPAL

class ControladorPrincipal
{
private:
	GestorConexion* conexion;
	VistaPrincipal* u;
public:
	ControladorPrincipal(const char* servidor = mysql_ip.c_str());
	ControladorPrincipal(char* usuario, char* contrasenia, const char* servidor = mysql_ip.c_str());
	~ControladorPrincipal();

	int iniciarSesion(const char* servidor = mysql_ip.c_str(), char* usuario = nullptr, char* contrasenia = nullptr);
	void ejecutarLogica(const char* servidor);
};

#endif