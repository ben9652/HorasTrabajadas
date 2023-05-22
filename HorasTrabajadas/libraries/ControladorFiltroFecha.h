#ifndef __CONTROLADOR_FILTRO_FECHA_
#define __CONTROLADOR_FILTRO_FECHA_
#include "Actividad.h"
#include "GestorConexion.h"
#include <ctime>

class VistaFiltroFecha;

namespace {
	struct FechasFiltro
	{
		char* fechaInicio;
		char* fechaFin;
	};
}

class ControladorFiltroFecha
{
public:
	ControladorFiltroFecha();
	~ControladorFiltroFecha();

    enum Fecha { SIN_CRITERIO = -1, IGUAL, MENOR, MENOR_O_IGUAL, MAYOR, MAYOR_O_IGUAL, ENTRE };

	void ejecutarLogica();
    char* escribirFechaFiltro();

	void limpiarFiltro();
	char* getFiltroFechaInicio();
	char* getFiltroFechaFin();
    Fecha getCriterio();
    bool hayFiltro();

private:
	VistaFiltroFecha* vista;

	static FechasFiltro fecha_busqueda;

    // No se considerarán las fechas si el criterio es -1
    static Fecha criterio;
	static bool filtroAplicado;

    const int MAX_VALID_YR = 9999;
    const int MIN_VALID_YR = 1800;

    // Retorna verdadero si el año dado es válido
    bool isLeap(int year)
    {
        // Return true if year
        // is a multiple of 4 and
        // not multiple of 100.
        // OR year is multiple of 400.
        return (((year % 4 == 0) &&
            (year % 100 != 0)) ||
            (year % 400 == 0));
    }

    // Retorna verdadero si la fecha dada es válida
    bool isValidDate(int d, int m, int y)
    {
        // If year, month and day
        // are not in given range
        if (y > MAX_VALID_YR ||
            y < MIN_VALID_YR)
            return false;
        if (m < 1 || m > 12)
            return false;
        if (d < 1 || d > 31)
            return false;

        // Handle February month
        // with leap year
        if (m == 2)
        {
            if (isLeap(y))
                return (d <= 29);
            else
                return (d <= 28);
        }

        // Months of April, June,
        // Sept and Nov must have
        // number of days less than
        // or equal to 30.
        if (m == 4 || m == 6 ||
            m == 9 || m == 11)
            return (d <= 30);

        return true;
    }
};

#include "VistaFiltroFecha.h"

#endif