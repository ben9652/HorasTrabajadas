#ifndef __VERIFICACION_VERSION
#define __VERIFICACION_VERSION
#include <string>
#include <stdlib.h>
#include <fstream>

#define CLAVE_COMPROBACION_VERSION 0xFAFAFA

class VerificacionVersion
{
public:
	VerificacionVersion();

	/// <summary>
	/// Funci�n que verifica si la versi�n del programa es la m�s reciente
	/// </summary>
	/// <returns>Un booleano respondiendo si es la misma versi�n o no</returns>
	static bool verificarVersion();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	static int descargarActualizacion();

	static bool checkConnection();

	static bool existeActualizador();

	static void eliminarActualizador();

private:
	static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream);
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
	static const std::string VERSION;
	static const std::string UPDATER_NAME;
	static const std::string FILENAME;
	static std::string servidor;
};

#endif