#include "Requerimiento.h"

namespace aed2 {

// Requerimiento::Requerimiento() : caracteristica_(""), tipo_(CAR),
// 								izq_(NULL), der_(NULL) {}

Requerimiento::Requerimiento(const String tag) : caracteristica_(tag), tipo_(CAR), 
								izq_(NULL), der_(NULL) {}

// Constructor privado.
Requerimiento::Requerimiento(const log_t tipo, const Requerimiento* izq,
								const Requerimiento* der) : tipo_(tipo), izq_(izq), 
								der_(der) {}

Requerimiento::~Requerimiento() 
{
	if(this->izq_)
		delete this->izq_;

	if(this->der_)
		delete this->der_;

	delete this;
}

Requerimiento* Requerimiento::AND(const Requerimiento* req) const
{ 
	return new Requerimiento(LAND, this, req);
}

Requerimiento* Requerimiento::OR(const Requerimiento* req) const
{ 
	return new Requerimiento(LOR, this, req);
}

Requerimiento* Requerimiento::NOT() const
{ 
	return new Requerimiento(LNOT, NULL, this);
}

bool Requerimiento::verificaAux(const Requerimiento* req, const Conj<String>& tags) const
{
	bool aux = false;
	if (req->tipo_ == CAR) {
		aux = tags.Pertenece(req->caracteristica_);
	} else if (req->tipo_ == LAND) {
		aux = verificaAux(req->izq_, tags) && verificaAux(req->der_, tags);
	} else if (req->tipo_ == LOR) {
		aux = verificaAux(req->izq_, tags) || verificaAux(req->der_, tags);
	} else {
		aux = !verificaAux(req->der_, tags);
	}
	return aux;
}

bool Requerimiento::verifica(const Conj<String>& tags) const
{
	return verificaAux(this, tags);
}

}