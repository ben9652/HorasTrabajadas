#include <iostream>
#include <locale>
#include <Windows.h>
#include "ControladorPrincipal.h"
#include <TextTable.h>
#include <Psapi.h>
#include "common.h"
#include <ctime>
#include <string.h>
#include <unordered_map>
#include <initializer_list>
#include <array>
#include <vector>
#include "VerificacionVersion.h"

#define TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#define TEXTTABLE_USE_EN_US_UTF8

//#define FUNCIONA_CHARACTER_SET_LATIN;

void print_256_colours_txt();
void usoDeTextTable();
void avanceDePorcentaje();
void pruebaFiltradoTiempo();
bool ip_valida(const char* cadena);

int main(int argc, char** argv)
{
	// Usa el conjunto de caracteres del código ISO/IEC 8859-1, que sirven
	// para poder usar caracteres del español en las cadenas de caracteres
	std::setlocale(LC_ALL, "spanish");

	if (esWindows11()) activarModoAdministrador();

	// Para poner el programa en pantalla completa
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	// Para Maximizar la ventana
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetConsoleBufferSize(1000, 20000);

	if (!ip_valida(apache_ip.c_str()))
	{
		std::cout << "Dirección IP de servidor Apache incorrecta" << std::endl;
		std::cin.get();
		return 1;
	}
	if(!ip_valida(mysql_ip.c_str()))
	{
		std::cout << "Dirección IP de servidor MySQL incorrecta" << std::endl;
		std::cin.get();
		return 1;
	}

	bool banderaActualizacion = false;
	if (!VerificacionVersion::existeActualizador())
	{
		if (VerificacionVersion::checkConnection())
		{
			if (!VerificacionVersion::verificarVersion())
			{
				std::cout << "Diferencia de versiones comprobada. Actualización en curso..." << std::endl;
				if (VerificacionVersion::descargarActualizacion()) return 0;
			}
		}
	}
	else
	{
		banderaActualizacion = true;
		VerificacionVersion::eliminarActualizador();
	}

	if (banderaActualizacion)
	{
		std::cout << "Programa actualizado. Presione ENTER para continuar..." << std::endl;
		std::cin.get();
	}

	// O se inicializa el programa sin ningún argumento...
	if (argc == 1)
		ControladorPrincipal cp;
	// ... o se inicializa el programa con dos argumentos, el primero es el nombre de usuario y el segundo es la contraseña
	else if (argc == 3)
		ControladorPrincipal cp(argv[1], argv[2]);
	else
	{
		std::cout << "Cantidad inválida de argumentos" << std::endl;
		return 1;
	}

	return 0;
}

void print_256_colours_txt()
{
	for (int i = 0; i < 256; i++)
	{
		if (i % 16 == 0 && i != 0)
			std::cout << std::endl;
		fprintf(stdout, "\033[38;5;%dm %3d\033[m", i, i);
	}
}

void usoDeTextTable()
{
	TextTable t('-', '|', '+');

	t.add("");
	t.add("Sexo");
	t.add("Edad");
	t.endOfRow();

	t.add("Moisés");
	t.add("masculino");
	t.add("4556");
	t.endOfRow();

	t.add("Jesús");
	t.add("masculino");
	t.add("2022");
	t.endOfRow();

	t.add("Debora");
	t.add("femenino");
	t.add("3001");
	t.endOfRow();

	t.add("Bob Isaías");
	t.add("masculino");
	t.add("25");
	t.endOfRow();

	t.setAlignment(2, TextTable::Alignment::RIGHT);
	std::cout << t;
}

void avanceDePorcentaje()
{
	std::cout << "[    %] Cargando datos";
	int x = 0;
	do
	{
		if (x < 10)
		{
			gotoxy(3, 0);
			printf("%d", x);
		}
		else if (x < 100)
		{
			gotoxy(2, 0);
			printf("%d", x);
		}
		else
		{
			gotoxy(1, 0);
			printf("%d", x);
		}
		x++;
		clock_t now = clock();
		while (clock() - now < CLOCKS_PER_SEC / 4);
	} while (1);
}

