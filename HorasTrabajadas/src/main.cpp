#include <iostream>
#include <clocale>
#include <Windows.h>
#include "ControladorPrincipal.h"
#include <TextTable.h>
#include <Psapi.h>
#include "Arbol_2_3.h"
#include "common.h"
#include <ctime>
#include "Prueba.h"
#include <string.h>
#include <unordered_map>
#include <initializer_list>
#include <array>
#include <vector>
#include "Actividad.h"

#define TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#define TEXTTABLE_USE_EN_US_UTF8

void print_256_colours_txt();
void pruebaArbol();
void usoDeTextTable();
void avanceDePorcentaje();
Prueba& pruebaClase();
void pruebaFiltradoTiempo();
bool ip_valida(const char* cadena);

struct Vertex
{
	int x, y, z;
	char* nombre;
	Vertex(int x, int y, int z) : x(x), y(y), z(z)
	{
		nombre = (char*)malloc(100);
		strcpy_s(nombre, 100, "Prueba");
	}
	~Vertex()
	{
		std::cout << "¡Destruido!" << std::endl;
		delete[] nombre;
	}
	Vertex(const Vertex& other)
	{
		std::cout << "¡Copiado!" << std::endl;
		x = other.x;
		y = other.y;
		z = other.z;
		nombre = (char*)malloc(100);
		strcpy_s(nombre, 100, other.nombre);
	}
	Vertex(Vertex&& other) noexcept
	{
		std::cout << "¡Valor R!" << std::endl;
		x = other.x;
		y = other.y;
		z = other.z;
		nombre = (char*)malloc(100);
		strcpy_s(nombre, 100, other.nombre);
	}

	Vertex& operator=(const Vertex& other)
	{
		std::cout << "Operador =" << std::endl;
		x = other.x;
		y = other.y;
		z = other.z;
		//nombre = (char*)malloc(100);
		//strcpy_s(nombre, 100, other.nombre);

		return *this;
	}
};

