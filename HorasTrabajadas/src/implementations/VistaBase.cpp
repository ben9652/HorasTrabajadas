#include "VistaBase.h"
#include <iostream>
#include <stdlib.h>
#include "common.h"

void VistaBase::mostrar(const char* s)
{
	std::cout << s;
}

void VistaBase::mostrar(int i)
{
	std::cout << i;
}

void VistaBase::mostrar(size_t uli)
{
	std::cout << uli;
}

void VistaBase::limpiar()
{
	system("cls");
}

char* VistaBase::ingresar(size_t limite)
{
	return ingresar_cadena(limite);
}

char* VistaBase::ingresar_password(size_t limite)
{
	return ingresar_cadena_contrasenia(limite);
}

char* VistaBase::ingresar_opcion_salir(size_t limite)
{
	return ingresar_cadena_con_opcion_de_salir(limite);
}

char VistaBase::ingresar_con_memoria(size_t limite, char*& cad, size_t& index, size_t& teclas_apretadas)
{
	return ingresar_cadena_con_memoria(limite, cad, index, teclas_apretadas);
}

void VistaBase::irXY(short x, short y)
{
	gotoxy(x, y);
}
