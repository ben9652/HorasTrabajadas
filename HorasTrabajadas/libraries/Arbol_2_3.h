#ifndef __ARBOL_2_3_
#define __ARBOL_2_3_

#include "Nodo.h"
#include "Nodo3.h"
#include <initializer_list>

/// <summary>
/// Árbol de búsqueda de índices para un vector.
/// Tiene un máximo de 3 árboles hijos, y si solo hay dos hijos, se lo representa con el árbol izquierdo y el del medio, quedando nulo el de la derecha.
/// Al árbol de la izquierda se irá si clave_busqueda < k1.
/// Al árbol del medio se irá si k1 < clave_busqueda < k2.
/// Al árbol de la derecha se irá si k2 < clave_busqueda.
/// </summary>
class Arbol_2_3
{
public:
	Arbol_2_3(unsigned short _sizeClave);
	Arbol_2_3(const Arbol_2_3& other);
	Arbol_2_3(Nodo* raiz);
	Arbol_2_3(Nodo3* raiz);
	~Arbol_2_3();

	/// <summary>
	/// Se inserta un valor con una clave compuesta asociada en el árbol.
	/// No hay control de duplicidad de claves, por lo que el usuario se tiene que encargar de la unicidad de estas.
	/// </summary>
	/// <param name="clave"></param>
	/// <param name="valor"></param>
	void insertarElemento(std::initializer_list<int> clave, int valor);

	/// <summary>
	/// Se inserta un valor con una clave compuesta asociada en el árbol.
	/// No hay control de duplicidad de claves, por lo que el usuario se tiene que encargar de la unicidad de estas.
	/// </summary>
	/// <param name="clave"></param>
	/// <param name="valor"></param>
	void insertarElemento(int* clave, int valor);

	/// <summary>
	/// Se inserta un valor con una clave asociada en el árbol.
	/// No hay control de duplicidad de claves, por lo que el usuario se tiene que encargar de la unicidad de estas.
	/// </summary>
	/// <param name="clave"></param>
	/// <param name="valor"></param>
	void insertarElemento(int clave, int valor);

	/// <summary>
	/// Modificación de un valor con una clave asociada.
	/// </summary>
	/// <param name="clave"></param>
	/// <param name="nuevoValor"></param>
	void modificarElemento(std::initializer_list<int> clave, int nuevoValor);

	/// <summary>
	/// Borrado de un valor asociado a la clave especificada.
	/// </summary>
	/// <param name="clave"></param>
	int borrarElemento(std::initializer_list<int> clave);

	/// <summary>
	/// Borrado de un valor asociado a la clave especificada.
	/// </summary>
	/// <param name="clave"></param>
	int borrarElemento(int*& clave);

	/// <summary>
	/// Borrado de un valor asociado a la clave especificada.
	/// </summary>
	/// <param name="clave"></param>
	int borrarElemento(int clave);

	int obtenerValor(std::initializer_list<int> clave);

	/// <summary>
	/// Devuelve el valor asociado a la clave dada
	/// </summary>
	/// <param name="clave">Identificador del elemento que se quiere</param>
	/// <returns>El valor cuya clave es la dada</returns>
	int obtenerValor(int*& clave);

	int obtenerValor(int clave);

	/// <summary>
	/// Se obtiene la altura del árbol 2-3
	/// </summary>
	/// <returns>Altura del árbol</returns>
	size_t obtenerAltura();

	/// <summary>
	/// Se obtiene la cantidad total de claves que hay en el árbol 2-3
	/// </summary>
	/// <returns>Claves totales del árbol</returns>
	size_t obtenerElementosTotales();

	/// <summary>
	/// Función para saber si un árbol es vacío.
	/// </summary>
	/// <returns>Valor booleano que informa si el árbol es vacío</returns>
	bool esA23Vacio();

	/// <summary>
	/// Función que señala si el nodo actual es una hoja
	/// </summary>
	/// <returns><b>true</b>: si no tiene hijos; <b>false</b>: si tiene hijos</returns>
	bool esHoja();

