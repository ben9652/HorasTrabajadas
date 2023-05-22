#ifndef __CONTROLADOR_REGISTRO_
#define __CONTROLADOR_REGISTRO_
#include "ControladorPrincipal.h"
#include "GestorRegistros.h"
#include "Actividad.h"
#include "VistaRegistro.h"

class ControladorRegistro
{
private:
	GestorConexion* conector;
	Registro* modelo;
	Actividad* actividad;
	VistaRegistro* vista;

	static char* descripcionString;
	static size_t index_descripcionString;
	static size_t teclas_apretadas_descripcion;
	// Esta variable sirve para conservar lo escrito si: 1) se llegara a ingresar mal, o 2) si se vuelve al menú anterior
	static bool texto_escrito_descr;
public:
	ControladorRegistro(Registro&& _modelo, Actividad&& _actividad);
	~ControladorRegistro();

	void ejecutarLogica();
};

#endif