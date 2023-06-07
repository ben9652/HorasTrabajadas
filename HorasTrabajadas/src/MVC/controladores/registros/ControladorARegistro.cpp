#include "ControladorARegistro.h"
#include "GestorActividades.h"
#include <string>
#include <sstream>
#include <ctype.h>
#include "common.h"
#include <ConnectionException.h>

char* ControladorARegistro::tiempoString = (char*)malloc(10);
size_t ControladorARegistro::index_tiempoString = 0;
size_t ControladorARegistro::teclas_apretadas_tiempoString = 0;
bool ControladorARegistro::texto_escrito_tiempo = false;

char* ControladorARegistro::descripcionString = (char*)malloc(256);
size_t ControladorARegistro::index_descripcionString = 0;
size_t ControladorARegistro::teclas_apretadas_descripcion = 0;
bool ControladorARegistro::texto_escrito_descr = false;

ControladorARegistro::ControladorARegistro(Actividad&& _actividad)
{
	conector = GestorConexion::instanciar();
	modelo = GestorRegistros::instanciar();
	actividad = new Actividad();
	actividad = &_actividad;
	vista = new VistaARegistro();
	tiempoSegundos = 0;

	ejecutarLogica();
}

ControladorARegistro::~ControladorARegistro()
{
	delete vista;
}

size_t ControladorARegistro::cantidadRegistros()
{
	return modelo->cantidadRegistrosPorActividad(actividad->getIdActividad());
}

Registro& ControladorARegistro::obtenerRegistroPorId(int idRegistro, int idActividad)
{
	return modelo->obtenerRegistroPorId(idRegistro, idActividad);
}

Registro& ControladorARegistro::obtenerRegistroPorIndice(int index)
{
	return modelo->obtenerRegistroPorIndice(index);
}

void ControladorARegistro::ejecutarLogica()
{
	char resultado;
	do
	{
		vista->limpiar();
		vista->mostrar("Tiempo: ");
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

		if ((tiempoSegundos = tiempoIngresadoCorrectamente(tiempoString)) == -1)
		{
			vista->mostrar("\nFormato incorrecto.\nEl formato puede ser:\n- <numero>(s): se expresa simplemente en segundos\n- <numero>m: se expresa en minutos\n- <numero>m<numero>s: se expresa en minutos y segundos");
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

		do
		{
			vista->irXY(0, 2);
			vista->mostrar("Descripción: ");
			if (texto_escrito_descr)
				vista->mostrar(descripcionString);
			else
			{
				memset(descripcionString, 0, 256);
				index_descripcionString = 0;
				teclas_apretadas_descripcion = 0;
			}

			resultado = vista->ingresar_con_memoria(255, descripcionString, index_descripcionString, teclas_apretadas_descripcion);

			if (resultado == 0x1B)
			{
				texto_escrito_descr = true;
				texto_escrito_tiempo = true;
			}
			break;
		} while (true);

		if (resultado == 0)
		{
			texto_escrito_tiempo = false;
			texto_escrito_descr = false;
			break;
		}

	} while (true);

	if (resultado == 0)
	{
		try {
			modelo->AgregarRegistro(actividad->getIdActividad(), (unsigned int)tiempoSegundos, descripcionString);
		}
		catch (ConnectionException ce) {
			std::cout << ce.what() << std::endl;
			std::cin.get();
		}
	}
}
