#ifndef __GESTOR_CONEXION
#define __GESTOR_CONEXION

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

class GestorConexion
{
public:
	~GestorConexion();

	static const char* ERROR_DRIVER;
	static const char* ABRIR_CONEXION_ERROR;
	static const char* ERROR_CONEXION;
	static const char* ERROR_STMT;
	static const char* ERROR_CONSULTA;

	// Abrir una conexión con el servidor SQL
	static GestorConexion* abrirConexion(const char* usuario, const char* clave, const char* servidor);

	static GestorConexion* instanciar();

	// Se crea una instancia del objeto encargado del armado de una consulta SQL
	sql::Statement* createStatement();

	// Esto nos sirve para preparar una consulta de la que no esperamos un resultado
	sql::PreparedStatement* prepareStatement(const sql::SQLString& sql);

	// Cerrar la conexión con el servidor SQL
	void cerrarConexion();

	// Obtener el nombre del usuario con el que se abrió la conexión
	const char* getUsuario() const;

	// Obtener el nombre del servidor con el que se abrió la conexión
	const char* getServidor() const;

private:
	GestorConexion(const char* usuario, const char* clave, const char* servidor);

	static const unsigned short PUERTO;
	static const char* BD;
	const char* usuario;

	static GestorConexion* gestor;
	sql::Connection* conector;
	sql::Driver* driver;
};

#endif