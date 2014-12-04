#include "ColaDePrioridad.h"

namespace aed2 {

ColaPrio::ColaPrio(): raiz_(NULL), padreUlt_(NULL), cant_(0) {}

ColaPrio::~ColaPrio(){
	while (cant_ > 0){
		desencolar();
	}
}

bool ColaPrio::esVacia(){
	return cant_ == 0;
}

itCola ColaPrio::encolar(Nat a, Nat b){
	cant_++;
	Nodo* n = new Nodo(a, b);
	float cantLog = log (cant_) / log(2);
	if ( raiz_ == NULL ){
		raiz_ = n;
	}
	else if ( padreUlt_ == NULL){
		padreUlt_ = raiz_;
		n->padre = raiz_;
		raiz_->izq = n;
	}
	else if ( cantLog == (int) cantLog ){
		padreUlt_ = busqIzq(raiz_);
		n->padre = padreUlt_;
		padreUlt_->izq = n;
	}
	else{
		padreUlt_= busqTransversal(padreUlt_);
		n->padre = padreUlt_;
		padreUlt->izq = n;	
	}
	subir(n);
	return crearIt(n);
}

tupla ColaPrio::desencolar(){
	tupla res = tupla(raiz_->rur_, raiz_->infr_);
	Nodo* ult;
	if (padreUlt_ == NULL){ //Quiere decir solo hay raiz!
		delete (raiz_);
		raiz_ = NULL;
	}else{	
		if ( padreUlt_->der_ != NULL && padreUlt_->izq_ != NULL){
			padreUlt_ = BusqTransvInv(padreUlt_); 
		}
		if ( padreUlt_->der != NULL ) {
			ult = padreUlt_->der_;
			padreUlt_->der_ = NULL;
		}else {
			ult = padreUlt_->izq_;
			padreUlt_->izq_ = NULL;
		}
		ult->padre_ = NULL;
		ult->izq_ = raiz_->izq_;
		ult->der_ = raiz_->der_;
		ult->izq_->padre_ = ult;
		ult->der_->padre_ = ult;
		delete (raiz_);
		raiz_ = ult; 
		bajar(ult);
	}
	cant--;
	return res;
}

void ColaPrio::subir(Nodo* n){
	Nodo* parent = n->padre_;
	while ( parent != NULL && mayorPrio(n, parent) ){
		if (parent == padreUlt_) {
			padreUlt_ = n;
		}else if (n == padreUlt_){
			padreUlt_ = parent;
		}
		if (parent == raiz_){
			raiz_ = n;
		}
		swapPadreHijo(parent, n);
		parent = n->padre_;
	}		
}

void ColaPrio::bajar(Nodo* n){
	while( n->izq_ !=NULL && mayorPrio(n->izq_, n) ||
		 n->der_ != NULL && mayorPrio(n->der_, n)){
		if ( n->der_ != NULL && mayorPrio(n->der_, n->izq_) ){
			if ( n == raiz_ ){
				raiz_ = n->der_;
			}
			if (n == padreUlt_){
				padreUlt_ = n->der_;
			}else if ( n->der_==padreUlt_){
				padreUlt_ = n;
			}
			swapPadreHijo(n, n->der_);
		}else{
			if ( n == raiz_ ){
				raiz_ = n->izq_;
			}
			if (n == padreUlt_){
				padreUlt_ = n->izq_;
			}else if ( n->izq_==padreUlt_){
				padreUlt_ = n;
			}
			swapPadreHijo(n, n->izq_);
		}	
	}	
}

bool ColaPrio::mayorPrio(Nodo* n1, Nodo* n2){
	return ( n2->infr_ == n1->infr_ )? n1->rur > n2->rur : n1->infr_ > n2->infr_;
}

void ColaPrio::swapPadreHijo(Nodo* parent, Nodo* hijo){
	Nodo* aux;
	if ( parent->padre_ != NULL){
		if (parent->padre_->der_ == parent){
			parent->padre_->der_ = hijo;
		}else{
			parent->padre_->izq_ = hijo;
		}
	}
	
	hijo->padre_ = parent->padre_;
	parent->padre = hijo;
	if ( hijo->izq_ != NULL){
		hijo->izq_->padre_ = parent;
	}
	if ( hijo->der_ != NULL){
		hijo->der_->padre_ = parent;
	}
	
	if (parent->der == hijo){
		aux = parent->izq_;
		aux->padre_ = hijo;
		parent->der_ = hijo->der_;
		parent->izq_ = hijo->izq_;
		hijo->izq_ = aux;
		hijo->der_ = parent;
	}else{
		aux = parent->der_;
		aux->padre_ = hijo;
		parent->der_ = hijo->der_;
		parent->izq_ = hijo->izq_;
		hijo->izq_ = parent;
		hijo->der_ = aux;
	}
}

Nodo* ColaPrio::busqIzq(Nodo* n){
	Nodo* actual = n;
	while(actual->izq_ != NULL){
		actual = actual->izq_;
	}
	return actual;
}

Nodo* ColaPrio::busqDer(Nodo* n){	
	Nodo* actual = n;
	while(actual->der_ != NULL){
		actual = actual->der_;
	}
	return actual;
}

Nodo* ColaPrio::busqTransversal(Nodo* n){
	Nodo* parent = n->padre_;
	Nodo* act = n;
	while( parent =! NULL && parent->der_ == act){
		act = parent;
		parent = parent->padre_;
	}
	act = parent->der_;
	while(act->izq_ != NULL){
		act = act->izq_;
	}
	return act;
}

Nodo* ColaPrio::busqTransvInv(Nodo* n){
	Nodo* parent = n->padre_;
	Nodo* act = n;
	while( parent =! NULL && parent->izq_ == act){
		act = parent;
		parent = parent->padre_;
	}
	act = parent->izq_;
	while(act->der_ != NULL){
		act = act->der_;
	}
	return act;
}

typename ColaPrio::Iterador ColaPrio::CrearIt(Nodo* n){
	return Iterador(this, n);
}

typename ColaPrio::tupla ColaPrio::Iterador::siguiente(){
	return tupla(nodoSig_->rur_, nodoSig_->infr_);
}

void ColaPrio::Iterador::elimSig(){
	Nodo* ult;
	if ( cola_->raiz_ == nodoSig_){ cola_.desencolar() }
	else{
		if ( cola_->padreUlt_->der_ == NULL){
			ult = cola_->padreUlt_->izq_;
		}else{
			ult = cola_->padreUlt_->der_;
		}
		bool deboRestaurar? = false;
		if( !esDescendiente(ult, nodoSig_) ){
			ult = cola_.busqDer(nodoSig_);
			ult->padre_->der_ = NULL;
			deboRestaurar? = true;
		}
		ult->padre_ = nodoSig_->padre;
		ult->izq_ = nodoSig_->izq;
		ult->der_ = nodoSig_->der;
		ult->der_->padre = ult;
		ult->izq_->padre =ult;
		delete nodoSig;
		if ( deboRestaurar? ){
			Nodo* colaUlt = cola_.busqDer(ult);
			if ( cola_->padreUlt_->der == NULL){
				colaUlt->der_ = cola_->padreUlt_->izq_;
				cola_->padreUlt_->izq_ = NULL;
			}else{
				colaUlt->der_ = cola_->padreUlt_->der_;
				cola_->padreUlt_->der_ = NULL;
			}
			cola_.subir(colaUlt->der);
		}
		
		cola_.bajar(ult);
	}
}

bool ColaPrio::esDescendiente(Nodo* n1, Nodo* n2){
	bool res = false;
	while( n1->padre_ != NULL){
		if (n2 == n1) { res = true}
		n1 = n1->padre_;
	}
	return res;
}
