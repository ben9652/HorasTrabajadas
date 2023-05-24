#include "ControladorListarRegistros.h"
#include "ControladorRegistro.h"
#include "ConnectionException.h"
#include "TreeException.h"
#include <stdlib.h>
#include "Registro.h"
#include "common.h"
#include <utility>

ControladorListarRegistros::ControladorListarRegistros(Actividad&& _actividad)
{
	conector = GestorConexion::instanciar();
	modelo = GestorRegistros::instanciar();
	actividad = new Actividad();
	actividad = &_actividad;
	vista = new VistaListarRegistros();

	ejecutarLogica();
}

ControladorListarRegistros::~ControladorListarRegistros()
{
	delete vista;
}

size_t ControladorListarRegistros::cantidadRegistros()
{
	return modelo->cantidadRegistrosPorActividad(actividad->getIdActividad());
}

Registro& ControladorListarRegistros::obtenerRegistroPorId(int idRegistro, int idActividad)
{
	return modelo->obtenerRegistroPorId(idRegistro, idActividad);
}

Registro& ControladorListarRegistros::obtenerRegistroPorIndice(int index)
{
	return modelo->obtenerRegistroPorIndice(index);
}

void ControladorListarRegistros::ejecutarLogica()
{
	int idActividad = actividad->getIdActividad();

	char* idRegistro = (char*)malloc(20);
	char* segundosConsumidos = (char*)malloc(20);
	char* fechaCreacion = (char*)malloc(20);

	do
	{
		vista->limpiar();
		size_t cantidadRegistros = actividad->getRegistrosTotales();

		for (int i = 1, c = 0; c < cantidadRegistros; i++)
		{
			Registro& r = modelo->obtenerRegistroPorId(i, idActividad);
			if (r.esRegistroNulo())
				continue;
			else
				c++;
			strcpy_s(idRegistro, 20, r.getIdRegistroString());
			strcpy_s(fechaCreacion, 20, r.getFechaCreacionString());
			vista->mostrarRegistro(idRegistro, r.getTiempoConsumido(), fechaCreacion, r.getDescripcion());
			
			vista->mostrar("\n\t\t-----------------------------------------------------\n\n");
		}

		size_t digitosCantidadRegistros;
		size_t sizeRegistros = cantidadRegistros;
		for (digitosCantidadRegistros = 0; sizeRegistros != 0; sizeRegistros /= 10)
			digitosCantidadRegistros++;

		COORD posicionActual = posicionActualCursor();

		do
		{
			vista->irXY(posicionActual.X, posicionActual.Y);
			vista->mostrar("A continuación, puede ingresar algún ID para acceder a un registro en particular: ");
			for (int i = 0; i < digitosCantidadRegistros; i++)
				vista->mostrar(" ");
			for (int i = 0; i < digitosCantidadRegistros; i++)
				vista->mostrar("\b");
			char* resultado = vista->ingresar_opcion_salir(digitosCantidadRegistros);

			if (resultado[0] == 0x1B)
				return;

			if (!es_numero(resultado))
				continue;

			int ID = atoi(resultado);

			Registro& r = modelo->obtenerRegistroPorId(ID, idActividad);

			if (r.esRegistroNulo())
				continue;

			ControladorRegistro cr(std::move(r), std::move(*actividad));
			break;

		} while (true);

	} while (true);
}
