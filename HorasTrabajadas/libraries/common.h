#pragma once

#include <string>
#include <semaphore>
#include <initializer_list>
#include <vector>
#include <Windows.h>

#define _SIN_CONFIGURACION_LOCALE 0

#if _SIN_CONFIGURACION_LOCALE
//#define U_MINUSCULA_DIERESIS		0x81
//#define E_MINUSCULA_TILDE			0x82
//#define E_MAYUSCULA_TILDE			0x90
//#define U_MAYUSCULA_DIERESIS		0x9A
//#define A_MINUSCULA_TILDE			0xA0
//#define I_MINUSCULA_TILDE			0xA1
//#define O_MINUSCULA_TILDE			0xA2
//#define U_MINUSCULA_TILDE			0xA3
//#define N_MINUSCULA_VIRGULILLA	0xA4
//#define N_MAYUSCULA_VIRGULILLA	0xA5
//#define SIMBOLO_GRADOS			0xA7
//#define SIMBOLO_INTERROGACION		0xA8
//#define SIMBOLO_EXCLAMACION		0xAD
//#define A_MAYUSCULA_TILDE			0xB5
//#define I_MAYUSCULA_TILDE			0xD6
//#define O_MAYUSCULA_TILDE			0xE0
//#define U_MAYUSCULA_TILDE			0xE9
#else
#define U_MINUSCULA_DIERESIS		0xFC
#define E_MINUSCULA_TILDE			0xE9
#define E_MAYUSCULA_TILDE			0xC9
#define U_MAYUSCULA_DIERESIS		0xDC
#define A_MINUSCULA_TILDE			0xE1
#define I_MINUSCULA_TILDE			0xED
#define O_MINUSCULA_TILDE			0xF3
#define U_MINUSCULA_TILDE			0xFA
#define N_MINUSCULA_VIRGULILLA		0xF1
#define N_MAYUSCULA_VIRGULILLA		0xD1
#define SIMBOLO_GRADOS				0xBA
#define SIMBOLO_INTERROGACION		0xBF
#define SIMBOLO_EXCLAMACION			0xA1
#define A_MAYUSCULA_TILDE			0xC1
#define I_MAYUSCULA_TILDE			0xCD
#define O_MAYUSCULA_TILDE			0xD3
#define U_MAYUSCULA_TILDE			0xDA
#define O_MINUSCULA_SOMBRERO		0xF4
#define O_MAYUSCULA_SOMBRERO		0xD4
#endif

bool es_numero(const std::string& s);
char* ingresar_cadena(size_t limite);
char* ingresar_cadena_utf8(size_t limite);
char* ingresar_cadena_contrasenia(size_t limite);
char* ingresar_cadena_contrasenia_utf8(size_t limite);
char* ingresar_cadena_con_opcion_de_salir(size_t limite);
char* ingresar_cadena_con_opcion_de_salir_utf8(size_t limite);
// En esta función, el usuario tiene la responsabilidad de asignar espacio de memoria para cad, y de inicializar las variables index y teclas_apretadas. El valor devuelto será un caracter nulo si se terminó de ingresar; sino, será el caracter de escape.
char ingresar_cadena_con_memoria(size_t limite, char*& cad, size_t& index, size_t& teclas_apretadas);
char ingresar_cadena_con_memoria_utf8(size_t limite, char*& cad, size_t& index, size_t& teclas_apretadas);
char* utf8_to_ascii(const char* utf8string);
const char* ascii_to_utf8(const char* asciistring);
void ConcatArrays(int* a, size_t a_size, int* b, size_t b_size);

// Funciones que hacen uso de la API de Windows

void gotoxy(short x, short y);
void scrollX(short x);
void scrollY(short y);
void mostrarCursor(bool mostrarlo);
COORD posicionActualCursor();
void SetConsoleBufferSize(short width, short height);
SHORT verticalSizeWindow();

///////////////////////////////////////////////

int contar_palabras(const char* cad);
void trim(char* cad, size_t n);
int cambiar_ascii_a_ISO8859(int c);
std::vector<int>& arregloConFiltro(std::initializer_list<int> v, int numFiltro);
std::vector<int>& arregloConFiltro(int* v, size_t tam, int numFiltro);
int tiempoIngresadoCorrectamente(const char* tiempoString);

static std::binary_semaphore print_permission(1);

namespace {
	unsigned char convert_utf8_to_ascii(unsigned char car, unsigned char codigo)
	{
		if (codigo == 0xC2)
		{
			if (car == 0xBA)
				return SIMBOLO_GRADOS;
			else if (car == 0xBF)
				return SIMBOLO_INTERROGACION;
			else if (car == 0xA1)
				return SIMBOLO_EXCLAMACION;
		}
		else if (codigo == 0xC3)
		{
			switch (car)
			{
			case 0xBC:
				return U_MINUSCULA_DIERESIS;
			case 0xA9:
				return E_MINUSCULA_TILDE;
			case 0x89:
				return E_MAYUSCULA_TILDE;
			case 0x9C:
				return U_MAYUSCULA_DIERESIS;
			case 0xA1:
				return A_MINUSCULA_TILDE;
			case 0xAD:
				return I_MINUSCULA_TILDE;
			case 0xB3:
				return O_MINUSCULA_TILDE;
			case 0xBA:
				return U_MINUSCULA_TILDE;
			case 0xB1:
				return N_MINUSCULA_VIRGULILLA;
			case 0x91:
				return N_MAYUSCULA_VIRGULILLA;
			case 0x81:
				return A_MAYUSCULA_TILDE;
			case 0x8D:
				return I_MAYUSCULA_TILDE;
			case 0x93:
				return O_MAYUSCULA_TILDE;
			case 0x9A:
				return U_MAYUSCULA_TILDE;
			case 0xB4:
				return O_MINUSCULA_SOMBRERO;
			case 0x94:
				return O_MAYUSCULA_SOMBRERO;
			default:
				return car;
			}
		}

		return car;
	}

	unsigned char convert_ascii_to_utf8(unsigned char car)
	{
		switch (car)
		{
		case U_MINUSCULA_DIERESIS:		return 0xBC;
		case E_MINUSCULA_TILDE:			return 0xA9;
		case E_MAYUSCULA_TILDE:			return 0x89;
		case U_MAYUSCULA_DIERESIS:		return 0x9C;
		case A_MINUSCULA_TILDE:			return 0xA1;
		case I_MINUSCULA_TILDE:			return 0xAD;
		case O_MINUSCULA_TILDE:			return 0xB3;
		case U_MINUSCULA_TILDE:			return 0xBA;
		case N_MINUSCULA_VIRGULILLA:	return 0xB1;
		case N_MAYUSCULA_VIRGULILLA:	return 0x91;
		case SIMBOLO_GRADOS:			return 0xBA;
		case SIMBOLO_INTERROGACION:		return 0xBF;
		case SIMBOLO_EXCLAMACION:		return 0xA1;
		case A_MAYUSCULA_TILDE:			return 0x81;
		case I_MAYUSCULA_TILDE:			return 0x8D;
		case O_MAYUSCULA_TILDE:			return 0x93;
		case U_MAYUSCULA_TILDE:			return 0x9A;
		case O_MINUSCULA_SOMBRERO:		return 0xB4;
		case O_MAYUSCULA_SOMBRERO:		return 0x94;
		default:						return car;
		}
	}
}