void pruebaFiltradoTiempo()
{
#define EJEMPLO 0

#if EJEMPLO == 0
	std::vector<int> v = arregloConFiltro({ 2,6,1,21,17,8,5 }, 3);

	// En teor�a, deber�a devolver el arreglo {2,1,3,2,1,3,3,3,3,3,3,3,3,3,3,3,3,2,1,3,3,1,2,3}
#elif EJEMPLO == 1
	Vector<int> v = arregloConFiltro({ 4,6,1,9,8,7,2,5,2,3,1 }, 10);

	// En teor�a, deber�a devolver el arreglo {4,6,1,9,8,2,5,2,2,1,2,1}

#elif EJEMPLO == 2
	Vector<int> v = arregloConFiltro({ 4,6,1,9,8,7,6,3,2,23,12,7 }, 10);

	// En teor�a, deber�a devolver el arreglo {4,6,1,9,8,2,5,5,1,3,2,4,10,9,1,10,1,7}

#elif EJEMPLO == 3
	Vector<int> v = arregloConFiltro({ 1,2,3,5,6 }, 10);

	// En teor�a, deber�a devolver el arreglo {4,6,1,9,8,2,5,5,1,3,2,4,10,10,5,5,7,3,4}

#elif EJEMPLO == 4
	int vecOriginal[] = { 46,97,1074,248,346,515,690,285,288,308,276,96,264,919,65,815,603,37,1219,277,71,188,742,2400,167,189,31,519,480,137,138,230,272,533,197,180,463,67,1039,533,473,117,48,102,120,258,53,50,45,32,32,341,442,720,17,90,157,720,343,120,49,1655,600,742,4100,250,167,229,420,30,1094,240,83,816,141,98,131,600,120,480,792,102,113,93,132,642,395,2400,157,420,132,152,87,1714,375,314,409,124,339,67,1108,66,353,208,300,300,1578,63,613,59,224,120,600,97,53,18,120,112,193,280,294,270,207,480,182,87,88,76,396,300,186,210,438,1006,540,120,279,90,300,387,1800,104,300,480,27,135,287,687,600,1200,438,713,854,354,844,242,630,60,360,300,143,454,206,600,3120,40,71,780 };
	std::vector<int> v = arregloConFiltro({ 46,97,1074,248,346,515,690,285,288,308,276,96,264,919,65,815,603,37,1219,277,71,188,742,2400,167,189,31,519,480,137,138,230,272,533,197,180,463,67,1039,533,473,117,48,102,120,258,53,50,45,32,32,341,442,720,17,90,157,720,343,120,49,1655,600,742,4100,250,167,229,420,30,1094,240,83,816,141,98,131,600,120,480,792,102,113,93,132,642,395,2400,157,420,132,152,87,1714,375,314,409,124,339,67,1108,66,353,208,300,300,1578,63,613,59,224,120,600,97,53,18,120,112,193,280,294,270,207,480,182,87,88,76,396,300,186,210,438,1006,540,120,279,90,300,387,1800,104,300,480,27,135,287,687,600,1200,438,713,854,354,844,242,630,60,360,300,143,454,206,600,3120,40,71,780 }, 7200);
	std::cout << "------ Vector original ------" << std::endl;
	for (size_t i = 0; i < 168; i++)
	{
		std::cout << i + 1 << ": " << vecOriginal[i] << std::endl;
	}
#endif

	std::cout << "----- Vector resultante -----" << std::endl;
	for (size_t i = 0; i < v.size(); i++)
		std::cout << i + 1 << ": " << v[i] << std::endl;
}

bool ip_pura_valida(const char* cadena)
{
	char copia_cadena[20];
	strcpy_s(copia_cadena, 20, cadena);

	char* next_token;
	char* segmento = strtok_s(copia_cadena, ".", &next_token);
	unsigned int contador_numeros = 0;

	while (segmento != nullptr)
	{
		if (!es_numero(segmento))
			return false;
		else
		{
			int num = atoi(segmento);
			if (num < 0 || num > 255)
				return false;
		}

		segmento = strtok_s(nullptr, ".", &next_token);
		contador_numeros++;
	}

	return (contador_numeros == 4);
}

bool ip_valida(const char* cadena)
{
	if (strlen(cadena) >= 30) // Asegurándonos de que la cadena no es demasiado larga.
		return false;

	char copia_cadena[30];
	strcpy_s(copia_cadena, 30, cadena);

	char* next_token;
	char* segmento_ip = strtok_s(copia_cadena, ":", &next_token);
	char* segmento_puerto = strtok_s(nullptr, ":", &next_token);

	if (segmento_ip == nullptr || !ip_pura_valida(segmento_ip))
		return false;

	if (segmento_puerto != nullptr)
	{
		if (!es_numero(segmento_puerto))
			return false;
		else
		{
			int num = atoi(segmento_puerto);
			if (num < 0 || num > 65535)
				return false;
		}
	}

	return (strtok_s(nullptr, ":", &next_token) == nullptr); // Asegurándonos de que no hay más segmentos.
}