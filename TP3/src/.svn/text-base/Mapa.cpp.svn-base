#include "Mapa.h"

/* Los constructores por default de los atributos internos ya deberian
 * inicializar todos los valores de forma correcta.
 */

Mapa::Mapa() {}

void Mapa::Agregar(Estacion e)
{
	estaciones_.Agregar(e);
}

// void Mapa::conectarAux(const Estacion e1, const Estacion e2)
// {
// 	 Como los pararmetros que se le pasan a una funcion se guardan en el stack,
// 	 * debo hacer una copia de idSenda en el heap. Caso contrario corro el riesgo
// 	 * de que esa posicion de memoria en particular sea overwritten, causando que
// 	 * el significado de mi diccionario apunte a cualquier lado.
	 
// 	Nat idSenda = nroConecciones_;
// 	if (!idConeccion_.Definido(e1)) {
// 		DiccString<Nat>* diccAux = new DiccString<Nat>;
// 		diccAux->Definir(e2, idSenda);
// 		idConeccion_.Definir(e1,*diccAux);
// 	} else {
// 		idConeccion_.Significado(e1).Definir(e2, idSenda);
// 	}
// }

void Mapa::Conectar(const Estacion e1, const Estacion e2, const Requerimiento* req)
{
	typename Mapa::Senda* senda = new Mapa::Senda();
	senda->e1 = e1;
	senda->e2 = e2;
	senda->req = req;

	// conectarAux(e1, e2);
	// conectarAux(e2, e1);

	sendas_.AgregarRapido(*senda);

	// nroConecciones_++;

}

typename Conj<Estacion>::const_Iterador Mapa::Estaciones() const
{
	Conj<Estacion>::const_Iterador it = estaciones_.CrearIt();

	return it;
}

bool Mapa::existeConeccion(const Estacion e1, const Estacion e2) const
{
	typename Conj<Mapa::Senda>::const_Iterador it = sendas_.CrearIt();
	typename Mapa::Senda sendaActual;
	bool encontrado = false;

	while (it.HaySiguiente() && !encontrado)
	{
		sendaActual = it.Siguiente();

		if ((sendaActual.e1 == e1 && sendaActual.e2 == e2) || 
			(sendaActual.e1 == e2 && sendaActual.e2 == e1))
		{
			encontrado = true;
		}

		it.Avanzar();
	}

	return encontrado;
}

const Requerimiento Mapa::Restriccion(const Estacion e1, const Estacion e2) const
{
	typename Conj<Mapa::Senda>::const_Iterador it = sendas_.CrearIt();
	typename Mapa::Senda sendaActual;
	bool encontrado = false;

	while (it.HaySiguiente() && !encontrado)
	{
		sendaActual = it.Siguiente();

		if ((sendaActual.e1 == e1 && sendaActual.e2 == e2) || 
			(sendaActual.e1 == e2 && sendaActual.e2 == e1))
		{
			encontrado = true;
		}

		it.Avanzar();
	}

	return *sendaActual.req;

}

/* Hay que checkear bien que mi manejo de los arreglos es correcto.
 * En C++ parece que uno solo puede devolver un puntero al primer elemento, y 
 * habria que verificar que la forma en la que asigno esta bien.
 *
 * El modulo de nivel superior Ciudad no va a necesitar saber la longitud de este
 * arreglo, dado que va a solicitar el id de la senda al necesitarlo.
 */
// bool* Mapa::construirPermisos(const Conj<Caracteristica> car) const
// {
// 	bool* permisos = new bool[nroConecciones_];

// 	typename Conj<Senda>::const_Iterador it = sendas_.CrearIt();
// 	typename Mapa::Senda sendaActual;

// 	while (it.HaySiguiente())
// 	{
// 		sendaActual = it.Siguiente();
// 		permisos[nroConeccion(sendaActual.e1, sendaActual.e2)] = sendaActual.req->verifica(car); 
// 	}

// 	return permisos;

// }

// Nat Mapa::nroConeccion(const Estacion e1, const Estacion e2) const
// {
// 	return idConeccion_.Significado(e1).Significado(e2);
// }

