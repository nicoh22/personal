#ifndef DICC_STRING_H
#define DICC_STRING_H

#include "aed2/Arreglo.h"

namespace aed2 {

template <typename T>
class DiccString 
{

	public:

		DiccString();

		~DiccString();

		void Definir(const String& clave, T& significado);

		bool Definido(const String& clave) const;

		/* Significado no devuelve algo const dado que algun metodo de nivel superior
		 * luego puede necesitar manipular esta referencia. Por ejemplo, cuando tengo
		 * un DiccString<DiccString<Nat>>, para modificar el DiccString interior primero
		 * debo pedirselo al contenedor con Significado.
		 */
		T& Significado(const String& clave) const;

	private:

		struct Nodo {

			Nodo();

			~Nodo();

			Arreglo<Nodo>* caracteres;
			T* significado;

		};

		Nodo* raiz_;

};

template<class T>
DiccString<T>::Nodo::Nodo()
{
	caracteres = new Arreglo<Nodo>(256);
	significado = NULL;
}

template<class T>
DiccString<T>::Nodo::~Nodo()
{
	delete significado;
	delete caracteres;
}

template<class T>
DiccString<T>::DiccString()
{
	raiz_ = new Nodo();
}

template<class T>
DiccString<T>::~DiccString()
{
	delete raiz_;
}


/* WARNING: Parece que no es valido usar algo como Definir("TP","3"). 
 * Una vez que sale de la funcion, la referencia al 3 muere, y cuando
 * llamo nuevamente la funcion el output es nulo.
 */

template<class T>
void DiccString<T>::Definir(const String& clave, T& significado)
{
	// std::cout << "\nDefiniendo clave: " << clave << "\nSignificado: " << significado << std::endl;

	Nodo* nodoActual = raiz_;
	for (Nat i = 0; i < clave.length(); ++i)
	{
		int pos = (int) clave.at(i);
		if (!nodoActual->caracteres->Definido(pos)) {
			Nodo* nuevoNodo = new Nodo();
			nodoActual->caracteres->Definir(pos, *nuevoNodo);
			// std::cout << "Definiendo nodo " << clave.at(i) << std::endl;
		} else {
			// std::cout << "Nodo ya definido " << clave.at(i) << std::endl;
		}
		nodoActual = &(*(nodoActual->caracteres))[pos];
	}
	nodoActual->significado = &significado;
}

template<class T>
bool DiccString<T>::Definido(const String& clave) const
{
	// std::cout << "\nRecorriendo nodos: " << clave << std::endl;

	Nodo* nodoActual = raiz_;
	Nat i = 0;
	bool seguirBuscando = true;
	int pos;
	while (i < clave.length() && seguirBuscando) {
		pos = (int) clave.at(i);
		if (!nodoActual->caracteres->Definido(pos)) {
			// std::cout << clave.at(i) << " no encontrado." << std::endl;
			seguirBuscando = false;
		} else {
			// std::cout << "Nodo " << clave.at(i) << " encontrado." << std::endl;
			nodoActual = &(*nodoActual->caracteres)[pos];
			i++;
		}
	}
	return nodoActual->significado != NULL;
}

template<class T>
T& DiccString<T>::Significado(const String& clave) const
{
	// std::cout << "\nBuscando significado: " << clave << std::endl;

	Nodo* nodoActual = raiz_;
	for (Nat i = 0; i < clave.length(); i++)
	{
		// std::cout << "Nodo " << clave.at(i) << " encontrado." << std::endl;
		nodoActual = &(*nodoActual->caracteres)[(int) clave.at(i)];
	}

	// std::cout << "Significado: " << *nodoActual->significado << std::endl;

	return *nodoActual->significado;
}

}

#endif // DICC_STRING_H