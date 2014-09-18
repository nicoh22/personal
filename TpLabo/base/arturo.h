#ifndef ARTURO_H_
#define ARTURO_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * IMPORTANTE!
 * Se puede asumir que el tipo T tiene constructor por copia y operator == y operator <<
 * No se puede asumir que el tipo T tenga operator =
 */
template<typename T>
class Arturo {

  public:

	/*
	 * Crea una mesa redonda nueva sin caballeros.
	 */	
	Arturo();

	/*
	 * Una vez copiados, ambos Arturos deben ser independientes, 
	 * es decir, cuando se borre uno no debe borrar la otra.
	 */	
	Arturo(const Arturo<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~Arturo();

	/*
	* Arturo se sienta siempre primero.
	* 
	* PRE: La mesa esta vacía.
	* POST: Arturo está hablando y es el único en la mesa.
	*/
	void sentarArturo(const T& a);

	/*
	 * Agrega un nuevo caballero a la mesa. El nuevo caballero se sentará
	 * a la derecha de Arturo. No se pueden agregar caballeros repetidos.
	 *
	 * PRE: Arturo esta sentado en la mesa y el nuevo caballero c no está sentado aún
	 * POST: El caballero c se sienta a la derecha de Arturo.
	 */
	void incorporarCaballero(const T& c);
	
	/*
	 * Elimina de la mesa al caballero pasado por parámetro. En caso de borrar al 
	 * caballeroActual, pasará a ser el actual que esté sentado a su derecha.
	 * Si se expulsa al caballero interrumpido por Arturo, Arturo sigue hablando
	 * como si nunca hubiera interrumpido, es decir, el próximo es el de la
	 * derecha de Arturo y el anterior es el de la izquierda de Arturo.
	 *
	 * IMPORTANTE: Sólo se puede borrar a Arturo, si es el único sentado en la mesa.
	 * 
     * PRE: c puede ser Arturo sólo si la mesa tiene tamaño 1
     * POST: El caballero c no está más sentado en la mesa. 
	 */
	void expulsarCaballero(const T& c);
	
    /*
	 * Devuelve al caballero que está hablando en este momento.
	 *
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	const T& caballeroActual() const;
	
	/*
	 * Cambia el turno del caballero actual, al de su derecha. Si Arturo
	 * interrumpió, el turno pasa al de la derecha del interrumpido.
	 * El resultado no tiene interrumpido.
	 * 
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	void proximoCaballero();

	/*
	 * Cambia el turno del caballero actual, al de su izquierda. Si Arturo
	 * interrumpió, el turno pasa al de la izquierda del interrumpido. 
	 * Esta función puede ser llamada varias veces seguidas.
	 * El resultado no tiene interrumpido.
	 * 
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	void caballeroAnterior();

	/*
	* Arturo puede elegir que es su turno de hablar en cualquier momento e 
	* interrumpir al que está hablando. Arturo termina de hablar por interrupción
	* cuando se pasa al proximoCaballero() o al caballeroAnterior().
	*
	* PRE: Si Arturo está hablando, no se puede interumpir a sí mismo.
	*/
	void hablaArturo();

    /*
	 * Indica si Arturo está sentado en la mesa. 
	 */
	bool arturoPresente() const;
	
	/*
	* Arturo quiere separar un conflicto y por lo tanto cambia su posición y
	* se sienta a la derecha del caballero pasado como parámetro.
	* Tanto como el que está hablando como el interrumpido siguen siendo los mismos.
	* Ejemplos:
	*  cambiarDeLugar(c1) de la mesa: [Arturo(c0), c1, c2] deja la mesa: [Arturo(c0), c2, c1]
	*  cambiarDeLugar(c1) de la mesa: [c1, c2, Arturo(c0)] deja la mesa: [c1, Arturo(c0), c2]
	*  cambiarDeLugar(c2) de la mesa: [c1, c2, Arturo(c0), c3] deja la mesa: [c1, c2, Arturo(c0), c3]
	*
	* PRE: La mesa tiene al menos tamaño 3
	* POST: Arturo está sentado a la derecha de c
	*/
	void cambioDeLugar(const T& c);

	/*
	 * Dice si la mesa tiene o no caballeros sentados.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de caballeros en la mesa.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las mesas son iguales.
	 * Dos mesas son iguales cuando todos sus caballeros son iguales,
	 * están sentados en las mismas posiciones, y además tanto Arturo,
	 * como el que está hablando, como el interrumpido (si hubiera) son iguales.
	 */
	bool operator==(const Arturo<T>&) const;	
	
	/*
	 * Debe mostrar la mesa por el ostream os (y retornar el mismo).
	 * Mesa vacia: []
	 * Mesa con caballero c0 como Arturo: [ARTURO(c0)]
	 * Mesa con 2 caballeros (Arturo está hablando): [ARTURO(c0), c1]
	 * Mesa con 3 caballeros (Arturo está hablando): [ARTURO(c0), c1, c2]
	 * Mesa con 3 caballeros (c1 está hablando): [c1, c2, ARTURO(c0)]
	 * Mesa con 3 caballeros (c1 fue interrumpido): [ARTURO(c0),*c1,c2]
	 */
	ostream& mostrarArturo(ostream& os) const;
	
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	Arturo<T>& operator=(const Arturo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		Nodo();
		Nodo(const T & elemento);
		Nodo(const Nodo & n);
		~Nodo();
		
		T caballero;
 		Nodo *sig;
 		Nodo *ant;
		
	};

	int len;
	Nodo *rey;
	Nodo *orador;
	bool interrupcion;
	
};

template<class T>
ostream& operator<<(ostream& out, const Arturo<T>& a) {
	return a.mostrarArturo(out);
}

// Implementación a hacer por los alumnos.

template <typename T>
int Arturo<T>::tamanio() const{
	return len;
};

template <typename T>
bool Arturo<T>::esVacia() const{
	return tamanio() == 0;
};

template <typename T>
bool Arturo<T>::arturoPresente() const{
	return rey != NULL;
}

template <typename T>
Arturo<T>::Arturo():len(0), rey(NULL), orador(NULL), interrupcion(false){} 

template <typename T>
void Arturo<T>::sentarArturo(const T& a){
	Nodo *nuevo = new Nodo(a);
	this->rey = nuevo;
	this->orador = nuevo;
	len++;
}

template <typename T>
void Arturo<T>::incorporarCaballero(const T& c){
	Nodo *nuevo = new Nodo(c);
	Nodo *derechoActual;

	nuevo->ant = rey;
	derechoActual = rey->sig;
	rey->sig = nuevo;
	
	if (derechoActual != NULL){
		derechoActual->ant = nuevo; nuevo->sig = derechoActual;	
	}else{
		nuevo->sig = rey; rey->ant = nuevo;
	}
	len++;
}

template <typename T>
void Arturo<T>::expulsarCaballero(const T& c){
	 int n(0);
	 Nodo *actual = orador;
	 if (tamanio() > 1){
		if(tamanio() == 2){
			actual = rey->sig;
			rey->sig = NULL;
			rey->ant = NULL;
			interrupcion = false;
			orador = rey;
		}else{
			while (n < tamanio()){
			 	if (actual->caballero == c){
		 			actual->ant->sig = actual->sig;
		 			actual->sig->ant = actual->ant;
			 		n = tamanio();
			 		if (orador == actual){
			 			if(interrupcion){
			 				interrupcion = false;
			 				orador = rey;	
			 			}else{
			 				orador = actual->sig;	
			 			}
			 		}
			 	}else{
			 		actual = actual->sig;
			 		n++;
			 	}
			}
		}
         }else{
         	orador = NULL; rey = NULL; interrupcion = false;
         }
         len--;
         delete actual;	
}

template <typename T>
const T& Arturo<T>::caballeroActual() const{
	return interrupcion? rey->caballero : orador->caballero;
}

template <typename T>
Arturo<T>::Arturo(const Arturo<T>& a):len(0), rey(NULL), orador(NULL), interrupcion(false){
	if(a.tamanio() > 0){
		sentarArturo(a.rey->caballero);
		int n(0);
		interrupcion = a.interrupcion;
		Nodo *actual = a.rey->ant;
		
		if(a.orador->caballero == rey->caballero){
			orador = rey;
		}
		
		while(n < a.tamanio() - 1){
			if(actual == a.orador){
				orador = new Nodo(a.orador->caballero);
				orador->ant = rey;
				if(tamanio() > 2){
					orador->sig = rey->sig;
					rey->sig->ant = orador;
					rey->sig = orador;
				}else{
					orador->sig = rey;
					rey->ant = orador;
				}			
				len++;
			}else{
				incorporarCaballero(actual->caballero);
			}
			actual = actual->ant;
			n++;	
		}	
	}
		
}




template <typename T>
void Arturo<T>::proximoCaballero(){
	interrupcion = false;
	orador = orador->sig;
}

template <typename T>
void Arturo<T>::caballeroAnterior(){
	interrupcion = false;
	orador = orador->ant;
}

template <typename T>
void Arturo<T>::hablaArturo(){
	interrupcion = true;
}

template <typename T>
void Arturo<T>::cambioDeLugar(const T& c){
	if(rey->ant->caballero != c){
		rey->ant->sig = rey->sig;
		rey->sig->ant = rey->ant;	
		Nodo *actual = rey->sig;
		int n(0);
		while (n < tamanio() - 1){
			
			if(actual->caballero = c){
				rey->sig = actual->sig;
				rey->ant = actual;
				actual->sig->ant = rey;
				actual->sig = rey; 
				n = tamanio();	
			}else{
				actual = actual->sig;
			}
			n++;		
		}
	}
}

template <typename T>
bool Arturo<T>::operator==(const Arturo<T>& otra) const{
	if (tamanio() != otra.tamanio() || interrupcion != otra.interrupcion){return false;
	}else{
		if(tamanio() == 0){return true;
		}else{
		int n(0);
		Nodo *actualOtra = otra.orador;
		Nodo *actualThis = orador;
			while(n < tamanio()){
				if(!(actualOtra->caballero == actualThis->caballero)){
					return false;
				}
			
				actualOtra = actualOtra->sig;
				actualThis = actualThis->sig;
				n++;
			}
			return rey->caballero == otra.rey->caballero;
		}
	}
}

template <typename T>
Arturo<T>::~Arturo(){
	Nodo* actual = rey;
	Nodo* aBorrar;
	while(tamanio() > 1){
		aBorrar = actual;
		actual = actual->sig;
		if(aBorrar != rey){
			expulsarCaballero(aBorrar->caballero);
		}
	}
	if(arturoPresente()){
		expulsarCaballero(rey->caballero);
	}
}

template <typename T>
ostream& Arturo<T>::mostrarArturo(ostream& os) const{
	if(esVacia()){
		os<<"[]";
	}else{
		int n(0);
		os<<"[";
		Nodo *actual;
		if(interrupcion){
			actual = rey;
		}else{
			actual = orador;
		}
		
		while(n < tamanio()){
			if (actual == rey){
				os << "ARTURO(" << actual->caballero <<"), ";
			}else{
				if (interrupcion && actual == orador) {
					os << "*" << actual->caballero << ", ";
				}else{
					os << actual->caballero << ", ";
				}		
				}
			actual = actual->sig;
			n++;
		}
		char c = 8;
		os<< c << c <<"]";
	}
	return os;
}
	/*
	 * Debe mostrar la mesa por el ostream os (y retornar el mismo).
	 * Mesa vacia: []
	 * Mesa con caballero c0 como Arturo: [ARTURO(c0)]
	 * Mesa con 2 caballeros (Arturo está hablando): [ARTURO(c0), c1]
	 * Mesa con 3 caballeros (Arturo está hablando): [ARTURO(c0), c1, c2]
	 * Mesa con 3 caballeros (c1 está hablando): [c1, c2, ARTURO(c0)]
	 * Mesa con 3 caballeros (c1 fue interrumpido): [ARTURO(c0),*c1,c2]
	 */



template <typename T>
Arturo<T>::Nodo::Nodo() :
caballero(), sig(NULL), ant(NULL) {}
template <typename T>
Arturo<T>::Nodo::Nodo(const T & c) :
caballero(c), sig(NULL), ant(NULL){}
template <typename T>
Arturo<T>::Nodo::Nodo(const Nodo & c) :
caballero(c.caballero), sig(NULL), ant(NULL)  {}
template <typename T>
Arturo<T>::Nodo::~Nodo(){}

#endif //ARTURO_H_
