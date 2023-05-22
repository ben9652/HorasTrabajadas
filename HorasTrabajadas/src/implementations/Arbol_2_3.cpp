#include "Arbol_2_3.h"
#include "TreeException.h"
#include "KeyException.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>

bool yaSeBorroElemento;
int valorDevueltoPorBorrado;

const char* Arbol_2_3::INDEX_ERROR = "Índice no encontrado.";

Arbol_2_3::Arbol_2_3(unsigned short _sizeClave)
{
	this->sizeClave = _sizeClave;

	this->clavesTotales = 0;
	this->altura = 0;

	this->nodo = new Nodo3(_sizeClave);

	this->izquierdo = nullptr;
	this->medioIzq = nullptr;
	this->medioDer = nullptr;
	this->derecho = nullptr;
}

Arbol_2_3::Arbol_2_3(const Arbol_2_3& other)
{
	this->sizeClave = other.sizeClave;

	this->clavesTotales = other.clavesTotales;
	this->altura = other.altura;

	this->nodo = other.nodo;

	this->izquierdo = other.izquierdo;
	this->medioIzq = other.medioIzq;
	this->medioDer = other.medioDer;
	this->derecho = other.derecho;
}

Arbol_2_3::Arbol_2_3(Nodo* raiz)
{
	this->sizeClave = raiz->getSizeClave();

	this->clavesTotales = 0;
	this->altura = 0;

	this->nodo = new Nodo3(raiz);
	this->izquierdo = nullptr;
	this->medioIzq = nullptr;
	this->medioDer = nullptr;
	this->derecho = nullptr;
}

Arbol_2_3::Arbol_2_3(Nodo3* raiz)
{
	this->sizeClave = raiz->getSizeClave();

	this->clavesTotales = 0;
	this->altura = 0;

	this->nodo = new Nodo3(*raiz);

	this->izquierdo = nullptr;
	this->medioIzq = nullptr;
	this->medioDer = nullptr;
	this->derecho = nullptr;
}

Arbol_2_3::~Arbol_2_3()
{
	clavesTotales = 0;
	altura = 0;

	if (nodo != nullptr)
	{
		delete nodo;
		nodo = nullptr;
	}

	if (izquierdo != nullptr)
	{
		delete izquierdo;
		izquierdo = nullptr;
	}
	if (medioIzq != nullptr)
	{
		delete medioIzq;
		medioIzq = nullptr;
	}
	if (medioDer != nullptr)
	{
		delete medioDer;
		medioDer = nullptr;
	}
	if (derecho != nullptr)
	{
		delete derecho;
		derecho = nullptr;
	}
}

void Arbol_2_3::insertarElemento(std::initializer_list<int> clave, int valor)
{
	if (clave.size() != sizeClave)
	{
		char* alerta = (char*)malloc(200);
		char* contador_elementos = (char*)malloc(10);
		char* tam_clave = (char*)malloc(10);
		_itoa_s((int)clave.size(), contador_elementos, 10, 10);
		_itoa_s(sizeClave, tam_clave, 10, 10);
		strcpy_s(alerta, 200, "ERROR: La lista inicializadora no tiene la cantidad de elementos que tiene la clave compuesta. Se esperaban ");
		strcat_s(alerta, 200, tam_clave);
		strcat_s(alerta, 200, " elementos, y se recibieron ");
		strcat_s(alerta, 200, contador_elementos);
		strcat_s(alerta, 200, ".");
		throw TreeException(alerta);
	}

	unsigned short contador = 0;
	int* lista = (int*)malloc(sizeClave * sizeof(int));
	for (const int& elem : clave)
		lista[contador++] = elem;

	this->insertarElementoRecursivo(nullptr, this, lista, valor);
}

void Arbol_2_3::insertarElemento(int* clave, int valor)
{
	this->insertarElementoRecursivo(nullptr, this, clave, valor);
}

void Arbol_2_3::insertarElemento(int clave, int valor)
{
	if (sizeClave > 1)
		throw KeyException("ERROR: Este árbol contiene claves compuestas. No puede ingresar una clave simple.");
	this->insertarElementoRecursivo(nullptr, this, clave, valor);
}

bool Arbol_2_3::insertarElementoRecursivo(Arbol_2_3* arbolPadre, Arbol_2_3* raiz, int* clave, int valor)
{
	bool se_devuelve_un_nodo_para_agregar = false;
	
	if (esA23Vacio())
	{
		if (nodo->insertarValor(clave, valor))
			raiz->clavesTotales++;
		return false;
	}
	if (esHoja() && nodo->esNodo2())
	{
		if (nodo->insertarValor(clave, valor))
			raiz->clavesTotales++;
	}
	else if (esHoja())
	{
		if (nodo->insertarValor(clave, valor))
		{
			raiz->clavesTotales++;
			se_devuelve_un_nodo_para_agregar = true;
		}
	}
	else
	{
		int* claveMenor = nodo->getClaveMenorInt();
		int* claveMedio;

		if (VectorInt(clave, sizeClave) < VectorInt(claveMenor, sizeClave))
			se_devuelve_un_nodo_para_agregar = izquierdo->insertarElementoRecursivo(this, raiz, clave, valor);
		else if (VectorInt(claveMenor, sizeClave) <= VectorInt(clave, sizeClave) && nodo->esNodo2())
			se_devuelve_un_nodo_para_agregar = medioIzq->insertarElementoRecursivo(this, raiz, clave, valor);
		else
		{
			claveMedio = nodo->getClaveMedioInt();

			if (VectorInt(clave, sizeClave) < VectorInt(claveMedio, sizeClave))
				se_devuelve_un_nodo_para_agregar = medioIzq->insertarElementoRecursivo(this, raiz, clave, valor);
			else
				se_devuelve_un_nodo_para_agregar = medioDer->insertarElementoRecursivo(this, raiz, clave, valor);
		}
	}

	if (se_devuelve_un_nodo_para_agregar && nodo->esNodo4())
		this->dividir(arbolPadre);

	return se_devuelve_un_nodo_para_agregar;
}

