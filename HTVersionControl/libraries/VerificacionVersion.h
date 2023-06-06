#ifndef __VERIFICACION_VERSION
#define __VERIFICACION_VERSION
#include <string>
#include <stdlib.h>

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

private:
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
	static const char* VERSION;
};

#endif