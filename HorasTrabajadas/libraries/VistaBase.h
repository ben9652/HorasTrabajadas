#ifndef __VISTA_BASE_
#define __VISTA_BASE_
#include "GestorVistas.h"
#include <stdlib.h>

class VistaBase
{
public:
	void mostrar(const char* s);
	void mostrar(int i);
	void mostrar(size_t uli);
	void limpiar();
	char* ingresar(size_t limite);
	char* ingresar_password(size_t limite);
	char* ingresar_opcion_salir(size_t limite);
	char ingresar_con_memoria(size_t limite, char*& cad, size_t& index, size_t& teclas_apretadas);
	void irXY(short x, short y);
};

#endif