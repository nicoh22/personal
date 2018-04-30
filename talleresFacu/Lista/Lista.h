#ifndef LISTA_H_
#define LISTA_H_

#include <string>
#include <ostream>

typedef unsigned long Nat;

template <typename T>
class Lista
{
	public:

		/**
		 * Constructor por defecto.
		 * Crea una lista enlazada vacía. ( Operación Vacia() )
		 */
		Lista();

		/**
		 * Constructor por copia.
		 * Crea, por copia, una lista enlazada. (operación Copiar())
		 */
		Lista(const Lista& otra);

		/**
		 * Destructor.
		 * Destruye la lista, incluyendo los elementos 'T' alojados.
		 */
		~Lista();

		/**
		 * Operacion de asignacion.
		 * Recrea a la lista como una copia de la pasada como parámetro.
		 */
		Lista<T>& operator=(const Lista<T>& otra);

		//observadores

		/**
		 * Devuelve la cantidad de elementos almacenados en la lista.
		 */
		Nat longitud() const;

		/**
		 * Devuelve el i-esimo elemento (versión modificable)
		 */
		T& iesimo(Nat i);

		/**
		 * Devuelve el i-esimo elemento (versión no modificable)
		 */
		const T& iesimo(Nat i) const;

		/**
		 * Operacion de comparacion.
		 * Retorna verdadero si la lista es igual a otra pasada como
		 * parámetro, falso en caso contrario.
		 */
		bool operator==(const Lista<T>& otra) const;

		// algunas operaciones de lista

		/**
		 * Agrega un nuevo elemento como primer elemento de la lista.
		 */
		void agAdelante(const T& elem);

		/**
		 * Agrega un nuevo elemento como último elemento de la lista.
		 */
		void agAtras(const T& elem);

		/**
		 * Elimina al i-ésimo elemento de la lista.
		 */
		void eliminar(Nat i);

		/**
		 * Muestra la lista en un ostream
		 * formato de salida: [a_0, a_1, a_2, ...], donde a_i es
		 * el resultado del "mostrar" el elemento i de la lista
		 */
		void mostrar(std::ostream& o) const;

		template <typename S>
		friend std::ostream& operator<<(std::ostream& os, const Lista<S> &l);

	private:

		struct Nodo {
			T dato;
			Nodo* sig;
		};

		Nat len;
		Nodo* prim;
		Nodo* fin;
};

template <typename T>
Lista<T>::Lista()
	: len(0), prim(NULL), fin(NULL) {
}

template <typename T>
Lista<T>::Lista(const Lista& otra) {
	int i = 0;
	while( i < otra.longitud()){
		this->agAtras( otra.iesimo( i ) );
		i++;
	}
}

template <typename T>
Lista<T>::~Lista() {
	while(this->longitud() != 0){
		eliminar(0);
	}
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra) {
	int i = 0;
	while(this->longitud() != 0){
		eliminar(0);
	}
	while( i < otra.longitud()){
		this->agAtras( otra.iesimo( i ) );
		i++;
	}
}

template <typename T>
Nat Lista<T>::longitud() const {
	return len;
}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
	int act = 0;
	Nodo* actual = prim;
	while (act < i){
		actual = actual->sig;
		act++;
	}
	return actual->dato;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
	int act = 0;
	Nodo* actual = prim;
	while (act < i){
		actual = actual->sig;
		act++;
	}
	return actual->dato;
}

template <typename T>
bool Lista<T>::operator==(const Lista<T>& otra) const {
	int act = 0;
	if (longitud() != otra.longitud()){ 
		return false;
	}
	while (act < longitud()){
		if (iesimo(act) != otra.iesimo(act)){
			return false;
		}
		act++;
	}
  return true;
}

template <typename T>
void Lista<T>::agAdelante(const T& elem) {
	Nodo* nuevo = new Nodo;
	nuevo->dato = elem;
	nuevo->sig = prim;
	prim = nuevo;
	if (fin == NULL){
		fin = nuevo;
	}
	len++;
}

template <typename T>
void Lista<T>::agAtras(const T& elem) {
	Nodo* nuevo = new Nodo;
	nuevo->dato = elem;
	nuevo->sig = NULL;
	if (prim == NULL){
		prim = nuevo;
	}
	if (fin != NULL){
		fin->sig = nuevo;	
	}
	fin = nuevo;
	len++;
}

template <typename T>
void Lista<T>::eliminar(Nat i) {
	int actual = 0;
	Nodo* iesimo = prim;
	Nodo* anterior = NULL;
	while(actual < i){
		anterior = iesimo;
		iesimo = iesimo->sig;
		actual++;
	}
	if (anterior != NULL){
		anterior->sig = iesimo->sig; 
	}else{
		prim = iesimo->sig;
	}
	if ( fin==iesimo ){
		fin = anterior;
	}
	delete iesimo;
	len--;
}

template <typename T>
void Lista<T>::mostrar(std::ostream& o) const {
	int i = 0;
	o << "[";
	while( i < longitud()){
		if (i == longitud() - 1){
			o << iesimo(i) << "]";
		}else{
			o << iesimo(i) << ", ";
		}
		i++;
	}	
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Lista<T> &l) {
	l.mostrar(os);
	return os;
}
#endif // LISTA_H_
