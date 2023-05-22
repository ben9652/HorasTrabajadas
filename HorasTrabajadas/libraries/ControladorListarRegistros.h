#ifndef __CONTROLADOR_LISTAR_REGISTROS_
#define __CONTROLADOR_LISTAR_REGISTROS_
#include "ControladorPrincipal.h"
#include "GestorRegistros.h"
#include "Actividad.h"

class VistaListarRegistros;

class ControladorListarRegistros
{
private:
	GestorConexion* conector;
	GestorRegistros* modelo;
	Actividad* actividad;
	VistaListarRegistros* vista;
public:
	ControladorListarRegistros(Actividad&& _actividad);
	~ControladorListarRegistros();

	size_t cantidadRegistros();
	Registro& obtenerRegistroPorId(int idRegistro, int idActividad);
	Registro& obtenerRegistroPorIndice(int index);

	void ejecutarLogica();
};

#include "VistaListarRegistros.h"

#endif