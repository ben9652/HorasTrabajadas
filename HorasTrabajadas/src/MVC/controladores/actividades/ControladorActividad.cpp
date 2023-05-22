#include "ControladorActividad.h"
#include "ControladorARegistro.h"
#include "ControladorListarRegistros.h"
#include "ControladorBuscarRegistros.h"
#include "ControladorIngresarTA.h"
#include "ControladorMostrarConjuntos.h"
#include "ControladorModifyNameAct.h"
#include "ControladorDelActividad.h"
#include "common.h"
#include <utility>

ControladorActividad::ControladorActividad(Actividad&& _modelo)
{
	conector = GestorConexion::instanciar();
	modelo = new Actividad();
	modelo = &_modelo;
	vista = new VistaActividad(this);
	
	ejecutarLogica();
}

ControladorActividad::~ControladorActividad()
{
	delete vista;
}

const char* ControladorActividad::getNombreActividad() const
{
	return modelo->getNombre();
}

const char* ControladorActividad::getTiempoTotal() const
{
	return modelo->getTiempoConsumido();
}

void ControladorActividad::ejecutarLogica()
{
	char* opcionString;
	int opcion;
	do
	{
		do
		{
			vista->limpiar();
			vista->MenuActividad();
			opcionString = vista->ingresar_opcion_salir(1);
			if (opcionString[0] == 0x1B)
				return;
		} while (!es_numero(opcionString));

		opcion = atoi(opcionString);

		if (opcion == 1)
			ControladorARegistro car(std::move(*modelo));
		else if (opcion == 2)
			ControladorListarRegistros clr(std::move(*modelo));
		else if (opcion == 3)
			ControladorBuscarRegistros cbr(std::move(*modelo));
		else if (opcion == 4)
			ControladorIngresarTA cita(std::move(*modelo));
		else if (opcion == 5)
			ControladorMostrarConjuntos cmc(std::move(*modelo));
		else if (opcion == 6)
			ControladorModifyNameAct cmna(std::move(*modelo));
		else if (opcion == 7)
		{
			ControladorDelActividad cda(std::move(*modelo));
			if (cda.ejecutarLogica())
			{
				modelo = nullptr;
				break;
			}
		}
	} while (1);
}