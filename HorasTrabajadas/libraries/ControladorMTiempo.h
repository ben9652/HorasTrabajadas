#ifndef _CONTROLADOR_MODIFICAR_TIEMPO_CONSUMIDO_
#define _CONTROLADOR_MODIFICAR_TIEMPO_CONSUMIDO_
#include "GestorConexion.h"
#include "Registro.h"
#include "Actividad.h"
#include "VistaMTiempo.h"

class ControladorMTiempo
{
private:
	GestorConexion* conector;
	Registro* modelo;
	Actividad* actividad;
	VistaMTiempo* vista;

	int tiempoSegundos;

	static char* tiempoString;
	static size_t index_tiempoString;
	static size_t teclas_apretadas_tiempoString;
	// Esta variable sirve para conservar lo escrito si: 1) se llegara a ingresar mal, o 2) si se vuelve al menú anterior
	static bool texto_escrito_tiempo;

	int tiempoIngresadoCorrectamente();

public:
	ControladorMTiempo(Registro&& _modelo, Actividad&& _actividad);
	~ControladorMTiempo();

	void ejecutarLogica();
};

#endif