void Arbol_2_3::modificarElemento(std::initializer_list<int> clave, int nuevoValor)
{
	if (clave.size() != sizeClave)
	{
		char* alerta = (char*)malloc(200);
		char* contador_elementos = (char*)malloc(10);
		char* tam_clave = (char*)malloc(10);
		_itoa_s((int)clave.size(), contador_elementos, 10, 10);
		_itoa_s(sizeClave, tam_clave, 10, 10);
		strcpy_s(alerta, 200, "ERROR: La lista inicializadora no tiene la cantidad de elementos que tiene la clave compuesta. Se esperaban ");
		strcat_s(alerta, 200, tam_clave);
		strcat_s(alerta, 200, " elementos, y se recibieron ");
		strcat_s(alerta, 200, contador_elementos);
		strcat_s(alerta, 200, ".");
		throw TreeException(alerta);
	}

	unsigned short contador = 0;
	int* lista = (int*)malloc(sizeClave * sizeof(int));
	for (const int& elem : clave)
		lista[contador++] = elem;

	unsigned char numero_de_clave_a_modificar;
	Nodo3* nodo_a_modificar = obtenerNodo(lista, &numero_de_clave_a_modificar);

	switch (numero_de_clave_a_modificar)
	{
	case 1:
		nodo_a_modificar->setValorClaveMenor(nuevoValor);
	case 2:
		nodo_a_modificar->setValorClaveMedio(nuevoValor);
	case 3:
		nodo_a_modificar->setValorClaveMayor(nuevoValor);
	}
}

void Arbol_2_3::dividir(Arbol_2_3* arbolPadre)
{
	int* claveMedio = nodo->getClaveMedioInt();
	int valorClaveMedio = nodo->getValorClaveMedio();
	Nodo* elementoMedio = new Nodo(claveMedio, valorClaveMedio, sizeClave);
	Nodo* elementoIzq = new Nodo(nodo->getClaveMenorInt(), nodo->getValorClaveMenor(), sizeClave);
	Nodo* elementoDer = new Nodo(nodo->getClaveMayorInt(), nodo->getValorClaveMayor(), sizeClave);

	Arbol_2_3* arbolRaiz = new Arbol_2_3(elementoMedio);
	Arbol_2_3* arbolIzq = new Arbol_2_3(elementoIzq);
	Arbol_2_3* arbolDer = new Arbol_2_3(elementoDer);

	arbolIzq->izquierdo = this->izquierdo;
	arbolIzq->medioIzq = this->medioIzq;
	
	arbolDer->izquierdo = this->medioDer;
	arbolDer->medioIzq = this->derecho;

	if (arbolPadre != nullptr)
		arbolPadre->nodo->insertarValor(claveMedio, valorClaveMedio);

	// Si este es el árbol raíz, se crea un nuevo árbol raíz, cuyos hijos serán un árbol que tenga la clave menor del nodo, y otro que tenga la clave mayor del nodo.
	// A la vez, los hijos de estos árboles hijos serán los dos menores del árbol raíz original, y los dos mayores del árbol raíz original, respectivamente.
	if (arbolPadre == nullptr)
	{
		arbolRaiz->izquierdo = arbolIzq;
		arbolRaiz->medioIzq = arbolDer;
		arbolRaiz->altura = this->altura + 1;
		arbolRaiz->clavesTotales = this->clavesTotales;

		*this = *arbolRaiz;
	}

	// Transfiero el elemento del medio al nodo padre y divido en dos al nodo actual, haciendo que la clave menor y la clave mayor sean nodos hijos del nodo padre
	else if (!arbolPadre->nodo->esNodo4())
	{
		switch (soyElHijoNumero(arbolPadre))
		{
		case 1:
			arbolPadre->medioDer = arbolPadre->medioIzq;
			arbolPadre->medioIzq = arbolDer;
			arbolPadre->izquierdo = arbolIzq;
			break;
		case 2:
			arbolPadre->medioDer = arbolDer;
			arbolPadre->medioIzq = arbolIzq;
			break;
		}
	}
	
	else
	{
		switch (soyElHijoNumero(arbolPadre))
		{
		case 1:
			arbolPadre->derecho = arbolPadre->medioDer;
			arbolPadre->medioDer = arbolPadre->medioIzq;
			arbolPadre->medioIzq = arbolDer;
			arbolPadre->izquierdo = arbolIzq;
			break;
		case 2:
			arbolPadre->derecho = arbolPadre->medioDer;
			arbolPadre->medioDer = arbolDer;
			arbolPadre->medioIzq = arbolIzq;
			break;
		case 3:
			arbolPadre->derecho = arbolDer;
			arbolPadre->medioDer = arbolIzq;
			break;
		}
	}

	if (arbolPadre != nullptr)
	{
		this->izquierdo = nullptr;
		this->medioIzq = nullptr;
		this->medioDer = nullptr;
		this->derecho = nullptr;
		delete this;
	}
}

int Arbol_2_3::borrarElemento(std::initializer_list<int> clave)
{
	if (clave.size() != sizeClave)
	{
		char* alerta = (char*)malloc(200);
		char* contador_elementos = (char*)malloc(10);
		char* tam_clave = (char*)malloc(10);
		_itoa_s((int)clave.size(), contador_elementos, 10, 10);
		_itoa_s(sizeClave, tam_clave, 10, 10);
		strcpy_s(alerta, 200, "ERROR: La lista inicializadora no tiene la cantidad de elementos que tiene la clave compuesta. Se esperaban ");
		strcat_s(alerta, 200, tam_clave);
		strcat_s(alerta, 200, " elementos, y se recibieron ");
		strcat_s(alerta, 200, contador_elementos);
		strcat_s(alerta, 200, ".");
		throw TreeException(alerta);
	}

	unsigned short contador = 0;
	int* lista = (int*)malloc(sizeClave * sizeof(int));
	for (const int& elem : clave)
		lista[contador++] = elem;

	yaSeBorroElemento = false;
	if (borrarElementoRecursivo(nullptr, lista))
	{
		clavesTotales--;
		return valorDevueltoPorBorrado;
	}

	return -1;
}

