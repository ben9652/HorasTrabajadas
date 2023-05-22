#ifndef _CONTROLADOR_MODIFICAR_DESCRIPCION_
#define _CONTROLADOR_MODIFICAR_DESCRIPCION_
#include "GestorConexion.h"
#include "Registro.h"
#include "Actividad.h"
#include "VistaMTiempo.h"

class ControladorMDescr
{
private:
	GestorConexion* conector;
	Registro* modelo;
	Actividad* actividad;
	VistaMTiempo* vista;

	static char* descripcionString;
	static size_t index_descripcionString;
	static size_t teclas_apretadas_descripcion;
	// Esta variable sirve para conservar lo escrito si: 1) se llegara a ingresar mal, o 2) si se vuelve al menú anterior
	static bool texto_escrito_descr;

public:
	ControladorMDescr(Registro&& _modelo, Actividad&& _actividad);
	~ControladorMDescr();

	void ejecutarLogica();
};

#endif