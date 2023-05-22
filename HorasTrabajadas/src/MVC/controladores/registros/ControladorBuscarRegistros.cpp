#include "ControladorBuscarRegistros.h"
#include "ControladorFiltroID.h"
#include "ControladorFiltroTiempo.h"
#include "ControladorFiltroFecha.h"
#include "ControladorFiltroDescr.h"
#include "ControladorAccionBReg.h"
#include "common.h"
#include <utility>

ControladorBuscarRegistros::ControladorBuscarRegistros(Actividad&& _modelo)
{
	conector = GestorConexion::instanciar();
	modelo = new Actividad();
	*modelo = _modelo;
	vista = new VistaBuscarRegistros();

	ejecutarLogica();
}

ControladorBuscarRegistros::~ControladorBuscarRegistros() {}

void ControladorBuscarRegistros::ejecutarLogica()
{
	char* opcionString;
	int opcion;
	do
	{
		do
		{
			vista->limpiar();
			vista->MenuBuscarRegistros();
			opcionString = vista->ingresar_opcion_salir(1);
			if (opcionString[0] == 0x1B)
				return;
		} while (!es_numero(opcionString));

		opcion = atoi(opcionString);

		if (opcion == 1)
		{
			ControladorFiltroID cfid(std::move(*modelo));
			cfid.ejecutarLogica();
		}
		else if (opcion == 2)
		{
			ControladorFiltroTiempo cft;
			cft.ejecutarLogica();
		}
		else if (opcion == 3)
		{
			ControladorFiltroFecha cff;
			cff.ejecutarLogica();
		}
		else if (opcion == 4)
		{
			ControladorFiltroDescr cfd;
			cfd.ejecutarLogica();
		}
		else if (opcion == 5)
		{
			ControladorFiltroID cfid;
			ControladorFiltroTiempo cft;
			ControladorFiltroFecha cff;
			ControladorFiltroDescr cfd;
			cfid.limpiarFiltro();
			cft.limpiarFiltro();
			cff.limpiarFiltro();
			cfd.limpiarFiltro();
		}
		else if (opcion == 6)
		{
			ControladorAccionBReg cabr(std::move(*modelo));
		}

	} while (1);
}
