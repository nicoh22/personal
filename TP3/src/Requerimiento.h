/*
 * Genera y manipula requerimientos con operadores logicos.
 *
 */

#ifndef REQUERIMIENTO_H
#define REQUERIMIENTO_H

#include "aed2/Conj.h"

namespace aed2 {

class Requerimiento {

	public:

		// Este constructor lo use parar hacer testing de algo en Mapa, en realidad
		// no es necesario y de hecho te rompe algunas cosas.
		// Requerimiento();

		// Analogo a nuevoTag de nuestro TAD. En realidad es simplemente un constructor.
		Requerimiento(const String tag);

		~Requerimiento();

		Requerimiento* AND(const Requerimiento* req) const;

		Requerimiento* OR (const Requerimiento* req) const;

		Requerimiento* NOT() const;

		/* Para que se le pueda aplicar el metodo directo a la clase,
		 * agregue una funcion auxiliar. Aun no testie esto.
		 */
		bool verifica(const Conj<String>& tags) const;

	private:

		bool verificaAux(const Requerimiento* req, const Conj<String>& tags) const;

		enum log_t {LAND, LOR, LNOT, CAR};

		Requerimiento(const log_t tipo, const Requerimiento* izq, const Requerimiento* der);

		const String caracteristica_;
		const log_t tipo_;
		const Requerimiento* izq_;
		const Requerimiento* der_;

};

}

#endif // REQUERIMIENTO_H