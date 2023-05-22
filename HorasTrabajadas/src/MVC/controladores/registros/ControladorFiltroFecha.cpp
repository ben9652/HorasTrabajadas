#include "ControladorFiltroFecha.h"
#include "common.h"

FechasFiltro ControladorFiltroFecha::fecha_busqueda;
bool ControladorFiltroFecha::filtroAplicado = false;
ControladorFiltroFecha::Fecha ControladorFiltroFecha::criterio = SIN_CRITERIO;

ControladorFiltroFecha::ControladorFiltroFecha()
{
	vista = new VistaFiltroFecha();
}

ControladorFiltroFecha::~ControladorFiltroFecha()
{
}

void ControladorFiltroFecha::ejecutarLogica()
{
	char* opcionString;
	int opcion;

	do
	{
		do
		{
			vista->limpiar();
			vista->mostrar("1- Igual a una fecha\n2- Menor que una fecha\n3- Menor o igual que una fecha\n4- Mayor que una fecha\n5- Mayor o igual que una fecha\n6- Entre una fecha y otra\n\n");
			opcionString = vista->ingresar_opcion_salir(1);
			if (opcionString[0] == 0x1B)
				return;
		} while (!es_numero(opcionString));

		opcion = atoi(opcionString);

		if (opcion == 1 || opcion == 2 || opcion == 3 || opcion == 4 || opcion == 5)
		{
			fecha_busqueda.fechaInicio = escribirFechaFiltro();
			fecha_busqueda.fechaFin = nullptr;
			filtroAplicado = true;
		}
		else if (opcion == 6)
		{
			vista->limpiar();
			vista->mostrar("Fecha inicial\n\n");
			fecha_busqueda.fechaInicio = escribirFechaFiltro();
			vista->limpiar();
			vista->mostrar("Fecha final\n\n");
			fecha_busqueda.fechaFin = escribirFechaFiltro();
			filtroAplicado = true;
		}
		else
			continue;

		if (opcion == 1)
			criterio = IGUAL;
		else if (opcion == 2)
			criterio = MENOR;
		else if (opcion == 3)
			criterio = MENOR_O_IGUAL;
		else if (opcion == 4)
			criterio = MAYOR;
		else if (opcion == 5)
			criterio = MAYOR_O_IGUAL;
		else if (opcion == 6)
			criterio = ENTRE;

	} while (true);
}

void ControladorFiltroFecha::limpiarFiltro()
{
	filtroAplicado = false;
	fecha_busqueda.fechaInicio = nullptr;
	fecha_busqueda.fechaFin = nullptr;
}

char* ControladorFiltroFecha::getFiltroFechaInicio()
{
	return fecha_busqueda.fechaInicio;
}

char* ControladorFiltroFecha::getFiltroFechaFin()
{
	return fecha_busqueda.fechaFin;
}

ControladorFiltroFecha::Fecha ControladorFiltroFecha::getCriterio()
{
	return criterio;
}

bool ControladorFiltroFecha::hayFiltro()
{
	return filtroAplicado;
}

char* ControladorFiltroFecha::escribirFechaFiltro()
{
	char* fechaCompleta = (char*)malloc(11);
	memset(fechaCompleta, 0, 11);
	char* dia = (char*)malloc(3);
	char* mes = (char*)malloc(3);
	char* anio = (char*)malloc(5);

	int d, m, y;

	COORD posicionActual;
	bool fechaValida = false;

	do
	{
		vista->mostrar("Día: ");
		posicionActual = posicionActualCursor();
		do
		{
			gotoxy(posicionActual.X, posicionActual.Y);
			vista->mostrar("  \b\b");
			dia = ingresar_cadena(2);
		} while (!es_numero(dia));
		d = atoi(dia);

		vista->mostrar("Mes: ");
		posicionActual = posicionActualCursor();
		do
		{
			gotoxy(posicionActual.X, posicionActual.Y);
			vista->mostrar("  \b\b");
			mes = ingresar_cadena(2);
		} while (!es_numero(mes));
		m = atoi(mes);

		vista->mostrar("Año: ");
		posicionActual = posicionActualCursor();
		do
		{
			gotoxy(posicionActual.X, posicionActual.Y);
			vista->mostrar("  \b\b");
			anio = ingresar_cadena(4);
		} while (!es_numero(anio));
		y = atoi(anio);

		if (isValidDate(d, m, y))
			fechaValida = true;
		else
		{
			vista->mostrar("La fecha ingresada no es válida. Inténtelo de nuevo.");
			vista->ingresar(0);
		}

	} while (!fechaValida);

	strcat_s(fechaCompleta, 11, anio);
	strcat_s(fechaCompleta, 11, "-");
	strcat_s(fechaCompleta, 11, mes);
	strcat_s(fechaCompleta, 11, "-");
	strcat_s(fechaCompleta, 11, dia);

	return fechaCompleta;
}