#ifndef COLA_DE_PRIORIDAD_H
#define COLA_DE_PRIORIDAD_H

namespace aed2 {

class ColaPrio {

	public:
	
		// Forward declarations
		class Iterador;
		struct tupla;

		ColaPrio();
		
		~ColaPrio();	
		
		Iterador encolar(Nat a, Nat b);
		
		tupla desencolar();
		
		bool vacia();
	
		struct tupla { // devuelvo este struct en desencolar y sig del iterador

			tupla(Nat a, Nat b):rur_(a), infr_(b){};
			Nat rur_;
			Nat infr_;

		};
	
		class Iterador { 

			public:
				//no tiene crearIt publico la unica forma de tener
				//un iterador es asignando el it creado por encolar.
				
				Iterador() : cola_(NULL), nodoSig_(NULL) {};

				Iterador(const typename ColaPrio::Iterador& otro):
					cola_(otro.cola_),
					nodoSig_(otro.nodoSig_){} 
					
				tupla siguiente() const; // devuelve el elemento apuntado
				void elimSig(); //borra de la cola el elemento
			
			private:
			
				Iterador(ColaPrio* c, typename ColaPrio::Nodo* n)
					:cola_(c), nodoSig_(n){}
					
				ColaPrio* cola_;
				typename ColaPrio::Nodo* nodoSig_;
				
				friend typename ColaPrio::Iterador ColaPrio::CrearIt(typename ColaPrio::Nodo* n);
				
		};

	private:
	
		struct Nodo {

			Nodo(Nat a, Nat b):rur_(a), infr_(b){};
			Nat rur_;
			Nat infr_;
			Nodo* padre_;
			Nodo* izq_;
			Nodo* der_;

		};

		// Faltan mas Funciones Auxiliares
		Iterador CrearIt(typename ColaPrio::Nodo* n); // no estoy seguro de esto

		bool mayorPrio(Nodo* n1, Nodo* n2);
		void swapPadreHijo(Nodo* parent, Nodo* hijo);
		Nodo* busqIzq(Nodo* n);
		Nodo* busqDer(Nodo* n);
		Nodo* busqTransversal(Nodo* n);
		Nodo* busqTransvInv(Nodo* n);
		bool esDescendiente(Nodo* n1, Nodo* n2);
		void subir(Nodo* n);
		void bajar(Nodo* n);
		
		Nodo* raiz_;
		Nodo* padreUlt_;
		Nat cant_;
		
		
		
};

}

#endif // COLA_DE_PRIORIDAD_H
