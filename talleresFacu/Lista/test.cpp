#include <iostream>
#include <assert.h>
#include "Lista.h"

template<typename T>
void testearMostrar(const T& t1, const T& t2, const T& t3, const T& t4) {
	Lista<T> l;
	l.agAtras(t1);
	l.agAtras(t2);
	l.agAtras(t3);
	l.agAtras(t4);
	std::cout << l << std::endl;
}

template<typename T>
void testearVacia() {
	Lista<T> l1, l2;
	assert( l1.longitud() == 0 );
	assert( l1 == l2 );
}

template<typename T>
void testearAgAdelante(const T& t) {
	Lista<T> l;
	l.agAdelante( t );

	assert( l.longitud() == 1 );
	assert( l.iesimo( 0 ) == t );

	l.eliminar( 0 );

	assert( l.longitud() == 0 );
}

template<typename T>
void testearAgAtras(const T& t) {
	Lista<T> l;
	l.agAdelante( t );

	assert( l.longitud() == 1 );
	assert( l.iesimo( 0 ) == t );

	l.eliminar( 0 );

	assert( l.longitud() == 0 );
}

template<typename T>
void testearEliminar(const T& t1, const T& t2) {
	{
		Lista<T> l;
		l.agAtras( t2 );
		l.agAdelante( t1 );

		assert( l.longitud() == 2 );
		assert( l.iesimo( 0 ) == t1 );
		assert( l.iesimo( 1 ) == t2 );

		l.eliminar( 0 );

		assert( l.longitud() == 1 );
		assert( l.iesimo( 0 ) == t2 );
	}
	{
		Lista<T> l;
		l.agAtras( t2 );
		l.agAdelante( t1 );

		assert( l.longitud() == 2 );
		assert( l.iesimo( 0 ) == t1 );
		assert( l.iesimo( 1 ) == t2 );

		l.eliminar( 1 );

		assert( l.longitud() == 1 );
		assert( l.iesimo( 0 ) == t1 );
	}
}

template<typename T>
void testearCambiar(const T& t1, const T& t2, const T& t3, const T& t4) {
	{
		Lista<T> l1;
		l1.agAtras(t1);
		l1.agAtras(t2);
		l1.agAtras(t3);

		Lista<T> l2;
		l2.agAtras(t4);
		l2.agAtras(t2);
		l2.agAtras(t3);

		l1.iesimo(0) = t4;
		assert(l1 == l2);
	}
	{
		Lista<T> l1;
		l1.agAtras(t1);
		l1.agAtras(t2);
		l1.agAtras(t3);

		Lista<T> l2;
		l2.agAtras(t1);
		l2.agAtras(t4);
		l2.agAtras(t3);

		assert( !( l1 == l2 ) );

		l1.iesimo(1) = t4;

		assert(l1 == l2);
	}
	{
		Lista<T> l1;
		l1.agAtras(t1);
		l1.agAtras(t2);
		l1.agAtras(t3);

		Lista<T> l2;
		l2.agAtras(t1);
		l2.agAtras(t2);
		l2.agAtras(t4);

		assert( !( l1 == l2 ) );

		l1.iesimo(2) = t4;

		assert(l1 == l2);
	}
}

template<typename T>
void testearLista(const T& t1, const T& t2, const T& t3, const T& t4)
{
	std::cout << "testeando: ";
	testearMostrar<T>(t1, t2, t3, t4);
	testearVacia<T>();
	testearAgAdelante<T>(t1);
	testearAgAtras<T>(t1);
	testearEliminar(t1, t2);
	testearCambiar(t1, t2, t3, t4);
}

int main() {

	{
		testearLista<int>( -1, 5, -5, 13 );
	}

	{
		testearLista<std::string>( "uno", "dos", "tres", "cuatro" );
	}

	{
		Lista<Nat> l_nat1;
		l_nat1.agAtras(0);

		Lista<Nat> l_nat2;
		l_nat2.agAtras(20);
		l_nat2.agAtras(20);
		l_nat2.agAdelante(20);
		l_nat2.agAdelante(20);

		Lista<Nat> l_nat3;

		Lista<Nat> l_nat4;
		l_nat4.agAdelante(2);
		l_nat4.agAdelante(1);
		l_nat4.agAtras(3);
		l_nat4.agAtras(2);
		l_nat4.agAtras(1);

		testearLista<Lista<Nat> >(l_nat1, l_nat2, l_nat3, l_nat4);
	}

  return 0;
}
