#include "ControladorPrincipal.h"
#include "ControladorAActividad.h"
#include "ControladorSelectActividad.h"
#include "GestorActividades.h"
#include "GestorRegistros.h"
#include "GestorDatos.h"
#include "ConnectionException.h"
#include <ctime>
#include "common.h"
#include <iostream>
#include <thread>

ControladorPrincipal::ControladorPrincipal(const char* servidor)
{
	u = new VistaPrincipal();

	conexion = nullptr;

	int resultado;
	do resultado = iniciarSesion(servidor);
	while (resultado != 0);

	ejecutarLogica(servidor);
}

ControladorPrincipal::ControladorPrincipal(char* usuario, char* contrasenia, const char* servidor)
{
	u = new VistaPrincipal();

	conexion = nullptr;

	int resultado;
	do resultado = iniciarSesion(servidor, usuario, contrasenia);
	while (resultado != 0);

	ejecutarLogica(servidor);
}

ControladorPrincipal::~ControladorPrincipal()
{
	if (conexion != nullptr)
		conexion->cerrarConexion();
}

int ControladorPrincipal::iniciarSesion(const char* servidor, char* usuario, char* contrasenia)
{
	if (!usuario && !contrasenia)
	{
		u->limpiar();

		u->mostrar("Usuario: ");
		usuario = u->ingresar(50);

		u->mostrar("Contrase�a: ");
		contrasenia = u->ingresar_password(100);
	}

	try {
		conexion = GestorConexion::abrirConexion(usuario, contrasenia, servidor);
	}
	catch (ConnectionException e) {
		u->mostrar("\n");
		u->mostrar(e.what());
		u->mostrar("\n\nPresione ENTER para intentar otra vez.\n");
		u->ingresar(0);
		return -1;
	}

	return 0;
}

void ControladorPrincipal::ejecutarLogica(const char* servidor)
{

	GestorActividades* ga = GestorActividades::instanciar();
	GestorRegistros* gr = GestorRegistros::instanciar();
	GestorDatos* gd = GestorDatos::instanciar();

	sql::ResultSet* res = nullptr;
	sql::Statement* stmt;

	sql::SQLString consulta;
	sql::SQLString condicion_usuario = "";
	if (strcmp(conexion->getUsuario(), "keanu") == 0)
		condicion_usuario = " WHERE idActividad = 1";

	// Obtengo la cantidad de filas que hay en la tabla Actividades
	stmt = conexion->createStatement();
	consulta = "SELECT COUNT(*) FROM Actividades";
	if (condicion_usuario.length() != 0)
		consulta += condicion_usuario;
	try {
		res = stmt->executeQuery(consulta);
	}
	catch (sql::SQLException e) {
		std::cout << e.what() << std::endl;
	}
	res->next();
	gd->asignarCantidadActividadesEnBD(res->getUInt(1));

	// Obtengo la cantidad de filas que hay en la tabla Registros
	stmt = conexion->createStatement();
	consulta = "SELECT COUNT(*) FROM Registros";
	if (condicion_usuario.length() != 0)
		consulta += condicion_usuario;
	try {
		res = stmt->executeQuery(consulta);
	}
	catch (sql::SQLException e) {
		std::cout << e.what() << std::endl;
	}
	res->next();
	gd->asignarCantidadRegistrosEnBD(res->getUInt(1));

	mostrarCursor(false);
	u->limpiar();
	std::thread cargaDeDatos(VistaPrincipal::mostrarCargaDeDatos);

	// Obtengo los datos de la base de datos
	ga->Dame(conexion->getUsuario());
	gr->Dame(conexion->getUsuario());

	cargaDeDatos.join();

	delete stmt;
	delete res;

	mostrarCursor(true);

	unsigned int opcion = 0;
	char* opcion_cadena;
	do
	{
		do
		{
			u->limpiar();
			u->mostrar("1- Agregar actividad\n2- Listar actividades\n3- Salir\n\n");
			opcion_cadena = u->ingresar(1);
		} while (!es_numero(opcion_cadena));

		opcion = atoi(opcion_cadena);

		if (opcion == 1)
			ControladorAActividad caa;
		else if (opcion == 2)
			ControladorSelectActividad csa;
		else if (opcion == 3)
			break;
		else
			continue;

	} while (1);
}
