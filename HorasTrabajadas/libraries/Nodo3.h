#ifndef __NODO3
#define __NODO3

#include "Integer.h"
#include "Nodo.h"

class Nodo3
{
public:

	Nodo3(unsigned short _sizeClave);
	Nodo3(int* clave1, int valor1, int* clave2, int valor2, unsigned short _sizeClave);
	Nodo3(int* clave, int valor, unsigned short _sizeClave);
	Nodo3(Nodo* nodo);
	Nodo3(const Nodo3& nodo);

	~Nodo3();

	Integer* getClaveMenor();
	int* getClaveMenorInt();
	bool setClaveMenor(int*& clave);
	int getValorClaveMenor();
	bool setValorClaveMenor(int valor);
	Nodo* getPrimerPar();
	void setPrimerPar(Nodo* par);

	Integer* getClaveMedio();
	int* getClaveMedioInt();
	bool setClaveMedio(int*& clave);
	int getValorClaveMedio();
	bool setValorClaveMedio(int valor);
	Nodo* getSegundoPar();
	void setSegundoPar(Nodo* par);

	Integer* getClaveMayor();
	int* getClaveMayorInt();
	bool setClaveMayor(int*& clave);
	int getValorClaveMayor();
	bool setValorClaveMayor(int valor);
	Nodo* getTercerPar();
	void setTercerPar(Nodo* par);

	Nodo* obtenerMaximo();

	Nodo* obtenerMinimo();

	/// <summary>
	/// Inserta un par clave-valor y los ordena entre los 3 lugares que hay.
	/// La función no realiza control de clave única.
	/// </summary>
	/// <param name="clave">Clave que identifica al valor. Esta clave debe ser única.</param>
	/// <param name="valor">Valor asociado a la clave.</param>
	bool insertarValor(int* clave, int valor);

	void insertarValor(Nodo* par);

	/// <summary>
	/// Borra un par clave-valor del nodo y re-ordena las claves.
	/// </summary>
	/// <param name="clave">Clave que se quiere eliminar</param>
	/// <returns>Número de clave que se eliminó. Si no se encontró la clave, se devuelve 0.</returns>
	Nodo* borrarValor(int*& clave);

	Nodo* borrarMaximo();

	Nodo* borrarIntermedio();

	Nodo* borrarMinimo();

	/// <summary>
	/// Comprueba si alguna de las claves del nodo coincide con la clave de entrada.
	/// </summary>
	/// <param name="clave">Clave a buscar</param>
	/// <returns>Número de clave que se encontró. Si no se encontró la clave, se devuelve 0.</returns>
	unsigned char contiene(int*& clave);

	/// <summary>
	/// Devuelve el valor asociado a la clave dada
	/// </summary>
	/// <param name="clave">Clave que identifica al valor</param>
	/// <returns>Valor asociado a la clave</returns>
	int obtenerValor(int*& clave);

	Nodo3* obtenerNodo(int*& clave, unsigned char* numeroClave);

	bool esNodo2();
	bool esNodo3();
	bool esNodo4();
	bool nodoVacio();

	unsigned short getSizeClave();

private:
	// Clave 1
	Integer* k1;

	// Clave 2
	Integer* k2;

	// Clave 3
	Integer* k3;

	// Valor almacenado asociado a k1
	int valor1;

	// Valor almacenado asociado a k2
	int valor2;

	// Valor almacenado asociado a k3
	int valor3;

	// Cantidad de elementos que tendrá cada clave compuesta
	unsigned short sizeClave;

	Integer* copiar_Integer(const Integer* vector);

	// Función que servirá para convertir los vectores Integer a vectores int
	int* Integer_to_int(const Integer* vector);

	// Función que servirá para convertir los vectores int a vectores Integer
	Integer* int_to_Integer(const int* vector);

	// Función que dice si los elementos de un vector Integer son TODOS menores a los elementos de un vector int
	bool Integer_menor_int(const Integer* v1, const int* v2);

	// Función que dice si los elementos de un vector int son TODOS menores a los elementos de un vector Integer
	bool int_menor_Integer(const int* v1, const Integer* v2);

	// Función que dice si los elementos de un vector Integer son TODOS iguales a los elementos de un vector int
	bool Integer_igual_int(const Integer* v1, const int* v2);
};

#endif