	/// <summary>
	/// Imprime árbol en pre-orden con claves en forma de números
	/// </summary>
	void preorden_int();

	/// <summary>
	/// Imprime árbol en pre-orden con claves en forma de caracteres
	/// </summary>
	void preorden_char();

private:
	size_t clavesTotales;

	size_t altura;

	// Árbol izquierdo
	Arbol_2_3* izquierdo;

	// Árbol del medio tirado para la izquierda
	Arbol_2_3* medioIzq;

	// Árbol del medio tirado para la derecha
	Arbol_2_3* medioDer;

	// Árbol derecho
	Arbol_2_3* derecho;

	// Información que contiene el nodo raíz de este árbol
	Nodo3* nodo;

	// Cantidad de elementos que posee la clave compuesta (cada clave compuesta será tomada como UNA clave igualmente)
	unsigned short sizeClave;

	static const char* INDEX_ERROR;

	void setIzquierdo(Arbol_2_3* izquierdo);
	void setMedioIzq(Arbol_2_3* medioIzq);
	void setMedioDer(Arbol_2_3* medioDer);
	void setDerecho(Arbol_2_3* derecho);
	
	void printNode_int();
	void printNode_char();

	bool insertarElementoRecursivo(Arbol_2_3* arbolPadre, Arbol_2_3* raiz, int* clave, int valor);
	bool borrarElementoRecursivo(Arbol_2_3* arbolPadre, int* clave);

	bool insertarElementoRecursivo(Arbol_2_3* arbolPadre, Arbol_2_3* raiz, int clave, int valor);
	bool borrarElementoRecursivo(Arbol_2_3* arbolPadre, int clave);

	void dividir(Arbol_2_3* arbolPadre);
	void unir(Arbol_2_3* arbolPadre);

	Nodo* suprimirMaximo();
	Nodo* suprimirMinimo();

	Nodo* encontrarMaximo();
	Nodo* encontrarMinimo();

	bool contiene(int*& clave);

	unsigned char soyElHijoNumero(Arbol_2_3* padre);

	Nodo3* obtenerNodo(std::initializer_list<int> clave, unsigned char* numeroValorModificado);
	Nodo3* obtenerNodo(int*& clave, unsigned char* numeroValorModificado);
};

namespace {
	class VectorInt
	{
	private:
		int* data;
		unsigned short size;

	public:
		VectorInt(int* data, unsigned short size) : data(data), size(size) {}

		friend bool operator==(const VectorInt& v, int x)
		{
			for (unsigned short i = 0; i < v.size; i++)
			{
				if (v.data[i] == x)
					return true;
			}
			return false;
		}

		friend bool operator<(const VectorInt& v1, const VectorInt& v2)
		{
			for (unsigned short i = 0; i < v1.size; i++)
			{
				if (v1.data[i] < v2.data[i])
					return true;
				else if (v1.data[i] > v2.data[i])
					return false;
			}

			return false;
		}

		friend bool operator<=(const VectorInt& v1, const VectorInt& v2)
		{
			for (unsigned short i = 0; i < v1.size; i++)
			{
				if (v1.data[i] < v2.data[i])
					return true;
				else if (v1.data[i] > v2.data[i])
					return false;
			}

			return false;
		}

		friend bool operator>(const VectorInt& v1, const VectorInt& v2)
		{
			for (unsigned short i = 0; i < v1.size; i++)
			{
				if (v1.data[i] > v2.data[i])
					return true;
				else if (v1.data[i] < v2.data[i])
					return false;
			}

			return false;
		}

		friend bool operator>=(const VectorInt& v1, const VectorInt& v2)
		{
			for (unsigned short i = 0; i < v1.size; i++)
			{
				if (v1.data[i] < v2.data[i])
					return false;
			}
			return true;
		}

		friend bool operator==(const VectorInt& v1, const VectorInt& v2)
		{
			for (unsigned short i = 0; i < v1.size; i++)
			{
				if (v1.data[i] != v2.data[i])
					return false;
			}
			return true;
		}
	};
}

#endif