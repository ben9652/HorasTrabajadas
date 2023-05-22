#include "Nodo3.h"
#include <stdlib.h>

Nodo3::Nodo3(unsigned short _sizeClave)
{
	sizeClave = _sizeClave;
	k1 = nullptr;
	k2 = nullptr;
	k3 = nullptr;
	valor1 = 0;
	valor2 = 0;
	valor3 = 0;
}

Nodo3::Nodo3(int* clave1, int valor1, int* clave2, int valor2, unsigned short _sizeClave)
{
	sizeClave = _sizeClave;

	this->k1 = int_to_Integer(clave1);

	this->k2 = int_to_Integer(clave2);

	this->k3 = nullptr;

	this->valor1 = valor1;
	this->valor2 = valor2;
	this->valor3 = 0;
}

Nodo3::Nodo3(int* clave, int valor, unsigned short _sizeClave)
{
	sizeClave = _sizeClave;

	this->k1 = int_to_Integer(clave);
	this->valor1 = valor;

	this->k2 = nullptr;
	this->valor2 = 0;

	this->k3 = nullptr;
	this->valor3 = 0;
}

Nodo3::Nodo3(Nodo* nodo)
{
	sizeClave = nodo->getSizeClave();

	this->k1 = nodo->getClave();
	this->valor1 = nodo->getValorClave();

	this->k2 = nullptr;
	this->valor2 = 0;
	
	this->k3 = nullptr;
	this->valor3 = 0;
}

Nodo3::Nodo3(const Nodo3& nodo)
{
	sizeClave = nodo.sizeClave;

	k1 = nodo.k1;
	k2 = nodo.k2;
	k3 = nodo.k3;

	valor1 = nodo.valor1;
	valor2 = nodo.valor2;
	valor3 = nodo.valor3;
}

Nodo3::~Nodo3()
{
	delete[] k1;
	delete[] k2;
	delete[] k3;
}

Integer* Nodo3::getClaveMenor()
{
	return k1;
}

int* Nodo3::getClaveMenorInt()
{
	return Integer_to_int(k1);
}

bool Nodo3::setClaveMenor(int*& clave)
{
	if (k1 != nullptr)
	{
		k1 = int_to_Integer(clave);
		return true;
	}
	return false;
}

int Nodo3::getValorClaveMenor()
{
	return valor1;
}

bool Nodo3::setValorClaveMenor(int valor)
{
	if (k1 != nullptr)
	{
		valor1 = valor;
		return true;
	}
	return false;
}

Nodo* Nodo3::getPrimerPar()
{
	if (k1 != nullptr)
		return new Nodo(Integer_to_int(k1), valor1, sizeClave);
	return nullptr;
}

void Nodo3::setPrimerPar(Nodo* par)
{
	k1 = par->getClave();
	valor1 = par->getValorClave();
}

Integer* Nodo3::getClaveMedio()
{
	return k2;
}

int* Nodo3::getClaveMedioInt()
{
	return Integer_to_int(k2);
}

bool Nodo3::setClaveMedio(int*& clave)
{
	if (k2 != nullptr)
	{
		k2 = int_to_Integer(clave);
		return true;
	}
	return false;
}

int Nodo3::getValorClaveMedio()
{
	return valor2;
}

bool Nodo3::setValorClaveMedio(int valor)
{
	if (k2 != nullptr)
	{
		valor2 = valor;
		return true;
	}
	return false;
}

Nodo* Nodo3::getSegundoPar()
{
	if (k2 != nullptr)
		return new Nodo(Integer_to_int(k2), valor2, sizeClave);
	return nullptr;
}

void Nodo3::setSegundoPar(Nodo* par)
{
	k2 = par->getClave();
	valor2 = par->getValorClave();
}

Integer* Nodo3::getClaveMayor()
{
	return k3;
}

int* Nodo3::getClaveMayorInt()
{
	return Integer_to_int(k3);
}

bool Nodo3::setClaveMayor(int*& clave)
{
	if (k3 != nullptr)
	{
		k3 = int_to_Integer(clave);
		return true;
	}
	return false;
}

int Nodo3::getValorClaveMayor()
{
	return valor3;
}

bool Nodo3::setValorClaveMayor(int valor)
{
	if (k3 != nullptr)
	{
		valor3 = valor;
		return true;
	}
	return false;
}

Nodo* Nodo3::getTercerPar()
{
	if (k3 != nullptr)
		return new Nodo(Integer_to_int(k3), valor3, sizeClave);
	return nullptr;
}

void Nodo3::setTercerPar(Nodo* par)
{
	k3 = par->getClave();
	valor3 = par->getValorClave();
}