int Arbol_2_3::borrarElemento(int*& clave)
{
	yaSeBorroElemento = false;
	if (borrarElementoRecursivo(nullptr, clave))
	{
		clavesTotales--;
		return valorDevueltoPorBorrado;
	}

	return -1;
}

int Arbol_2_3::borrarElemento(int clave)
{
	if (sizeClave > 1)
		throw KeyException("ERROR: Este árbol contiene claves compuestas. No puede ingresar una clave simple.");

	yaSeBorroElemento = false;
	if (borrarElementoRecursivo(nullptr, clave))
	{
		clavesTotales--;
		return valorDevueltoPorBorrado;
	}

	return -1;
}

Nodo3* Arbol_2_3::obtenerNodo(std::initializer_list<int> clave, unsigned char* numeroValorModificado)
{
	if (clave.size() != sizeClave)
	{
		char* alerta = (char*)malloc(200);
		char* contador_elementos = (char*)malloc(10);
		char* tam_clave = (char*)malloc(10);
		_itoa_s((int)clave.size(), contador_elementos, 10, 10);
		_itoa_s(sizeClave, tam_clave, 10, 10);
		strcpy_s(alerta, 200, "ERROR: La lista inicializadora no tiene la cantidad de elementos que tiene la clave compuesta. Se esperaban ");
		strcat_s(alerta, 200, tam_clave);
		strcat_s(alerta, 200, " elementos, y se recibieron ");
		strcat_s(alerta, 200, contador_elementos);
		strcat_s(alerta, 200, ".");
		throw TreeException(alerta);
	}

	unsigned short contador = 0;
	int* lista = (int*)malloc(sizeClave * sizeof(int));
	for (const int& elem : clave)
		lista[contador++] = elem;

	int* claveMenor = nullptr;
	int* claveMedio = nullptr;
	if (this->nodo->getClaveMenor() != nullptr)
		claveMenor = this->nodo->getClaveMenorInt();
	if (this->nodo->getClaveMedio() != nullptr)
		claveMedio = this->nodo->getClaveMedioInt();

	if (VectorInt(lista, sizeClave) == 0)
		throw TreeException("ERROR: Clave inválida. Ninguno de los elementos puede ser 0.");

	if (claveMenor == nullptr)
		throw TreeException(INDEX_ERROR);

	if (this->nodo->contiene(lista))
		return this->nodo->obtenerNodo(lista, numeroValorModificado);
	else if (VectorInt(lista, sizeClave) < VectorInt(claveMenor, sizeClave) && izquierdo != nullptr)
		return this->izquierdo->obtenerNodo(lista, numeroValorModificado);
	else if (claveMedio != nullptr)
	{
		if (VectorInt(claveMenor, sizeClave) < VectorInt(lista, sizeClave) && VectorInt(lista, sizeClave) < VectorInt(claveMedio, sizeClave) && medioIzq != nullptr)
			return this->medioIzq->obtenerNodo(lista, numeroValorModificado);

		else if (VectorInt(claveMedio, sizeClave) < VectorInt(lista, sizeClave) && medioDer != nullptr)
			return this->medioDer->obtenerNodo(lista, numeroValorModificado);
		else
			throw TreeException(INDEX_ERROR);
	}
	else if (medioIzq != nullptr)
		return this->medioIzq->obtenerNodo(lista, numeroValorModificado);
	else
		throw TreeException(INDEX_ERROR);
}

Nodo3* Arbol_2_3::obtenerNodo(int*& clave, unsigned char* numeroValorModificado)
{
	int* claveMenor = nullptr;
	int* claveMedio = nullptr;
	if (this->nodo->getClaveMenor() != nullptr)
		claveMenor = this->nodo->getClaveMenorInt();
	if (this->nodo->getClaveMedio() != nullptr)
		claveMedio = this->nodo->getClaveMedioInt();

	if (VectorInt(clave, sizeClave) == 0)
		throw TreeException("ERROR: Clave inválida. Ninguno de los elementos puede ser 0.");

	if (claveMenor == nullptr)
		throw TreeException(INDEX_ERROR);

	if (this->nodo->contiene(clave))
		return this->nodo->obtenerNodo(clave, numeroValorModificado);
	else if (VectorInt(clave, sizeClave) < VectorInt(claveMenor, sizeClave) && izquierdo != nullptr)
		return this->izquierdo->obtenerNodo(clave, numeroValorModificado);
	else if (claveMedio != nullptr)
	{
		if (VectorInt(claveMenor, sizeClave) < VectorInt(clave, sizeClave) && VectorInt(clave, sizeClave) < VectorInt(claveMedio, sizeClave) && medioIzq != nullptr)
			return this->medioIzq->obtenerNodo(clave, numeroValorModificado);

		else if (VectorInt(claveMedio, sizeClave) < VectorInt(clave, sizeClave) && medioDer != nullptr)
			return this->medioDer->obtenerNodo(clave, numeroValorModificado);
		else
			throw TreeException(INDEX_ERROR);
	}
	else if (medioIzq != nullptr)
		return this->medioIzq->obtenerNodo(clave, numeroValorModificado);
	else
		throw TreeException(INDEX_ERROR);
}

