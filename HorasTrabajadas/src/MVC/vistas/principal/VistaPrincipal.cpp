#include "VistaPrincipal.h"
#include "VistaActividad.h"
#include "GestorDatos.h"
#include <ctime>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "common.h"

VistaPrincipal::VistaPrincipal()
{
	SetConsoleBufferSize(1000, 20000);
}

void VistaPrincipal::mostrarCargaDeDatos()
{
	GestorDatos* gd = GestorDatos::instanciar();
	gotoxy(0,0);
	std::cout << "[    %] Cargando datos\n";
	std::cout << "Datos totales: " << gd->getDatosTotales() << "\n";
	std::cout << "Datos cargados: " << gd->getDatosTomados();

	int iteraciones = 0;
	int porcentaje;
	do
	{
		porcentaje = gd->porcentajeDatosTomados();
		gotoxy(0,0);
		if (porcentaje < 10)
		{
			gotoxy(3,0);
			printf("%d", porcentaje);
		}
		else if(porcentaje < 100)
		{
			gotoxy(2,0);
			printf("%d", porcentaje);
		}
		else
		{
			gotoxy(1,0);
			printf("%d", porcentaje);
		}
		size_t dc = gd->getDatosTomados();
		gotoxy(16,2);
		printf("%zu", dc);

		if (iteraciones == 100 && porcentaje == 0)
			break;

		iteraciones++;
	} while (porcentaje < 100);

	// Delay de casi 1 segundo
	clock_t now = clock();
	while (clock() - now < CLOCKS_PER_SEC/1.5);
}
