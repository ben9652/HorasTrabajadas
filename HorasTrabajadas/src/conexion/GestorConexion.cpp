#include <iostream>
#include "GestorConexion.h"
#include "ConnectionException.h"

const char* GestorConexion::ERROR_DRIVER = "No se encontr� la librer�a para el driver de MySQL";

const char* GestorConexion::ABRIR_CONEXION_ERROR = "Error al abrir la conexi�n. Revisar: \n\t* que est� levantado el servicio\n\t* que sean correctos el usuario y clave especificados";

const char* GestorConexion::ERROR_CONEXION = "Se perdi� la conexi�n con el servidor o base de datos";

const char* GestorConexion::ERROR_STMT = "No se pudo preparar la consulta";

const char* GestorConexion::ERROR_CONSULTA = "No se pudo hacer la consulta";

const unsigned short GestorConexion::PUERTO = 3306;

const char* GestorConexion::BD = "HorasTrabajadas";

GestorConexion* GestorConexion::gestor;

GestorConexion::GestorConexion(const char* usuario, const char* clave, const char* servidor)
{
	this->usuario = usuario;

	sql::ConnectOptionsMap connection_properties;

	connection_properties["hostName"] = servidor;
	connection_properties["userName"] = usuario;
	connection_properties["password"] = clave;
	connection_properties["schema"] = "HorasTrabajadas";
	connection_properties["port"] = 3306;
	connection_properties["OPT_RECONNECT"] = true;
	connection_properties["characterSetResults"] = "latin1";

	try {
		driver = get_driver_instance();
		conector = driver->connect(connection_properties);
	}
	catch (sql::SQLException e) {
		throw ConnectionException(ABRIR_CONEXION_ERROR);
	}
}

GestorConexion::~GestorConexion()
{
	if (conector != nullptr)
		cerrarConexion();
}

GestorConexion* GestorConexion::abrirConexion(const char* usuario, const char* clave, const char* servidor)
{
	if (gestor == nullptr)
		gestor = new GestorConexion(usuario, clave, servidor);
	return gestor;
}

GestorConexion* GestorConexion::instanciar()
{
	return gestor;
}

sql::Statement* GestorConexion::createStatement()
{
	if (conector != nullptr)
		return this->conector->createStatement();
	else
		throw sql::SQLException(ERROR_CONEXION);
}

sql::PreparedStatement* GestorConexion::prepareStatement(const sql::SQLString& sql)
{
	if (conector != nullptr)
		return this->conector->prepareStatement(sql);
	else
		throw sql::SQLException(ERROR_CONEXION);
}

void GestorConexion::cerrarConexion()
{
	if (conector != nullptr)
	{
		this->conector->close();
		this->conector = nullptr;
	}
	else
		throw sql::SQLString(ERROR_CONEXION);
}