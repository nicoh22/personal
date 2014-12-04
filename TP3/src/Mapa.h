#ifndef MAPA_H
#define MAPA_H

#include "DiccString.h"
#include "Requerimiento.h"
#include "aed2/Conj.h"
#include "Tipos.h"

/* Muchas cosas estan comentadas porque eran ideas que tenia para
 * simplificar y emprolijar mucho la forma en la que funcionan los
 * modulos. Sin embargo, como no esta permitido desviarse del 
 * disenio, no tuve mas opcion que comentarlo. Recordar que gran 
 * parte del codigo comentado se puede reciclar para armar despues
 * la CiudadRobotica.
 */

namespace aed2 {

	class Mapa {

		public:

			Mapa(); // Analogo a vacio del Modulo.

			void Agregar(Estacion e);

			void Conectar(const Estacion e1, const Estacion e2, const Requerimiento* req);

			typename Conj<Estacion>::const_Iterador Estaciones() const;

			bool existeConeccion(const Estacion e1, const Estacion e2) const;

			const Requerimiento Restriccion(const Estacion e1, const Estacion e2) const;

			// bool* construirPermisos(const Conj<Caracteristica> car) const;

			// Nat nroConeccion(const Estacion e1, const Estacion e2) const;

		private:

			// void conectarAux(const Estacion e1, const Estacion e2);

			struct Senda {

				Estacion e1;
				Estacion e2;
				const Requerimiento* req;

			};

			// DiccString< DiccString<Nat> > idConeccion_;
			Conj<Estacion> estaciones_;
			Conj<Senda> sendas_;
			// Nat nroConecciones_;

	};

}


#endif // MAPA_H