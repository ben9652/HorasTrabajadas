#include "ControladorFiltroTiempo.h"
#include "common.h"
#include <string>
#include <sstream>

TiemposFiltro ControladorFiltroTiempo::tiempo_busqueda;
bool ControladorFiltroTiempo::filtroAplicado = false;
ControladorFiltroTiempo::Tiempo ControladorFiltroTiempo::criterio = SIN_CRITERIO;

ControladorFiltroTiempo::ControladorFiltroTiempo()
{
	vista = new VistaFiltroTiempo();
}

ControladorFiltroTiempo::~ControladorFiltroTiempo()
{
}

void ControladorFiltroTiempo::ejecutarLogica()
{
	char* opcionString;
	int opcion;

	do
	{
		do
		{
			vista->limpiar();
			vista->mostrar("1- Igual a un tiempo\n2- Menor que un tiempo\n3- Menor o igual que un tiempo\n4- Mayor que un tiempo\n5- Mayor o igual que un tiempo\n6- Entre un tiempo y otro\n\n");
			opcionString = vista->ingresar_opcion_salir(1);
			if (opcionString[0] == 0x1B)
				return;
		} while (!es_numero(opcionString));

		opcion = atoi(opcionString);

		if (opcion == 1 || opcion == 2 || opcion == 3 || opcion == 4 || opcion == 5)
		{
			tiempo_busqueda.tiempoInicio = escribirTiempoFiltro();
			filtroAplicado = true;
		}
		else if (opcion == 6)
		{
			vista->limpiar();
			vista->mostrar("Tiempo inicial\n\n");
			tiempo_busqueda.tiempoInicio = escribirTiempoFiltro();
			vista->limpiar();
			vista->mostrar("Tiempo final\n\n");
			tiempo_busqueda.tiempoFin = escribirTiempoFiltro();
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

void ControladorFiltroTiempo::limpiarFiltro()
{
	filtroAplicado = false;
}

unsigned int ControladorFiltroTiempo::getTiempoFiltroInicio()
{
	return tiempo_busqueda.tiempoInicio;
}

unsigned int ControladorFiltroTiempo::getTiempoFiltroFin()
{
	return tiempo_busqueda.tiempoFin;
}

ControladorFiltroTiempo::Tiempo ControladorFiltroTiempo::getCriterio()
{
	return criterio;
}

bool ControladorFiltroTiempo::hayFiltro()
{
	return filtroAplicado;
}

unsigned int ControladorFiltroTiempo::escribirTiempoFiltro()
{
	char* tiempoString = (char*)malloc(20);

	int tiempo;
	
	bool tiempoValido = false;

	do
	{
		vista->mostrar("Ingresar el tiempo de filtro: ");
		tiempoString = ingresar_cadena(19);

		tiempo = tiempoIngresadoCorrectamente(tiempoString);

		if (tiempo == -1)
		{
			vista->mostrar("\nFormato incorrecto.\nEl formato puede ser:\n- <numero>(s): se expresa simplemente en segundos\n- <numero>m: se expresa en minutos\n- <numero>m<numero>s: se expresa en minutos y segundos");
			vista->ingresar(0);
		}

	} while (tiempo == -1);

	return (unsigned int)tiempo;
}