int Arbol_2_3::obtenerValor(std::initializer_list<int> clave)
{
	if (clave.size() != sizeClave)
	{
		char* alerta = (char*)malloc(200);
		char* contador_elementos = (char*)malloc(10);
		char* tam_clave = (char*)malloc(10);
		_itoa_s((int)clave.size(), contador_elementos, 10, 10);
		_itoa_s(sizeClave, tam_clave, 10, 10);
		strcpy_s(alerta, 200, "ERROR: La lista inicializadora no tiene la cantidad de elementos que tiene la clave compuesta. Se esperaban ");
		strcat_s(alerta, 200, tam_clave);
		strcat_s(alerta, 200, " elementos, y se recibieron ");
		strcat_s(alerta, 200, contador_elementos);
		strcat_s(alerta, 200, ".");
		throw TreeException(alerta);
	}

	unsigned short contador = 0;
	int* lista = (int*)malloc(sizeClave * sizeof(int));
	for (const int& elem : clave)
		lista[contador++] = elem;

	int* claveMenor = nullptr;
	int* claveMedio = nullptr;
	if (this->nodo->getClaveMenor() != nullptr)
		claveMenor = this->nodo->getClaveMenorInt();
	if (this->nodo->getClaveMedio() != nullptr)
		claveMedio = this->nodo->getClaveMedioInt();

	if (VectorInt(lista, sizeClave) == 0)
		throw TreeException("ERROR: Clave inválida. Ninguno de los elementos puede ser 0.");

	if (claveMenor == nullptr)
		throw TreeException(INDEX_ERROR);

	if (this->nodo->contiene(lista))
		return this->nodo->obtenerValor(lista);
	else if (VectorInt(lista, sizeClave) < VectorInt(claveMenor, sizeClave) && izquierdo != nullptr)
		return this->izquierdo->obtenerValor(clave);
	else if (claveMedio != nullptr)
	{
		if (VectorInt(claveMenor, sizeClave) < VectorInt(lista, sizeClave) && VectorInt(lista, sizeClave) < VectorInt(claveMedio, sizeClave) && medioIzq != nullptr)
			return this->medioIzq->obtenerValor(lista);
		else if (VectorInt(claveMedio, sizeClave) < VectorInt(lista, sizeClave) && medioDer != nullptr)
			return this->medioDer->obtenerValor(lista);
		else
			throw TreeException(INDEX_ERROR);
	}
	else if (medioIzq != nullptr)
		return this->medioIzq->obtenerValor(lista);
	else
		throw TreeException(INDEX_ERROR);
}

bool Arbol_2_3::borrarElementoRecursivo(Arbol_2_3* arbolPadre, int* clave)
{
	bool se_borra_elemento = false;

	int* claveMenor = nodo->getClaveMenorInt();
	if (esA23Vacio()) return false;
	if (this->nodo->contiene(clave))
	{
		se_borra_elemento = true;

		if (this->esHoja())
		{
			Nodo* nodoBorrado = nodo->borrarValor(clave);
			if (!yaSeBorroElemento)
			{
				valorDevueltoPorBorrado = nodoBorrado->getValorClave();
				yaSeBorroElemento = true;
			}
		}
		else
		{
			if (VectorInt(clave, sizeClave) == VectorInt(claveMenor, sizeClave))
			{
				Nodo* swap = medioIzq->encontrarMinimo();
				Nodo* nodoBorrado = nodo->borrarMinimo();
				if (!yaSeBorroElemento)
				{
					valorDevueltoPorBorrado = nodoBorrado->getValorClave();
					yaSeBorroElemento = true;
				}
				nodo->insertarValor(swap);
				medioIzq->borrarElementoRecursivo(this, swap->getClaveInt());
			}
			else
			{
				Nodo* swap = medioDer->encontrarMinimo();
				Nodo* nodoBorrado = nodo->borrarMaximo();
				if (!yaSeBorroElemento)
				{
					valorDevueltoPorBorrado = nodoBorrado->getValorClave();
					yaSeBorroElemento = true;
				}
				nodo->insertarValor(swap);
				medioDer->borrarElementoRecursivo(this, swap->getClaveInt());
			}
		}
	}
	else
	{
		if (VectorInt(clave, sizeClave) < VectorInt(claveMenor, sizeClave))
			se_borra_elemento = izquierdo->borrarElementoRecursivo(this, clave);
		else if (VectorInt(claveMenor, sizeClave) <= VectorInt(clave, sizeClave) && nodo->esNodo2())
			se_borra_elemento = medioIzq->borrarElementoRecursivo(this, clave);
		else
		{
			int* claveMedio = nodo->getClaveMedioInt();
			if (VectorInt(clave, sizeClave) < VectorInt(claveMedio, sizeClave))
				se_borra_elemento = medioIzq->borrarElementoRecursivo(this, clave);
			else
				se_borra_elemento = medioDer->borrarElementoRecursivo(this, clave);
		}
	}
	
	unir(arbolPadre);

	return se_borra_elemento;
}

bool Arbol_2_3::insertarElementoRecursivo(Arbol_2_3* arbolPadre, Arbol_2_3* raiz, int clave, int valor)
{
	bool se_devuelve_un_nodo_para_agregar = false;

	int* claveVector = (int*)malloc(sizeof(int));
	*claveVector = clave;
	if (esA23Vacio())
	{
		if (nodo->insertarValor(claveVector, valor))
			raiz->clavesTotales++;
		return false;
	}
	if (esHoja() && nodo->esNodo2())
	{
		if (nodo->insertarValor(claveVector, valor))
			raiz->clavesTotales++;
	}
	else if (esHoja())
	{
		if (nodo->insertarValor(claveVector, valor))
		{
			raiz->clavesTotales++;
			se_devuelve_un_nodo_para_agregar = true;
		}
	}
	else
	{
		int claveMenor = nodo->getClaveMenor()->getInt();
		int claveMedio;

		if (clave < claveMenor)
			se_devuelve_un_nodo_para_agregar = izquierdo->insertarElementoRecursivo(this, raiz, clave, valor);
		else if (claveMenor <= clave && nodo->esNodo2())
			se_devuelve_un_nodo_para_agregar = medioIzq->insertarElementoRecursivo(this, raiz, clave, valor);
		else
		{
			claveMedio = nodo->getClaveMedio()->getInt();

			if (clave < claveMedio)
				se_devuelve_un_nodo_para_agregar = medioIzq->insertarElementoRecursivo(this, raiz, clave, valor);
			else
				se_devuelve_un_nodo_para_agregar = medioDer->insertarElementoRecursivo(this, raiz, clave, valor);
		}
	}

	if (se_devuelve_un_nodo_para_agregar && nodo->esNodo4())
		this->dividir(arbolPadre);

	return se_devuelve_un_nodo_para_agregar;
}

