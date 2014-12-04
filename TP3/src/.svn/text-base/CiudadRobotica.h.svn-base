#ifndef CIUDAD_ROBOTICA_H
#define CIUDAD_ROBOTICA_H

namespace aed2 {

	class CiudadRobotica {

		public:

			CiudadRobotica();

			void Entrar(Conj<Caracteristica> car, Estacion e);

			void Mover(RUR rur, Estacion e);

			void Inspeccion(Estacion e);

			RUR proximoRUR() const;

			Mapa Mapa() const;

			typename Conj<Robot>::const_Iterador Robots() const;

			const Estacion Estacion(RUR rur) const;

			Conj<Caracteristica> tags(RUR rur) const;

			Nat nroInfracciones(RUR rur) const;

			typename Conj<Estacion>::const_Iterador Estaciones() const;

		private:

			struct Robot {

				Nat infr;
				RUR rur;
				bool estaActivo;
				Estacion est;
				Conj<Caracteristica> tag;
				DiccTrie<DiccTrie<bool>> permisos;
			
			};

			Lista<Robot> robots_;
			Arreglo< Conj<Robot>::const_Iterador > robRUR_;
			DiccTrie<ColaPrio> robEstacion_;
			Mapa mapa_;
			Nat proximoRUR_;

	};

}

#endif // CIUDAD_ROBOTICA_H