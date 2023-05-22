#ifndef __CONTROLADOR_AGREGAR_REGISTRO_
#define __CONTROLADOR_AGREGAR_REGISTRO_
#include "ControladorPrincipal.h"
#include "GestorRegistros.h"
#include "VistaARegistro.h"
#include "Actividad.h"

class ControladorARegistro
{
private:
	GestorConexion* conector;
	GestorRegistros* modelo;
	Actividad* actividad;
	VistaARegistro* vista;

	int tiempoSegundos;

	static char* tiempoString;
	static size_t index_tiempoString;
	static size_t teclas_apretadas_tiempoString;
	// Esta variable sirve para conservar lo escrito si: 1) se llegara a ingresar mal, o 2) si se vuelve al menú anterior
	static bool texto_escrito_tiempo;

	static char* descripcionString;
	static size_t index_descripcionString;
	static size_t teclas_apretadas_descripcion;
	// Esta variable sirve para conservar lo escrito si: 1) se llegara a ingresar mal, o 2) si se vuelve al menú anterior
	static bool texto_escrito_descr;

public:
	ControladorARegistro(Actividad&& _actividad);
	~ControladorARegistro();

	size_t cantidadRegistros();
	Registro& obtenerRegistroPorId(int idRegistro, int idActividad);
	Registro& obtenerRegistroPorIndice(int index);

	void ejecutarLogica();
};

#endif