bool Arbol_2_3::borrarElementoRecursivo(Arbol_2_3* arbolPadre, int clave)
{
	bool se_borra_elemento = false;

	int* claveVector = (int*)malloc(sizeof(int));
	*claveVector = clave;

	int claveMenor = nodo->getClaveMenor()->getInt();
	if (esA23Vacio()) return false;
	if (this->nodo->contiene(claveVector))
	{
		se_borra_elemento = true;

		if (this->esHoja())
		{
			Nodo* nodoBorrado = nodo->borrarValor(claveVector);
			if (!yaSeBorroElemento)
			{
				valorDevueltoPorBorrado = nodoBorrado->getValorClave();
				yaSeBorroElemento = true;
			}
		}
		else
		{
			if (clave < claveMenor)
			{
				Nodo* swap = medioIzq->encontrarMinimo();
				Nodo* nodoBorrado = nodo->borrarMinimo();
				if (!yaSeBorroElemento)
				{
					valorDevueltoPorBorrado = nodoBorrado->getValorClave();
					yaSeBorroElemento = true;
				}
				nodo->insertarValor(swap);
				medioIzq->borrarElementoRecursivo(this, swap->getClave()->getInt());
			}
			else
			{
				Nodo* swap = medioDer->encontrarMinimo();
				Nodo* nodoBorrado = nodo->borrarMaximo();
				if (!yaSeBorroElemento)
				{
					valorDevueltoPorBorrado = nodoBorrado->getValorClave();
					yaSeBorroElemento = true;
				}
				nodo->insertarValor(swap);
				medioDer->borrarElementoRecursivo(this, swap->getClave()->getInt());
			}
		}
	}
	else
	{
		if (clave < claveMenor)
			se_borra_elemento = izquierdo->borrarElementoRecursivo(this, clave);
		else if (claveMenor <= clave && nodo->esNodo2())
			se_borra_elemento = medioIzq->borrarElementoRecursivo(this, clave);
		else
		{
			int claveMedio = nodo->getClaveMedio()->getInt();
			if (clave < claveMedio)
				se_borra_elemento = medioIzq->borrarElementoRecursivo(this, clave);
			else
				se_borra_elemento = medioDer->borrarElementoRecursivo(this, clave);
		}
	}

	unir(arbolPadre);

	return se_borra_elemento;
}

