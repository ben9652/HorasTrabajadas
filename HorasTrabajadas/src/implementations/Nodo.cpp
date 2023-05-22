#include "Nodo.h"
#include <stdlib.h>

Nodo::Nodo(unsigned short _sizeClave)
{
	sizeClave = _sizeClave;
	k = nullptr;
	valor = 0;
}

Nodo::Nodo(int* clave, int valor, unsigned short _sizeClave)
{
	sizeClave = _sizeClave;
	this->k = (Integer*)malloc(_sizeClave* sizeof(Integer));
	for (unsigned short i = 0; i < _sizeClave; i++)
		this->k[i] = clave[i];
	this->valor = valor;
}

Nodo::~Nodo()
{
	delete[] k;
}

Integer* Nodo::getClave()
{
	return k;
}

int* Nodo::getClaveInt()
{
	int* p = (int*)malloc(sizeClave * sizeof(int));
	for (unsigned short i = 0; i < sizeClave; i++)
		p[i] = k[i];
	return p;
}

int Nodo::getValorClave()
{
	return valor;
}

unsigned short Nodo::getSizeClave()
{
	return sizeClave;
}

bool Nodo::nodoLleno()
{
	return k != nullptr;
}

bool operator==(const Nodo& n1, const Nodo& n2)
{
	return n1.k == n2.k && n1.valor == n2.valor;
}
