#include "ControladorMTiempo.h"
#include "ConnectionException.h"
#include <string>
#include <sstream>
#include <ctype.h>

char* ControladorMTiempo::tiempoString = (char*)malloc(10);
size_t ControladorMTiempo::index_tiempoString = 0;
size_t ControladorMTiempo::teclas_apretadas_tiempoString = 0;
bool ControladorMTiempo::texto_escrito_tiempo = false;

int ControladorMTiempo::tiempoIngresadoCorrectamente()
{
	std::string tiempo = tiempoString;
	std::stringstream ss(tiempo);
	std::string token;

	int resultado = -1;
	int minutos = 0;
	int segundos = 0;

	size_t posicion_m;
	size_t posicion_s;
	if ((tiempo.find('m') != std::string::npos) && tiempo.find('s') != std::string::npos)
	{
		// Extracción de horas
		std::getline(ss, token, 'm');
		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i])) return -1;
		}
		minutos = stoi(token);

		std::getline(ss, token, 'm');
		if (posicion_m = token.find('s'))
			token = token.erase(posicion_m, 1);

		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i])) return -1;
		}
		segundos = stoi(token);

		segundos += minutos * 60;
		resultado = segundos;
	}
	else if ((posicion_m = tiempo.find('m')) != std::string::npos)
	{
		std::getline(ss, token, 'm');
		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i])) return -1;
		}

		resultado = stoi(token) * 60;
	}
	else if ((posicion_s = tiempo.find('s')) != std::string::npos)
	{
		std::getline(ss, token, 's');
		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i])) return -1;
		}

		resultado = stoi(token);
	}
	else
	{
		for (unsigned int i = 0; i < tiempo.size(); i++)
		{
			if (!isdigit(tiempo[i])) return -1;
		}

		resultado = stoi(tiempo);
	}

	return resultado;
}

ControladorMTiempo::ControladorMTiempo(Registro&& _modelo, Actividad&& _actividad)
{
	conector = GestorConexion::instanciar();
	modelo = new Registro();
	modelo = &_modelo;
	actividad = new Actividad();
	actividad = &_actividad;
	vista = new VistaMTiempo();
	tiempoSegundos = 0;

	ejecutarLogica();
}

ControladorMTiempo::~ControladorMTiempo()
{
	delete vista;
}

void ControladorMTiempo::ejecutarLogica()
{
	char resultado;
	do
	{
		vista->limpiar();
		vista->mostrar("Tiempo actual: ");
		vista->mostrar(modelo->getTiempoConsumido());
		vista->mostrar("\nTiempo nuevo: ");
		if (texto_escrito_tiempo)
			vista->mostrar(tiempoString);
		else
		{
			memset(tiempoString, 0, 10);
			index_tiempoString = 0;
			teclas_apretadas_tiempoString = 0;
		}

		resultado = vista->ingresar_con_memoria(9, tiempoString, index_tiempoString, teclas_apretadas_tiempoString);

		if (resultado == 0x1B)
		{
			texto_escrito_tiempo = true;
			return;
		}

		if ((tiempoSegundos = tiempoIngresadoCorrectamente()) == -1)
		{
			vista->mostrar("Formato incorrecto. Inténtelo de nuevo.");
			vista->ingresar(0);
			texto_escrito_tiempo = true;
			continue;
		}
		else if (tiempoSegundos == 0)
		{
			vista->mostrar("El tiempo ingresado no puede ser 0. Inténtelo de nuevo.");
			vista->ingresar(0);
			texto_escrito_tiempo = false;
			continue;
		}

		if (resultado == 0)
		{
			texto_escrito_tiempo = false;
			break;
		}

	} while (true);

	unsigned int registroTiempoViejo = modelo->getSegundosConsumidos();
	actividad->RegistroModificaTiempo(registroTiempoViejo, tiempoSegundos);
	modelo->ModificarTiempo(tiempoSegundos);
}