Nodo* Nodo3::obtenerMaximo()
{
	if (k3 != nullptr)
		return new Nodo(Integer_to_int(k3), valor3, sizeClave);
	else if (k2 != nullptr)
		return new Nodo(Integer_to_int(k2), valor2, sizeClave);
	else if (k1 != nullptr)
		return new Nodo(Integer_to_int(k1), valor1, sizeClave);
	else
		return nullptr;
}

Nodo* Nodo3::obtenerMinimo()
{
	if (k1 != nullptr)
		return new Nodo(Integer_to_int(k1), valor1, sizeClave);
	else
		return nullptr;
}

bool Nodo3::insertarValor(int* clave, int valor)
{
	if (contiene(clave))
		return false;
	if (k1 == nullptr && k2 == nullptr && k3 == nullptr)
	{
		k1 = int_to_Integer(clave);
		valor1 = valor;
	}
	else if (k3 == nullptr && k2 == nullptr && k1 != nullptr)
	{
		if (Integer_menor_int(k1, clave))
		{
			k2 = int_to_Integer(clave);
			valor2 = valor;
		}
		else
		{
			k2 = copiar_Integer(k1);
			delete k1;
			valor2 = valor1;
			k1 = int_to_Integer(clave);
			valor1 = valor;
		}
	}
	else if (k3 == nullptr && k2 != nullptr && k1 != nullptr)
	{
		if (Integer_menor_int(k2, clave))
		{
			k3 = int_to_Integer(clave);
			valor3 = valor;
		}
		else if (Integer_menor_int(k1, clave) && int_menor_Integer(clave, k2))
		{
			k3 = copiar_Integer(k2);
			delete k2;
			valor3 = valor2;
			k2 = int_to_Integer(clave);
			valor2 = valor;
		}
		else if (int_menor_Integer(clave, k1))
		{
			k3 = copiar_Integer(k2);
			delete k2;
			valor3 = valor2;
			k2 = copiar_Integer(k1);
			delete k1;
			valor2 = valor1;
			k1 = int_to_Integer(clave);
			valor1 = valor;
		}
	}
	else
		return false;

	return true;
}

void Nodo3::insertarValor(Nodo* par)
{
	Integer* clave = par->getClave();
	insertarValor(Integer_to_int(clave), par->getValorClave());
}

Nodo* Nodo3::borrarValor(int*& clave)
{
	Nodo* nodoBorrado = nullptr;;
	unsigned char numClaveBorrada = 0;
	if (k1 != nullptr)
	{
		if (Integer_igual_int(k1, clave))
		{
			nodoBorrado = new Nodo(clave, valor1, sizeClave);
			delete k1;
			k1 = nullptr;
			valor1 = 0;

			numClaveBorrada = 1;
		}
	}
	if (k2 != nullptr)
	{
		if (Integer_igual_int(k2, clave))
		{
			nodoBorrado = new Nodo(clave, valor2, sizeClave);
			delete k2;
			k2 = nullptr;
			valor2 = 0;

			numClaveBorrada = 2;
		}
	}
	if (k3 != nullptr)
	{
		if (Integer_igual_int(k3, clave))
		{
			nodoBorrado = new Nodo(clave, valor3, sizeClave);
			delete k3;
			k3 = nullptr;
			valor3 = 0;

			numClaveBorrada = 3;
		}
	}

	switch (numClaveBorrada)
	{
	case 1:
		if (k2 != nullptr && k3 == nullptr)
		{
			k1 = new Integer(k2->getInt());
			delete k2;
			k2 = nullptr;
			valor2 = 0;
		}
		else if (k2 != nullptr && k3 != nullptr)
		{
			k1 = new Integer(k2->getInt());
			k2 = new Integer(k3->getInt());
			delete k3;
			k3 = nullptr;
			valor3 = 0;
		}
		break;

	case 2:
		if (k3 != nullptr)
		{
			k2 = new Integer(k3->getInt());
			delete k3;
			k3 = nullptr;
			valor3 = 0;
		}
		break;
	}

	return nodoBorrado;
}

Nodo* Nodo3::borrarMaximo()
{
	Nodo* nodoBorrado = nullptr;

	if (k3 != nullptr)
	{
		nodoBorrado = new Nodo(Integer_to_int(k3), valor3, sizeClave);
		delete[] k3;
		k3 = nullptr;
		valor3 = 0;
	}
	else if (k2 != nullptr)
	{
		nodoBorrado = new Nodo(Integer_to_int(k2), valor2, sizeClave);
		delete[] k2;
		k2 = nullptr;
		valor2 = 0;
	}
	else if (k1 != nullptr)
	{
		nodoBorrado = new Nodo(Integer_to_int(k1), valor1, sizeClave);
		delete[] k1;
		k1 = nullptr;
		valor1 = 0;
	}

	return nodoBorrado;
}

