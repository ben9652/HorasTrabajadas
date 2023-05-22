#ifndef __CONTROLADOR_MOSTRAR_CONJUNTOS_DE_REGISTROS
#define __CONTROLADOR_MOSTRAR_CONJUNTOS_DE_REGISTROS
#include "VistaMostrarConjuntos.h"
#include "Actividad.h"

class ControladorMostrarConjuntos
{
private:
	VistaMostrarConjuntos* vista;
	Actividad* modelo;

public:
	ControladorMostrarConjuntos(Actividad&& _modelo);

	void ejecutarLogica();
};

#endif