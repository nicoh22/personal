#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <assert.h>

using namespace std;

template <class T>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);

		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;

		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);

		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;

		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;

		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// muestra el conjunto.
		void mostrar(std::ostream&) const;

	private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izquierdo.
			Nodo* izq;
			// puntero a la raíz del subárbol derecho.
			Nodo* der; 
		};

		void mostrarAux(std::ostream&, Conjunto<T>::Nodo*) const;
		int cardinalAux(Conjunto<T>::Nodo*) const;
		void destructorAux(Conjunto<T>::Nodo*);

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz;

};

template <class T>
Conjunto<T>::Conjunto() : raiz(NULL)
{}

template <class T>
Conjunto<T>::~Conjunto()
{
	destructorAux(raiz);
	raiz = NULL;
}

template <class T>
void Conjunto<T>::destructorAux(Conjunto<T>::Nodo *n) {
	if (n != NULL) {
		destructorAux(n->izq);
		destructorAux(n->der);
		delete n;
	}
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const
{
	Conjunto<T>::Nodo *actual = raiz;
	while (true) {
		if (actual == NULL) {
			return false;
		}
		else if (actual->valor == clave) {
			return true;
		}
		else if (clave < actual->valor) {
			actual = actual->izq;
		}
		else {
			actual = actual->der;
		}
	}
	return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave)
{
	Conjunto<T>::Nodo *actual = raiz;
	Conjunto<T>::Nodo **pAnterior = &raiz;
	bool terminado = false;
	while (!terminado) {
		if (actual == NULL) {
			actual = new Nodo(clave);
			*pAnterior = actual;
			terminado = true;
		}
		else if (actual->valor == clave) {
			terminado = true;
		}
		else if (clave < actual->valor) {
			pAnterior = &(actual->izq);
			actual = actual->izq;
		}
		else {
			pAnterior = &(actual->der);
			actual = actual->der;
		}
	}
	//assert(false);
}

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL)
{}

template <class T>
void Conjunto<T>::remover(const T& clave) {
	Conjunto<T>::Nodo *actual = raiz, *n = NULL;
	Conjunto<T>::Nodo **pAnterior = &raiz;
	while (true) {
		if (actual == NULL) {
			break;
		}
		else if (actual->valor == clave) {
			n = actual;
			break;
		}
		else if (clave < actual->valor) {
			pAnterior = &actual->izq;
			actual = actual->izq;
		}
		else {
			pAnterior = &actual->der;
			actual = actual->der;
		}
	}
	
	if (n == NULL) return; //El elemento no existía
	
	//Caso sin hijos
	if (n->izq == NULL && n->der == NULL) {
		*pAnterior = NULL;
		delete n;
	}
	//Caso un hijo, izq
	else if (n->izq != NULL && n->der == NULL) {
		*pAnterior = n->izq;
		delete n;
	}
	//Caso un hijo, der
	else if (n->izq == NULL && n->der != NULL) {
		*pAnterior = n->der;
		delete n;
	}
	//Caso dos hijos
	else {
		//Busco el máximo de los menores, lo pongo en actual
		pAnterior = &actual->izq;
		actual = actual->izq;
		while (actual->der != NULL) {
			pAnterior = &actual->der;
			actual = actual->der;
		}
		n->valor = actual->valor;
		*pAnterior = actual->izq;
		delete actual;
	}
	//assert(false);
}
template <class T>
const T& Conjunto<T>::minimo() const {
	Conjunto<T>::Nodo *actual = raiz;
	while (actual->izq != NULL) {
		actual = actual->izq;
	}
	//assert(false);
	return actual->valor;
}
template <class T>
const T& Conjunto<T>::maximo() const {
	Conjunto<T>::Nodo *actual = raiz;
	while (actual->der != NULL) {
		actual = actual->der;
	}
	//assert(false);
	return actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
	return cardinalAux(raiz);
	//assert(false);
	return 0;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
	if (raiz != NULL) {
		os << "[ ";
		mostrarAux(os, raiz);
		os << "]";
	}
	//assert(false);
}

template <class T>
void Conjunto<T>::mostrarAux(std::ostream& os, Conjunto<T>::Nodo *n) const {
	if (n->izq) mostrarAux(os, n->izq);
	os << n->valor << " ";
	if (n->der) mostrarAux(os, n->der);
}

template <class T>
int Conjunto<T>::cardinalAux(Conjunto<T>::Nodo *n) const {
	if (n != NULL) {
		return 1 + cardinalAux(n->izq) + cardinalAux(n->der);
	}
	else {
		return 0;
	}
}

#endif // CONJUNTO_HPP_