Nodo* Nodo3::borrarIntermedio()
{
	Nodo* nodoBorrado = nullptr;
	if (k2 == nullptr)
		return nullptr;

	nodoBorrado = new Nodo(Integer_to_int(k2), valor2, sizeClave);

	if (k3 != nullptr)
	{
		k2 = copiar_Integer(k3);
		delete[] k3;
		k3 = nullptr;
		valor2 = valor3;
		valor3 = 0;
	}
	else
	{
		delete[] k2;
		k2 = nullptr;
		valor2 = 0;
	}

	return nodoBorrado;
}

Nodo* Nodo3::borrarMinimo()
{
	Nodo* nodoBorrado = nullptr;

	if (k1 != nullptr)
	{
		nodoBorrado = new Nodo(Integer_to_int(k1), valor1, sizeClave);
		
		if (k2 != nullptr)
		{
			k1 = copiar_Integer(k2);
			valor1 = valor2;

			if (k3 != nullptr)
			{
				k2 = copiar_Integer(k3);
				valor2 = valor3;
			}
			else
			{
				delete[] k2;
				k2 = nullptr;
				valor2 = 0;
			}
		}
		else
		{
			delete[] k1;
			k1 = nullptr;
			valor1 = 0;
		}
	}
	
	return nodoBorrado;
}

unsigned char Nodo3::contiene(int*& clave)
{
	if (k1 != nullptr)
	{
		if (Integer_igual_int(k1, clave))
			return 1;
	}
	if (k2 != nullptr)
	{
		if (Integer_igual_int(k2, clave))
			return 2;
	}
	if (k3 != nullptr)
	{
		if (Integer_igual_int(k3, clave))
			return 3;
	}

	return 0;
}

int Nodo3::obtenerValor(int*& clave)
{
	if (k1 != nullptr)
	{
		if (Integer_igual_int(k1, clave))
			return valor1;
	}
	if (k2 != nullptr)
	{
		if (Integer_igual_int(k2, clave))
			return valor2;
	}
	if (k3 != nullptr)
	{
		if (Integer_igual_int(k3, clave))
			return valor3;
	}
	return 0;
}

Nodo3* Nodo3::obtenerNodo(int*& clave, unsigned char* numeroClave)
{
	*numeroClave = 0;
	if (k1 != nullptr)
	{
		if (Integer_igual_int(k1, clave))
			*numeroClave = 1;
	}
	if (k2 != nullptr)
	{
		if (Integer_igual_int(k2, clave))
			*numeroClave = 2;
	}
	if (k3 != nullptr)
	{
		if (Integer_igual_int(k3, clave))
			*numeroClave = 3;
	}

	if (*numeroClave != 0)
		return this;
	else
		return 0;
}

bool Nodo3::esNodo2()
{
	return k1 != nullptr && k2 == nullptr && k3 == nullptr;
}

bool Nodo3::esNodo3()
{
	return k1 != nullptr && k2 != nullptr && k3 == nullptr;
}

bool Nodo3::esNodo4()
{
	return k1 != nullptr && k2 != nullptr && k3 != nullptr;
}

bool Nodo3::nodoVacio()
{
	return k1 == nullptr && k2 == nullptr && k3 == nullptr;
}

unsigned short Nodo3::getSizeClave()
{
	return sizeClave;
}

Integer* Nodo3::copiar_Integer(const Integer* vector)
{
	Integer* p = (Integer*)malloc(sizeClave * sizeof(Integer));
	for (unsigned short i = 0; i < sizeClave; i++)
		p[i] = vector[i];

	return p;
}

int* Nodo3::Integer_to_int(const Integer* vector)
{
	int* p = (int*)malloc(sizeClave * sizeof(int));
	for (unsigned short i = 0; i < sizeClave; i++)
		p[i] = vector[i];

	return p;
}

Integer* Nodo3::int_to_Integer(const int* vector)
{
	Integer* p = (Integer*)malloc(sizeClave * sizeof(Integer));
	for (unsigned short i = 0; i < sizeClave; i++)
		p[i] = vector[i];

	return p;
}

bool Nodo3::Integer_menor_int(const Integer* v1, const int* v2)
{
	for (unsigned short i = 0; i < sizeClave; i++)
	{
		if (v1[i] < v2[i])
			return true;
		else if (v1[i] > v2[i])
			return false;
	}

	return false;
}

bool Nodo3::int_menor_Integer(const int* v1, const Integer* v2)
{
	for (unsigned short i = 0; i < sizeClave; i++)
	{
		if (v1[i] < v2[i])
			return true;
		else if (v1[i] > v2[i])
			return false;
	}

	return false;
}

bool Nodo3::Integer_igual_int(const Integer* v1, const int* v2)
{
	for (unsigned short i = 0; i < sizeClave; i++)
	{
		if (v1[i] != v2[i])
			return false;
	}
	return true;
}