void Arbol_2_3::unir(Arbol_2_3* arbolPadre)
{
	if (arbolPadre == nullptr && izquierdo != nullptr && medioIzq == nullptr)
	{
		delete nodo;
		nodo = nullptr;
		size_t clavesTotales = this->clavesTotales;
		size_t altura = this->altura - 1;
		*this = *this->izquierdo;
		this->clavesTotales = clavesTotales;
		this->altura = altura;
		return;
	}

	bool me_queda_una_clave = nodo->getClaveMenor() != nullptr;
	if (me_queda_una_clave) return;

	if (esHoja())
	{
		unsigned char numeroDeHijo = soyElHijoNumero(arbolPadre);
		if (numeroDeHijo == 1)
		{
			// Si no queda clave, entonces el nodo es demasiado pequeño. Así que pasa a buscar a su próximo hermano, a ver si tiene una clave de sobra. Si es que tiene, entonces se la manda al padre, y el padre le da su clave más pequeña a su hijo menor.
			// Si el hermano no tiene dos claves (es decir, no tiene qué ofrecerle a su hermano sin claves) el nodo sin claves le pide a su padre, y este se queda sin claves. Y así, los hermanos se terminan uniendo formando así un nodo con dos claves. Y el nodo será el hijo más pequeño del árbol.
			bool le_quedan_dos_claves = arbolPadre->medioIzq->nodo->getClaveMedio() != nullptr;

			if (le_quedan_dos_claves)
			{
				Nodo* parPrestado = arbolPadre->medioIzq->nodo->borrarMinimo();
				arbolPadre->nodo->insertarValor(parPrestado);
				nodo->insertarValor(arbolPadre->nodo->borrarMinimo());
			}
			else
			{
				Nodo* parRegaladoPorPadre = arbolPadre->nodo->borrarMinimo();
				Nodo* parRegaladoPorHermano = arbolPadre->medioIzq->nodo->borrarMinimo();
				nodo->insertarValor(parRegaladoPorPadre);
				nodo->insertarValor(parRegaladoPorHermano);
				arbolPadre->izquierdo = this;
				arbolPadre->medioIzq = arbolPadre->medioDer;
				if (arbolPadre->medioDer != nullptr)
				{
					arbolPadre->medioDer = nullptr;
					delete arbolPadre->medioDer;
				}
			}
		}

		else if (numeroDeHijo == 2)
		{
			bool le_quedan_dos_claves_al_menor = arbolPadre->izquierdo->nodo->getClaveMedio() != nullptr;
			bool le_quedan_dos_claves_al_mayor = false;
			bool tengo_hermano_mayor = arbolPadre->medioDer != nullptr;
			if (tengo_hermano_mayor)
				le_quedan_dos_claves_al_mayor = arbolPadre->medioDer->nodo->getClaveMedio() != nullptr;

			if (le_quedan_dos_claves_al_mayor)
			{
				Nodo* parPrestado = arbolPadre->medioDer->nodo->borrarMinimo();
				arbolPadre->nodo->insertarValor(parPrestado);
				nodo->insertarValor(arbolPadre->nodo->borrarIntermedio());
			}
			else if (le_quedan_dos_claves_al_menor)
			{
				Nodo* parPrestado = arbolPadre->izquierdo->nodo->borrarMaximo();
				arbolPadre->nodo->insertarValor(parPrestado);
				nodo->insertarValor(arbolPadre->nodo->borrarIntermedio());
			}
			else
			{
				Nodo* parRegaladoPorPadre = arbolPadre->nodo->borrarMinimo();

				arbolPadre->izquierdo->nodo->insertarValor(parRegaladoPorPadre);

				delete arbolPadre->medioIzq;
				if (tengo_hermano_mayor)
					arbolPadre->medioIzq = arbolPadre->medioDer;
				else
					arbolPadre->medioIzq = nullptr;
				arbolPadre->medioDer = nullptr;
			}
		}

		else if(numeroDeHijo == 3)
		{
			bool le_quedan_dos_claves = arbolPadre->medioIzq->nodo->getClaveMedio() != nullptr;

			if (le_quedan_dos_claves)
			{
				Nodo* parPrestado = arbolPadre->medioIzq->nodo->borrarMaximo();
				arbolPadre->nodo->insertarValor(parPrestado);
				nodo->insertarValor(arbolPadre->nodo->borrarMaximo());
			}
			else
			{
				Nodo* parRegaladoPorPadre = arbolPadre->nodo->borrarMaximo();
				nodo->insertarValor(parRegaladoPorPadre);
				arbolPadre->medioIzq->nodo->insertarValor(nodo->borrarMinimo());

				delete arbolPadre->medioDer;
				arbolPadre->medioDer = nullptr;
			}
		}
	}
	else
	{
		unsigned char numeroDeHijo = soyElHijoNumero(arbolPadre);
		if (numeroDeHijo == 1)
		{
			Arbol_2_3* hermano = arbolPadre->medioIzq;
			// Si el hermano que me sigue tiene dos claves
			if (hermano->nodo->esNodo3())
			{
				// Mi hermano le pasa la clave menor a mi padre
				arbolPadre->nodo->insertarValor(hermano->nodo->borrarMinimo());
				// Adquiero la clave menor de mi padre
				nodo->insertarValor(arbolPadre->nodo->borrarMinimo());

				// El hijo menor del hermano que me sigue pasa a ser mi segundo hijo
				this->medioIzq = hermano->izquierdo;
				// El segundo hijo de mi hermano pasa a ser su primer hijo
				hermano->izquierdo = hermano->medioIzq;
				// El hijo mayor de mi hermano pasa a ser su hijo del medio
				hermano->medioIzq = hermano->medioDer;
				hermano->medioDer = nullptr;
			}

			// Si mi hermano no tiene dos claves
			else
			{
				// Mi padre me pasa su clave menor
				nodo->insertarValor(arbolPadre->nodo->borrarMinimo());

				// Me voy uniendo con mi hermano
				nodo->insertarValor(hermano->nodo->borrarMinimo());
				
				// Hago que mi hijo del medio sea el hijo menor de mi hermano
				this->medioIzq = hermano->izquierdo;
				// Hago que mi hijo mayor sea el hijo del medio de mi hermano
				this->medioDer = hermano->medioIzq;

				// Mato lo que queda de mi hermano que sigue
				hermano->izquierdo = nullptr;
				hermano->medioIzq = nullptr;
				delete hermano;

				// Hago que el hermano que me sigue sea mi anterior hermano mayor
				arbolPadre->medioIzq = arbolPadre->medioDer;
				arbolPadre->medioDer = nullptr;
			}
		}
		else if (numeroDeHijo == 2)
		{
			bool tengoHermanoMayor = arbolPadre->medioDer != nullptr;
			Arbol_2_3* hermanoMenor = arbolPadre->izquierdo;

			if (hermanoMenor->nodo->esNodo3())
			{
				// Mi hermano menor le pasa la clave mayor a mi padre
				arbolPadre->nodo->insertarValor(hermanoMenor->nodo->borrarMaximo());

				// Mi padre me pasa su clave de en medio
				nodo->insertarValor(arbolPadre->nodo->borrarIntermedio());

				// El hijo mayor de mi hermano menor pasa a ser mi hijo menor
				this->medioIzq = this->izquierdo;
				this->izquierdo = hermanoMenor->medioDer;
				hermanoMenor->medioDer = nullptr;
			}
			else if (tengoHermanoMayor)
			{
				Arbol_2_3* hermanoMayor = arbolPadre->medioDer;

				if (hermanoMayor->nodo->esNodo3())
				{
					// Mi hermano mayor le pasa a mi padre su clave menor
					arbolPadre->nodo->insertarValor(hermanoMayor->nodo->borrarMinimo());

					// Mi padre me pasa su clave de en medio
					nodo->insertarValor(arbolPadre->nodo->borrarIntermedio());

					// El hijo menor de mi hermano mayor pasa a ser mi segundo hijo
					this->medioIzq = hermanoMayor->izquierdo;
					hermanoMayor->izquierdo = hermanoMayor->medioIzq;
					hermanoMayor->medioIzq = hermanoMayor->medioDer;
					hermanoMayor->medioDer = nullptr;
				}
				else
				{
					// Mi padre me pasa su clave menor
					nodo->insertarValor(arbolPadre->nodo->borrarMinimo());

					// Mi hermano menor adquiere mi clave
					hermanoMenor->nodo->insertarValor(this->nodo->borrarMinimo());

					// Me uno con mi hermano menor, y hago que el hijo mayor de mi hermano menor sea mi hijo
					hermanoMenor->medioDer = this->izquierdo;

					// Dejo de tener hijos
					this->izquierdo = nullptr;

					// El segundo hijo de mi padre pasa a ser mi hermano mayor
					arbolPadre->medioIzq = hermanoMayor;
					arbolPadre->medioDer = nullptr;

					// Dejo de existir
					delete this;
				}
			}
			else
			{
				// Mi padre me pasa su clave menor
				nodo->insertarValor(arbolPadre->nodo->borrarMinimo());

				// Mi hermano menor adquiere mi clave
				hermanoMenor->nodo->insertarValor(this->nodo->borrarMinimo());

				// Me uno con mi hermano menor, y hago que el hijo mayor de mi hermano menor sea mi hijo
				hermanoMenor->medioDer = this->izquierdo;
				arbolPadre->medioIzq = nullptr;

				// Dejo de tener hijos
				this->izquierdo = nullptr;

				// Dejo de existir
				delete this;
			}
		}
		else if (numeroDeHijo == 3)
		{
			Arbol_2_3* hermanoAntecesor = arbolPadre->medioIzq;
			
			// Si el hermano que me antecede tiene dos claves
			if (hermanoAntecesor->nodo->esNodo3())
			{
				// Mi hermano le pasa a mi padre su clave mayor
				arbolPadre->nodo->insertarValor(hermanoAntecesor->nodo->borrarMaximo());

				// Mi padre me pasa su clave mayor
				nodo->insertarValor(arbolPadre->nodo->borrarMaximo());

				// Mi hijo menor pasa a ser mi segundo hijo
				this->medioIzq = this->izquierdo;
				
				// El hijo mayor del hermano que me antecede pasa a ser mi hijo menor
				this->izquierdo = hermanoAntecesor->medioDer;
				hermanoAntecesor->medioDer = nullptr;
			}
			else
			{
				// Mi padre me pasa su clave mayor
				nodo->insertarValor(arbolPadre->nodo->borrarMaximo());

				// Me uno con mi hermano precedente
				hermanoAntecesor->nodo->insertarValor(this->nodo->borrarMinimo());
				arbolPadre->medioDer = nullptr;

				// Su hijo mayor pasa a ser mi hijo menor
				hermanoAntecesor->medioDer = this->izquierdo;

				// Dejo de tener hijos
				this->izquierdo = nullptr;
				
				// Dejo de existir
				delete this;
			}
		}
	}
}

