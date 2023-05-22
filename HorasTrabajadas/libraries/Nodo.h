#ifndef __NODO
#define __NODO

#include "Integer.h"

class Nodo
{
public:
	
	Nodo(unsigned short _sizeClave);
	Nodo(int* clave, int valor, unsigned short _sizeClave);

	~Nodo();

	Integer* getClave();
	int* getClaveInt();
	int getValorClave();
	unsigned short getSizeClave();

	friend bool operator==(const Nodo& n1, const Nodo& n2);

	bool nodoLleno();

private:
	// Clave 1
	Integer* k;

	// Cantidad de elementos que tendrá la clave compuesta que tenga el nodo
	unsigned short sizeClave;

	// Valor almacenado asociado a k1
	int valor;
};

#endif