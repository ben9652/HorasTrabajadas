#include "Prueba.h"

int Prueba::x_stat = 0;

Prueba::Prueba(int _x)
{
	x = _x;
}

void Prueba::setX(int _x)
{
	x = _x;
}

int Prueba::getX()
{
	return x;
}