int main(int argc, char** argv)
{
	// Usa el conjunto de caracteres del código ISO/IEC 8859-1, que sirven
	// para poder usar caracteres del español en las cadenas de caracteres
	std::setlocale(LC_ALL, "spanish");

	// Para poner el programa en pantalla completa
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	// Para Maximizar la ventana
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetConsoleBufferSize(1000, 20000);

#define EXPERIMENTO_VECTORES 2
#if EXPERIMENTO_VECTORES == 0
	std::vector<Vertex> v;
	v.emplace_back(1, 2, 3);
	v.emplace_back(4, 5, 6);
	v.emplace_back(7, 8, 9);
	v.emplace_back(10, 11, 12);
	v.emplace_back(13, 14, 15);
#elif EXPERIMENTO_VECTORES == 1
	std::vector<Actividad> v;
	v.emplace_back(1, "Enseñándole a Lucas", 70558);
	v.emplace_back(2, "Pruebas", 0);
	v.emplace_back(3, "PruebaFiltro1", 60);
	v.emplace_back(4, "PruebaFiltro2", 48);
	v.emplace_back(5, "PruebaFiltro3", 88);
#endif
#if EXPERIMENTO_VECTORES < 2
	std::cout << std::endl;
	v.erase(v.begin() + 1);
#endif

	if (argc == 1)
		ControladorPrincipal cp;
	else if (argc == 2)
	{
		if (!ip_valida(argv[1]))
		{
			std::cout << "Dirección IP incorrecta" << std::endl;
			return 1;
		}
		ControladorPrincipal cp(argv[1]);
	}
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

void pruebaArbol()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T inicioUso = pmc.PrivateUsage;

	Arbol_2_3* arbol = new Arbol_2_3(2);
	std::cout << "-------------- Árbol sin modificar ---------------" << std::endl;
	arbol->insertarElemento({1,1}, 0);
	arbol->insertarElemento({1,2}, 1);
	arbol->insertarElemento({2,1}, 2);
	arbol->insertarElemento({2,2}, 3);
	arbol->insertarElemento({3,1}, 4);
	arbol->insertarElemento({3,2}, 5);
	arbol->insertarElemento({4,1}, 6);
	arbol->insertarElemento({4,2}, 7);
	arbol->insertarElemento({5,1}, 8);
	arbol->insertarElemento({5,2}, 9);
	arbol->insertarElemento({6,1}, 10);
	arbol->insertarElemento({6,2}, 11);
	arbol->insertarElemento({7,1}, 12);
	arbol->insertarElemento({7,2}, 13);
	arbol->insertarElemento({8,1}, 14);
	arbol->insertarElemento({8,2}, 15);
	arbol->insertarElemento({9,1}, 16);
	arbol->insertarElemento({9,2}, 17);
	arbol->insertarElemento({10,1}, 18);
	arbol->insertarElemento({10,2}, 19);
	arbol->insertarElemento({11,1}, 20);
	arbol->insertarElemento({11,2}, 21);
	arbol->insertarElemento({12,1}, 22);
	arbol->insertarElemento({12,2}, 23);
	arbol->insertarElemento({13,1}, 24);
	arbol->insertarElemento({13,2}, 25);
	arbol->insertarElemento({14,1}, 26);
	arbol->insertarElemento({14,2}, 27);
	arbol->insertarElemento({15,1}, 28);
	arbol->insertarElemento({16,1}, 29);
	arbol->insertarElemento({17,1}, 30);
	arbol->insertarElemento({18,1}, 31);
	arbol->insertarElemento({19,1}, 32);
	arbol->insertarElemento({20,1}, 33);
	arbol->insertarElemento({21,1}, 34);
	arbol->insertarElemento({22,1}, 35);
	arbol->insertarElemento({23,1}, 36);
	arbol->insertarElemento({24,1}, 37);
	arbol->insertarElemento({25,1}, 38);
	arbol->insertarElemento({26,1}, 39);
	arbol->insertarElemento({27,1}, 40);
	arbol->insertarElemento({28,1}, 41);
	arbol->insertarElemento({29,1}, 42);
	arbol->insertarElemento({30,1}, 43);
	arbol->insertarElemento({31,1}, 44);
	arbol->insertarElemento({32,1}, 45);
	arbol->insertarElemento({33,1}, 46);
	arbol->insertarElemento({34,1}, 47);
	arbol->insertarElemento({35,1}, 48);
	arbol->insertarElemento({36,1}, 49);
	arbol->insertarElemento({37,1}, 50);
	arbol->insertarElemento({38,1}, 51);
	arbol->insertarElemento({39,1}, 52);
	arbol->insertarElemento({40,1}, 53);
	arbol->insertarElemento({41,1}, 54);
	arbol->insertarElemento({42,1}, 55);
	arbol->insertarElemento({43,1}, 56);
	arbol->insertarElemento({44,1}, 57);
	arbol->insertarElemento({45,1}, 58);
	arbol->insertarElemento({46,1}, 59);
	arbol->insertarElemento({47,1}, 60);
	arbol->insertarElemento({48,1}, 61);
	arbol->insertarElemento({49,1}, 62);
	arbol->insertarElemento({50,1}, 63);
	arbol->insertarElemento({51,1}, 64);
	arbol->insertarElemento({52,1}, 65);
	arbol->insertarElemento({53,1}, 66);
	arbol->insertarElemento({54,1}, 67);
	arbol->insertarElemento({55,1}, 68);
	arbol->insertarElemento({56,1}, 69);
	arbol->insertarElemento({57,1}, 70);
	arbol->insertarElemento({58,1}, 71);
	arbol->insertarElemento({59,1}, 72);
	arbol->insertarElemento({60,1}, 73);
	arbol->insertarElemento({61,1}, 74);
	arbol->insertarElemento({62,1}, 75);
	arbol->insertarElemento({63,1}, 76);
	arbol->insertarElemento({64,1}, 77);
	arbol->insertarElemento({65,1}, 78);
	arbol->insertarElemento({66,1}, 79);
	arbol->insertarElemento({67,1}, 80);
	arbol->insertarElemento({68,1}, 81);
	arbol->insertarElemento({69,1}, 82);
	arbol->insertarElemento({70,1}, 83);
	arbol->insertarElemento({71,1}, 84);
	arbol->insertarElemento({72,1}, 85);
	arbol->insertarElemento({73,1}, 86);
	arbol->insertarElemento({74,1}, 87);
	arbol->insertarElemento({75,1}, 88);
	arbol->insertarElemento({76,1}, 89);
	arbol->insertarElemento({77,1}, 90);
	arbol->insertarElemento({78,1}, 91);
	arbol->insertarElemento({79,1}, 92);
	arbol->insertarElemento({80,1}, 93);
	arbol->insertarElemento({81,1}, 94);
	arbol->insertarElemento({82,1}, 95);
	arbol->insertarElemento({83,1}, 96);
	arbol->insertarElemento({84,1}, 97);
	arbol->insertarElemento({85,1}, 98);
	arbol->insertarElemento({86,1}, 99);
	arbol->insertarElemento({87,1}, 100);
	arbol->insertarElemento({88,1}, 101);
	arbol->insertarElemento({89,1}, 102);
	arbol->insertarElemento({90,1}, 103);
	arbol->insertarElemento({91,1}, 104);
	arbol->insertarElemento({92,1}, 105);
	arbol->insertarElemento({93,1}, 106);
	arbol->insertarElemento({94,1}, 107);
	arbol->insertarElemento({95,1}, 108);
	arbol->insertarElemento({96,1}, 109);
	arbol->insertarElemento({97,1}, 110);
	arbol->insertarElemento({98,1}, 111);
	arbol->insertarElemento({99,1}, 112);
	arbol->insertarElemento({100,1}, 113);
	arbol->insertarElemento({101,1}, 114);
	arbol->insertarElemento({102,1}, 115);
	arbol->insertarElemento({103,1}, 116);
	arbol->insertarElemento({104,1}, 117);
	arbol->insertarElemento({105,1}, 118);
	arbol->insertarElemento({106,1}, 119);
	arbol->insertarElemento({107,1}, 120);
	arbol->insertarElemento({108,1}, 121);
	arbol->insertarElemento({109,1}, 122);
	arbol->insertarElemento({110,1}, 123);
	arbol->insertarElemento({111,1}, 124);
	arbol->insertarElemento({112,1}, 125);
	arbol->insertarElemento({113,1}, 126);
	arbol->insertarElemento({114,1}, 127);
	arbol->insertarElemento({115,1}, 128);
	arbol->insertarElemento({116,1}, 129);
	arbol->insertarElemento({117,1}, 130);
	arbol->insertarElemento({118,1}, 131);
	arbol->insertarElemento({119,1}, 132);
	arbol->insertarElemento({120,1}, 133);
	arbol->insertarElemento({121,1}, 134);
	arbol->insertarElemento({122,1}, 135);
	arbol->insertarElemento({123,1}, 136);
	arbol->insertarElemento({124,1}, 137);
	arbol->insertarElemento({125,1}, 138);
	arbol->insertarElemento({126,1}, 139);
	arbol->insertarElemento({127,1}, 140);
	arbol->insertarElemento({128,1}, 141);
	arbol->insertarElemento({129,1}, 142);
	arbol->insertarElemento({130,1}, 143);
	arbol->insertarElemento({131,1}, 144);
	arbol->insertarElemento({132,1}, 145);
	arbol->insertarElemento({133,1}, 146);
	arbol->insertarElemento({134,1}, 147);
	arbol->insertarElemento({135,1}, 148);
	arbol->insertarElemento({136,1}, 149);
	arbol->insertarElemento({137,1}, 150);
	arbol->insertarElemento({138,1}, 151);
	arbol->insertarElemento({139,1}, 152);
	arbol->insertarElemento({140,1}, 153);
	arbol->insertarElemento({141,1}, 154);
	arbol->insertarElemento({142,1}, 155);
	arbol->insertarElemento({143,1}, 156);
	arbol->insertarElemento({144,1}, 157);
	arbol->insertarElemento({145,1}, 158);
	arbol->insertarElemento({146,1}, 159);
	arbol->insertarElemento({147,1}, 160);
	arbol->insertarElemento({148,1}, 161);
	arbol->insertarElemento({149,1}, 162);
	arbol->insertarElemento({150,1}, 163);
	arbol->insertarElemento({151,1}, 164);
	arbol->insertarElemento({152,1}, 165);
	arbol->insertarElemento({153,1}, 166);
	arbol->insertarElemento({154,1}, 167);
	arbol->insertarElemento({155,1}, 168);
	arbol->insertarElemento({156,1}, 169);
	arbol->insertarElemento({157,1}, 170);
	arbol->insertarElemento({158,1}, 171);
	arbol->insertarElemento({159,1}, 172);
	arbol->insertarElemento({160,1}, 173);
	arbol->insertarElemento({161,1}, 174);
	arbol->insertarElemento({162,1}, 175);
	arbol->insertarElemento({163,1}, 176);
	arbol->insertarElemento({164,1}, 177);
	arbol->insertarElemento({165,1}, 178);
	arbol->insertarElemento({166,1}, 179);
	arbol->insertarElemento({167,1}, 180);
	arbol->insertarElemento({168,1}, 181);
	arbol->preorden_int();
	arbol->borrarElemento({ 162,1 });
	arbol->borrarElemento({ 3,2 });
	arbol->borrarElemento({ 165,1 });
	arbol->borrarElemento({ 90,1 });
	arbol->borrarElemento({ 18,1 });
	arbol->borrarElemento({ 31,1 });
	std::cout << "\n---------- Árbol modificado -----------" << std::endl;
	arbol->preorden_int();
	std::cout << std::endl;
	std::cout << "Altura: " << arbol->obtenerAltura() << std::endl;
	std::cout << "Cantidad de elementos: " << arbol->obtenerElementosTotales() << std::endl;

	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T finUso = pmc.PrivateUsage;

	std::cout << finUso - inicioUso << " B usados por árbol" << std::endl;
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

	t.add("Bob Çuçsü");
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

Prueba& pruebaClase()
{
	Prueba* prueba = new Prueba(3);
	Prueba& p = *prueba;
	return p;
}

void pruebaFiltradoTiempo()
{
#define EJEMPLO 0

#if EJEMPLO == 0
	std::vector<int> v = arregloConFiltro({ 2,6,1,21,17,8,5 }, 3);

	// En teoría, debería devolver el arreglo {2,1,3,2,1,3,3,3,3,3,3,3,3,3,3,3,3,2,1,3,3,1,2,3}
#elif EJEMPLO == 1
	Vector<int> v = arregloConFiltro({ 4,6,1,9,8,7,2,5,2,3,1 }, 10);

	// En teoría, debería devolver el arreglo {4,6,1,9,8,2,5,2,2,1,2,1}

#elif EJEMPLO == 2
	Vector<int> v = arregloConFiltro({ 4,6,1,9,8,7,6,3,2,23,12,7 }, 10);

	// En teoría, debería devolver el arreglo {4,6,1,9,8,2,5,5,1,3,2,4,10,9,1,10,1,7}

#elif EJEMPLO == 3
	Vector<int> v = arregloConFiltro({ 1,2,3,5,6 }, 10);

	// En teoría, debería devolver el arreglo {4,6,1,9,8,2,5,5,1,3,2,4,10,10,5,5,7,3,4}

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

bool ip_valida(const char* cadena)
{
	char* next_token;
	char* posible_direccion_ip = (char*)malloc(20);
	strcpy_s(posible_direccion_ip, 20, cadena);
	posible_direccion_ip = strtok_s(posible_direccion_ip, ".", &next_token);
	unsigned int contador_numeros = 0;
	while (posible_direccion_ip != nullptr)
	{
		if (!es_numero(posible_direccion_ip))
			return false;
		else
		{
			int num = atoi(posible_direccion_ip);
			if (num < 0 || num > 255)
				return false;
		}
		posible_direccion_ip = strtok_s(NULL, ".", &next_token);

		contador_numeros++;
	}

	if (contador_numeros != 4)
		return false;

	return true;
}