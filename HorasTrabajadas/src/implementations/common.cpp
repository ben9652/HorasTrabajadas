#include "common.h"
#include <string>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <locale>
#include <conio.h>
#include <ctype.h>
#include <cmath>
#include <iterator>

bool es_numero(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

char* ingresar_cadena_utf8(size_t limite)
{
	char* cad = (char*)malloc(limite);

	int tecla = 0;
	size_t index = 0;
	size_t teclas_apretadas = 0;
	while (tecla != 13)
	{
		if (_kbhit())
		{
			tecla = _getch();

			// Para omitir las teclas Fn
			if (_kbhit())
			{
				tecla = _getch();
				continue;
			}

			if (tecla == 0x1B)
				continue;

#if _SIN_CONFIGURACION_LOCALE == 0
			tecla = cambiar_ascii_a_ISO8859(tecla);
#endif

			if (tecla == 0)
				continue;

			if (tecla != 13)
			{
				// La tecla 8 es el retroceso
				if (tecla != 8)
				{
					if (teclas_apretadas < limite)
					{
						fputwc(tecla, stdout);
						teclas_apretadas++;
						cad[index++] = tecla;
					}
				}
				else if (teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribi� algo
				{
					teclas_apretadas--;
					if (teclas_apretadas < limite)
						cad[--index] = 0;
					printf("\b \b");
				}
			}
		}
	}
	fputwc('\n', stdout);

	cad[index++] = '\0';

	return cad;
}

char* ingresar_cadena_contrasenia_utf8(size_t limite)
{
	char* cad = (char*)malloc(limite);

	int tecla = 0;
	size_t index = 0;
	size_t teclas_apretadas = 0;
	while (tecla != 13)
	{
		if (_kbhit())
		{
			tecla = _getch();

			// Para omitir las teclas Fn
			if (_kbhit())
			{
				tecla = _getch();
				continue;
			}

			if (tecla == 0x1B)
				continue;

#if _SIN_CONFIGURACION_LOCALE == 0
			tecla = cambiar_ascii_a_ISO8859(tecla);
#endif

			if (tecla == 0)
				continue;

			if (tecla != 13)
			{
				// La tecla 8 es el retroceso
				if (tecla != 8)
				{
					if (teclas_apretadas < limite)
					{
						fputwc('*', stdout);
						teclas_apretadas++;
						cad[index++] = tecla;
					}
				}
				else if (teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribi� algo
				{
					teclas_apretadas--;
					if (teclas_apretadas < limite)
						cad[--index] = 0;
					printf("\b \b");
				}
			}
		}
	}
	fputwc('\n', stdout);

	cad[index++] = '\0';

	return cad;
}

char* ingresar_cadena_con_opcion_de_salir_utf8(size_t limite)
{
	char* cad = (char*)malloc(limite);

	int tecla = 0;
	size_t index = 0;
	size_t teclas_apretadas = 0;
	while (tecla != 13)
	{
		if (_kbhit())
		{
			tecla = _getch();

			// Para omitir las teclas Fn
			if (_kbhit())
			{
				tecla = _getch();
				continue;
			}

			// Tecla escape para salir de un ámbito
			if (tecla == 0x1B)
			{
				memset(cad, 0, limite);
				cad[0] = tecla;
				return cad;
			}

#if _SIN_CONFIGURACION_LOCALE == 0
			tecla = cambiar_ascii_a_ISO8859(tecla);
#endif

			if (tecla == 0)
				continue;

			if (tecla != 13)
			{
				// La tecla 8 es el retroceso
				if (tecla != 8)
				{
					if (teclas_apretadas < limite)
					{
						fputwc(tecla, stdout);
						teclas_apretadas++;
						cad[index++] = tecla;
					}
				}
				else if (teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribi� algo
				{
					teclas_apretadas--;
					if (teclas_apretadas < limite)
						cad[--index] = 0;
					printf("\b \b");
				}
			}
		}
	}
	fputwc('\n', stdout);

	cad[index++] = '\0';

	return cad;
}

char ingresar_cadena_con_memoria_utf8(size_t limite, char*& cad, size_t& index, size_t& teclas_apretadas)
{
	int tecla = 0;
	while (tecla != 13)
	{
		if (_kbhit())
		{
			tecla = _getch();

			// Para omitir las teclas Fn
			if (_kbhit())
			{
				tecla = _getch();
				continue;
			}

			// Tecla escape para salir de un ámbito
			if (tecla == 0x1B)
				return tecla;

#if _SIN_CONFIGURACION_LOCALE == 0
			tecla = cambiar_ascii_a_ISO8859(tecla);
#endif

			if (tecla == 0)
				continue;

			if (tecla != 13)
			{
				// La tecla 8 es el retroceso
				if (tecla != 8)
				{
					if (teclas_apretadas < limite)
					{
						fputwc(tecla, stdout);
						teclas_apretadas++;
						cad[index++] = tecla;
					}
				}
				else if (teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribi� algo
				{
					teclas_apretadas--;
					if (teclas_apretadas < limite)
						cad[--index] = 0;
					printf("\b \b");
				}
			}
		}
	}
	fputwc('\n', stdout);

	cad[index] = '\0';

	return '\0';
}

char* ingresar_cadena(size_t limite)
{
	char* cad = (char*)malloc(limite);

	int tecla = 0;
	size_t index = 0;
	size_t teclas_apretadas = 0;
	while (tecla != 13)
	{
		if (_kbhit())
		{
			tecla = _getch();

			// Para omitir las teclas Fn
			if (_kbhit())
			{
				tecla = _getch();
				continue;
			}

			if (tecla == 0x1B)
				continue;

#if _SIN_CONFIGURACION_LOCALE == 0
			tecla = cambiar_ascii_a_ISO8859(tecla);
#endif

			if (tecla == 0)
				continue;

			if (tecla != 13)
			{
				// La tecla 8 es el retroceso
				if (tecla != 8)
				{
					if (teclas_apretadas < limite)
					{
						fputc(tecla, stdout);
						teclas_apretadas++;
						cad[index++] = tecla;
					}
				}
				else if (teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribi� algo
				{
					teclas_apretadas--;
					if (teclas_apretadas < limite)
						cad[--index] = 0;
					printf("\b \b");
				}
			}
		}
	}
	fputc('\n', stdout);

	cad[index++] = '\0';

	return cad;
}

char* ingresar_cadena_contrasenia(size_t limite)
{
	char* cad = (char*)malloc(limite);

	int tecla = 0;
	size_t index = 0;
	size_t teclas_apretadas = 0;
	while (tecla != 13)
	{
		if (_kbhit())
		{
			tecla = _getch();

			// Para omitir las teclas Fn
			if (_kbhit())
			{
				tecla = _getch();
				continue;
			}

			if (tecla == 0x1B)
				continue;

#if _SIN_CONFIGURACION_LOCALE == 0
			tecla = cambiar_ascii_a_ISO8859(tecla);
#endif
			if (tecla == 0)
				continue;

			if (tecla != 13)
			{
				// La tecla 8 es el retroceso
				if (tecla != 8)
				{
					if (teclas_apretadas < limite)
					{
						fputc('*', stdout);
						teclas_apretadas++;
						cad[index++] = tecla;
					}
				}
				else if (teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribi� algo
				{
					teclas_apretadas--;
					if (teclas_apretadas < limite)
						cad[--index] = 0;
					printf("\b \b");
				}
			}
		}
	}
	fputc('\n', stdout);

	cad[index++] = '\0';

	return cad;
}

char* ingresar_cadena_con_opcion_de_salir(size_t limite)
{
	char* cad = (char*)malloc(limite);

	int tecla = 0;
	size_t index = 0;
	size_t teclas_apretadas = 0;
	while (tecla != 13)
	{
		if (_kbhit())
		{
			tecla = _getch();

			// Para omitir las teclas Fn
			if (_kbhit())
			{
				tecla = _getch();
				continue;
			}

			// Tecla escape para salir de un ámbito
			if (tecla == 0x1B)
			{
				memset(cad, 0, limite);
				cad[0] = tecla;
				return cad;
			}

#if _SIN_CONFIGURACION_LOCALE == 0
			tecla = cambiar_ascii_a_ISO8859(tecla);
#endif
			if (tecla == 0)
				continue;

			if (tecla != 13)
			{
				// La tecla 8 es el retroceso
				if (tecla != 8)
				{
					if (teclas_apretadas < limite)
					{
						fputc(tecla, stdout);
						teclas_apretadas++;
						cad[index++] = tecla;
					}
				}
				else if (teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribi� algo
				{
					teclas_apretadas--;
					if (teclas_apretadas < limite)
						cad[--index] = 0;
					printf("\b \b");
				}
			}
		}
	}
	fputc('\n', stdout);

	cad[index++] = '\0';

	return cad;
}

char ingresar_cadena_con_memoria(size_t limite, char*& cad, size_t& index, size_t& teclas_apretadas)
{
	int tecla = 0;
	while (tecla != 13)
	{
		if (_kbhit())
		{
			tecla = _getch();

			// Para omitir las teclas Fn
			if (_kbhit())
			{
				tecla = _getch();
				continue;
			}

			// Tecla escape para salir de un ámbito
			if (tecla == 0x1B)
				return tecla;

#if _SIN_CONFIGURACION_LOCALE == 0
			tecla = cambiar_ascii_a_ISO8859(tecla);
#endif
			if (tecla == 0)
				continue;

			if (tecla != 13)
			{
				// La tecla 8 es el retroceso
				if (tecla != 8)
				{
					if (teclas_apretadas < limite)
					{
						fputc(tecla, stdout);
						teclas_apretadas++;
						cad[index++] = tecla;
					}
				}
				else if (teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribi� algo
				{
					teclas_apretadas--;
					if (teclas_apretadas < limite)
						cad[--index] = 0;
					printf("\b \b");
				}
			}
		}
	}
	fputc('\n', stdout);

	cad[index] = '\0';

	return '\0';
}

char* utf8_to_ascii(const char* utf8string)
{
	char* asciistring = (char*)malloc(strlen(utf8string) + 1);
	size_t puntero = 0;

	unsigned char codigo = 0;
	for (char* aux = (char*)utf8string; *aux != 0; aux++)
	{
		unsigned char c = *aux;
		if (c == 0xC3 || c == 0xC2)
		{
			codigo = *aux;
			continue;
		}
		
		asciistring[puntero++] = convert_utf8_to_ascii(c, codigo);
		codigo = 0;
	}
	asciistring[puntero] = 0;

	return asciistring;
}

const char* ascii_to_utf8(const char* asciistring)
{
	size_t sizeUTF8str = 2 * strlen(asciistring) + 1;
	char* utf8_char_str = (char*)malloc(sizeUTF8str);
	memset(utf8_char_str, 0, sizeUTF8str);

	unsigned char car;
	int j = 0;
	for (int i = 0; i < sizeUTF8str; i++)
	{
		car = asciistring[i];
		if (car > 127)
		{
			if (car == SIMBOLO_GRADOS || car == SIMBOLO_INTERROGACION || car == SIMBOLO_EXCLAMACION)
				utf8_char_str[j++] = (char)0xC2;
			else
				utf8_char_str[j++] = (char)0xC3;
			utf8_char_str[j++] = convert_ascii_to_utf8(car);
		}
		else if (car == 0)
			break;
		else
			utf8_char_str[j++] = car;
	}

	return utf8_char_str;
}

void ConcatArrays(int* a, size_t a_size, int* b, size_t b_size)
{
	int* p = a + a_size;
	for (size_t i = 0; i < b_size; i++)
		*p++ = *b++;
}

void gotoxy(short x, short y)
{
	COORD coords;

	coords.X = x;
	coords.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
}

void scrollX(short x)
{
	HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handler, &csbi);
	cursorPos = csbi.dwCursorPosition;

	cursorPos.X += x;

	SetConsoleCursorPosition(handler, cursorPos);
}

void scrollY(short y)
{
	HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handler, &csbi);
	cursorPos = csbi.dwCursorPosition;

	cursorPos.Y += y;

	SetConsoleCursorPosition(handler, cursorPos);
}

void mostrarCursor(bool mostrarlo)
{
	HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handler, &cursorInfo);
	cursorInfo.bVisible = mostrarlo;
	SetConsoleCursorInfo(handler, &cursorInfo);
}

COORD posicionActualCursor()
{
	HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handler, &csbi);

	return csbi.dwCursorPosition;
}

void SetConsoleBufferSize(short width, short height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD Size;
	Size.X = width;
	Size.Y = height;
	SetConsoleScreenBufferSize(hStdout, Size);
}

SHORT verticalSizeWindow()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	return csbi.srWindow.Bottom;
}

int contar_palabras(const char* cad)
{
	int contadorPalabras = 0;
	bool unaLetraEncontrada = false;
	for (char* c = (char*)cad; *c != '\0'; c++)
	{
		if (*c == ' ')
			unaLetraEncontrada = false;
		else if (!unaLetraEncontrada)
		{
			if (isalpha(*c))
			{
				unaLetraEncontrada = true;
				contadorPalabras++;
			}
		}
	}

	return contadorPalabras;
}

void trim(char* cad, size_t n)
{
	bool espacioEncontrado = false;
	for (char* c = cad; *c != '\0'; c++)
	{
		if (*c == ' ')
		{
			if (!espacioEncontrado)
			{
				espacioEncontrado = true;
				*c = '\0';
			}
		}
		else
		{
			if (espacioEncontrado)
			{
				espacioEncontrado = false;
				strcat_s(cad, n, c);
			}
		}
	}
}

int cambiar_ascii_a_ISO8859(int c)
{
	switch (c)
	{
	case 0x81: return U_MINUSCULA_DIERESIS;
	case 0x82: return E_MINUSCULA_TILDE;
	case 0x90: return E_MAYUSCULA_TILDE;
	case 0x93: return O_MINUSCULA_SOMBRERO;
	case 0xE2: return O_MAYUSCULA_SOMBRERO;
	case 0x9A: return U_MAYUSCULA_DIERESIS;
	case 0xA0: return A_MINUSCULA_TILDE;
	case 0xA1: return I_MINUSCULA_TILDE;
	case 0xA2: return O_MINUSCULA_TILDE;
	case 0xA3: return U_MINUSCULA_TILDE;
	case 0xA4: return N_MINUSCULA_VIRGULILLA;
	case 0xA5: return N_MAYUSCULA_VIRGULILLA;
	case 0xA7: return SIMBOLO_GRADOS;
	case 0xA8: return SIMBOLO_INTERROGACION;
	case 0xAD: return SIMBOLO_EXCLAMACION;
	case 0xB5: return A_MAYUSCULA_TILDE;
	case 0xD6: return I_MAYUSCULA_TILDE;
	case 0xE0: return O_MAYUSCULA_TILDE;
	case 0xE9: return U_MAYUSCULA_TILDE;
	default:
		if (c > 127)
			return 0;
		else
			return c;
	}
}

// El error de esta función es que falta 
std::vector<int>& arregloConFiltro(std::initializer_list<int> vector, int numFiltro)
{
	int suma = 0, sRes = 0, x, sAnterior, vecesRepetido;
	std::vector<int>* vRes = new std::vector<int>();
	size_t tam = vector.size();
	int* v = (int*)malloc(tam * sizeof(int));
	int i = 0;
	for (const int& elem : vector)
		v[i++] = elem;
	
	for (i = 0; i < tam; i++)
	{
		if (suma != 0)
			suma += v[i];
		else
			suma = v[i];

		if (suma < numFiltro)
		{
			vRes->push_back(v[i]);
			sRes += v[i];
		}
		else if (suma == numFiltro)
		{
			vRes->push_back(v[i]);
			sRes += v[i];
			suma = 0;
		}
		else if (suma >= 2 * numFiltro)
		{
			if (suma != 0)
			{
				sAnterior = suma - v[i];
				x = abs(numFiltro - sAnterior);
				vRes->push_back(x);
				sRes += x;
				suma -= sAnterior + x;
			}

			vecesRepetido = suma / numFiltro;
			std::vector<int> numeroRepetido(vecesRepetido, numFiltro);
			vRes->insert(
				vRes->end(),
				std::make_move_iterator(numeroRepetido.begin()),
				std::make_move_iterator(numeroRepetido.end())
			);

			int resto = suma % numFiltro;
			if (resto != 0)
			{
				vRes->push_back(resto);
				sRes = 0;
			}
			suma -= vecesRepetido * numFiltro;
		}
		else if (suma > numFiltro)
		{
			x = abs(sRes - numFiltro);
			vRes->push_back(x);
			suma -= numFiltro;
			vRes->push_back(suma);
			sRes = suma;
		}

		if (sRes == numFiltro)
			sRes = 0;
		else if (sRes > numFiltro)
			sRes -= numFiltro;
	}

	return *vRes;
}

std::vector<int>& arregloConFiltro(int* v, size_t tam, int numFiltro)
{
	int suma = 0, sRes = 0, x, sAnterior, vecesRepetido;
	std::vector<int>* vRes = new std::vector<int>();

	for (int i = 0; i < tam; i++)
	{
		if (suma != 0)
			suma += v[i];
		else
			suma = v[i];

		if (suma < numFiltro)
		{
			vRes->push_back(v[i]);
			sRes += v[i];
		}
		else if (suma == numFiltro)
		{
			vRes->push_back(v[i]);
			sRes += v[i];
			suma = 0;
		}
		else if (suma >= 2 * numFiltro)
		{
			if (suma != 0)
			{
				sAnterior = suma - v[i];
				x = abs(numFiltro - sAnterior);
				vRes->push_back(x);
				sRes += x;
				suma -= sAnterior + x;
			}

			vecesRepetido = suma / numFiltro;
			std::vector<int> numeroRepetido(vecesRepetido, numFiltro);
			vRes->insert(
				vRes->end(),
				std::make_move_iterator(numeroRepetido.begin()),
				std::make_move_iterator(numeroRepetido.end())
			);

			int resto = suma % numFiltro;
			if (resto != 0)
			{
				vRes->push_back(resto);
				sRes = 0;
			}
			suma -= vecesRepetido * numFiltro;
		}
		else if (suma > numFiltro)
		{
			x = abs(sRes - numFiltro);
			vRes->push_back(x);
			suma -= numFiltro;
			vRes->push_back(suma);
			sRes = suma;
		}

		if (sRes == numFiltro)
			sRes = 0;
		else if (sRes > numFiltro)
			sRes -= numFiltro;
	}

	return *vRes;
}

int tiempoIngresadoCorrectamente(const char* tiempoString)
{
	std::string tiempo = tiempoString;
	std::stringstream ss(tiempo);
	std::string token;

	int resultado = -1;
	int minutos = 0;
	int segundos = 0;

	size_t posicion_m;
	size_t posicion_s;
	if ((tiempo.find('m') != std::string::npos) && tiempo.find('s') != std::string::npos)
	{
		// Extracción de horas
		std::getline(ss, token, 'm');
		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i])) return -1;
		}
		minutos = stoi(token);

		std::getline(ss, token, 'm');
		if (posicion_m = token.find('s'))
			token = token.erase(posicion_m, 1);

		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i])) return -1;
		}
		segundos = stoi(token);

		segundos += minutos * 60;
		resultado = segundos;
	}
	else if ((posicion_m = tiempo.find('m')) != std::string::npos)
	{
		std::getline(ss, token, 'm');
		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i])) return -1;
		}

		resultado = stoi(token) * 60;
	}
	else if ((posicion_s = tiempo.find('s')) != std::string::npos)
	{
		std::getline(ss, token, 's');
		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i])) return -1;
		}

		resultado = stoi(token);
	}
	else
	{
		for (unsigned int i = 0; i < tiempo.size(); i++)
		{
			if (!isdigit(tiempo[i])) return -1;
		}

		resultado = stoi(tiempo);
	}

	return resultado;
}