#ifndef __CONTROLADOR_ACCION_BUSCAR_REGISTRO_
#define __CONTROLADOR_ACCION_BUSCAR_REGISTRO_
#include "VistaAccionBReg.h"
#include "Actividad.h"
#include <unordered_map>

class ControladorAccionBReg
{
private:
	VistaAccionBReg* vista;
	Actividad* modelo;
	std::unordered_map<int, int> indices_registros_encontrados;

	sql::PreparedStatement* hacerBusqueda();
	sql::PreparedStatement* verificarNoErrores();
public:
	ControladorAccionBReg(Actividad&& _modelo);
	~ControladorAccionBReg();

	void ejecutarLogica();
};

#endif