Nodo* Arbol_2_3::suprimirMaximo()
{
	if (medioIzq == nullptr && medioDer == nullptr)
		return nodo->borrarMaximo();
	else
	{
		if (medioIzq != nullptr && medioDer == nullptr)
			return medioIzq->suprimirMaximo();
		else
			return medioDer->suprimirMaximo();
	}
}

Nodo* Arbol_2_3::suprimirMinimo()
{
	if (izquierdo == nullptr)
		return nodo->borrarMinimo();
	else
		return izquierdo->suprimirMinimo();
}

Nodo* Arbol_2_3::encontrarMaximo()
{
	if (medioIzq == nullptr && medioDer == nullptr)
		return nodo->obtenerMaximo();
	else
	{
		if (medioIzq != nullptr && medioDer == nullptr)
			return medioIzq->encontrarMaximo();
		else
			return medioDer->encontrarMaximo();
	}
}

Nodo* Arbol_2_3::encontrarMinimo()
{
	if (izquierdo == nullptr)
		return nodo->obtenerMinimo();
	else
		return izquierdo->encontrarMinimo();
}

bool Arbol_2_3::contiene(int*& clave)
{
	if (nodo->contiene(clave))
		return true;
	else if (esHoja())
		return false;
	else
	{
		int* claveMenor = nodo->getClaveMenorInt();
		
		if (nodo->esNodo2())
		{
			if (VectorInt(clave, sizeClave) < VectorInt(claveMenor, sizeClave))
				return izquierdo->contiene(clave);
			else
				return medioIzq->contiene(clave);
		}
		else
		{
			int* claveMedio = nodo->getClaveMedioInt();

			if (VectorInt(clave, sizeClave) < VectorInt(claveMenor, sizeClave))
				return izquierdo->contiene(clave);
			else if (VectorInt(clave, sizeClave) < VectorInt(claveMedio, sizeClave))
				return medioIzq->contiene(clave);
			else
				return medioDer->contiene(clave);
		}
	}
}

unsigned char Arbol_2_3::soyElHijoNumero(Arbol_2_3* padre)
{
	if (padre->izquierdo->nodo == nodo)
		return 1;
	else if (padre->medioIzq->nodo == nodo)
		return 2;
	else if (padre->medioDer->nodo == nodo)
		return 3;
	else if (padre->derecho->nodo == nodo)
		return 4;
	else
		return 0;
}

int Arbol_2_3::obtenerValor(int*& clave)
{
	int* claveMenor = nullptr;
	int* claveMedio = nullptr;
	if(this->nodo->getClaveMenor() != nullptr)
		claveMenor = this->nodo->getClaveMenorInt();
	if (this->nodo->getClaveMedio() != nullptr)
		claveMedio = this->nodo->getClaveMedioInt();

	if (VectorInt(clave, sizeClave) == 0)
		throw TreeException("ERROR: Clave inválida. Ninguno de los elementos puede ser 0.");

	if (claveMenor == nullptr)
		throw TreeException(INDEX_ERROR);

	if (this->nodo->contiene(clave))
		return this->nodo->obtenerValor(clave);
	else if (VectorInt(clave, sizeClave) < VectorInt(claveMenor, sizeClave) && izquierdo != nullptr)
		return this->izquierdo->obtenerValor(clave);
	else if (claveMedio != nullptr)
	{
		if (VectorInt(claveMenor, sizeClave) < VectorInt(clave, sizeClave) && VectorInt(clave, sizeClave) < VectorInt(claveMedio, sizeClave) && medioIzq != nullptr)
			return this->medioIzq->obtenerValor(clave);
		else if (VectorInt(claveMedio, sizeClave) < VectorInt(clave, sizeClave) && medioDer != nullptr)
			return this->medioDer->obtenerValor(clave);
		else
			throw TreeException(INDEX_ERROR);
	}
	else if (medioIzq != nullptr)
		return this->medioIzq->obtenerValor(clave);
	else
		throw TreeException(INDEX_ERROR);
}

int Arbol_2_3::obtenerValor(int clave)
{
	if (sizeClave > 1)
		throw KeyException("ERROR: Este árbol contiene claves compuestas. No puede ingresar una clave simple.");
	Integer* claveMenor = this->nodo->getClaveMenor();
	Integer* claveMedio = this->nodo->getClaveMedio();

	int* claveVector = (int*)malloc(1);
	*claveVector = clave;
	if (clave == 0)
		throw KeyException("ERROR: Clave inválida. La clave no puede ser 0.");
	if (claveMenor == nullptr)
		throw TreeException(INDEX_ERROR);

	if (this->nodo->contiene(claveVector))
		return this->nodo->obtenerValor(claveVector);
	else if (clave < claveMenor->getInt())
		return this->izquierdo->obtenerValor(clave);
	else if (claveMedio != nullptr)
	{
		if (claveMenor->getInt() < clave && clave < claveMedio->getInt() && medioIzq != nullptr)
			return this->medioIzq->obtenerValor(clave);
		else if (claveMedio->getInt() < clave && medioDer != nullptr)
			return this->medioDer->obtenerValor(clave);
		else
			throw TreeException(INDEX_ERROR);
	}
	else if (medioIzq != nullptr)
		return this->medioIzq->obtenerValor(clave);
	else
		throw TreeException(INDEX_ERROR);
}

size_t Arbol_2_3::obtenerAltura()
{
	return altura;
}

size_t Arbol_2_3::obtenerElementosTotales()
{
	return clavesTotales;
}

bool Arbol_2_3::esA23Vacio()
{
	return nodo->nodoVacio();
}

bool Arbol_2_3::esHoja()
{
	return izquierdo == nullptr && medioIzq == nullptr && medioDer == nullptr;
}

void Arbol_2_3::preorden_int()
{
	printNode_int();
	if (izquierdo != nullptr)
		izquierdo->preorden_int();
	if (medioIzq != nullptr)
		medioIzq->preorden_int();
	if (medioDer != nullptr)
		medioDer->preorden_int();
}

void Arbol_2_3::preorden_char()
{
	printNode_char();
	if(izquierdo != nullptr)
		izquierdo->preorden_char();
	if (medioIzq != nullptr)
		medioIzq->preorden_char();
	if (medioDer != nullptr)
		medioDer->preorden_char();
}

void Arbol_2_3::setIzquierdo(Arbol_2_3* izquierdo)
{
	if (izquierdo != nullptr)
	{
		this->izquierdo = new Arbol_2_3(sizeClave);
		this->izquierdo->izquierdo = izquierdo->izquierdo;
		this->izquierdo->medioIzq = izquierdo->medioIzq;
		this->izquierdo->medioDer = izquierdo->medioDer;
		this->izquierdo->derecho = izquierdo->derecho;
	}
	else
		this->izquierdo = izquierdo;
}

void Arbol_2_3::setMedioIzq(Arbol_2_3* medioIzq)
{
	if (medioIzq != nullptr)
	{
		this->medioIzq = new Arbol_2_3(sizeClave);
		*(this->medioIzq) = *medioIzq;
	}
	else
		this->medioIzq = medioIzq;
}

void Arbol_2_3::setMedioDer(Arbol_2_3* medioDer)
{
	if (medioDer != nullptr)
	{
		this->medioDer = new Arbol_2_3(sizeClave);
		*(this->medioDer) = *medioDer;
	}
	else
		this->medioDer = medioDer;
}

void Arbol_2_3::setDerecho(Arbol_2_3* derecho)
{
	if (derecho != nullptr)
	{
		this->derecho = new Arbol_2_3(sizeClave);
		*(this->derecho) = *derecho;
	}
	else
		this->derecho = derecho;
}

void Arbol_2_3::printNode_int()
{
	if (sizeClave == 1)
	{
		if (nodo->getClaveMenor() != nullptr)
			std::cout << nodo->getClaveMenor()->getInt() << " ";
		else
			std::cout << "NULL ";

		if (nodo->getClaveMedio() != nullptr)
			std::cout << nodo->getClaveMedio()->getInt() << " ";
		else
			std::cout << "NULL ";

		std::cout << std::endl;
	}
	else
	{
		if (nodo->getClaveMenor() != nullptr)
		{
			std::cout << "(";
			for (unsigned short i = 0; i < sizeClave; i++)
			{
				if (i != sizeClave - 1)
					std::cout << nodo->getClaveMenorInt()[i] << ",";
				else
					std::cout << nodo->getClaveMenorInt()[i] << ")" << " ";
			}
		}
		else
			std::cout << "NULL ";

		if (nodo->getClaveMedio() != nullptr)
		{
			std::cout << "(";
			for (unsigned short i = 0; i < sizeClave; i++)
			{
				if (i != sizeClave - 1)
					std::cout << nodo->getClaveMedioInt()[i] << ",";
				else
					std::cout << nodo->getClaveMedioInt()[i] << ")" << " ";
			}
		}
		else
			std::cout << "NULL ";

		std::cout << std::endl;
	}
}

void Arbol_2_3::printNode_char()
{
	if (nodo->getClaveMenor() != nullptr)
		std::cout << nodo->getClaveMenor()->getChar() << " ";
	else
		std::cout << "NULL ";
	
	if (nodo->getClaveMedio() != nullptr)
		std::cout << nodo->getClaveMedio()->getChar() << " ";
	else
		std::cout << "NULL ";

	std::cout << std::endl;
}
