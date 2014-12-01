#include <iostream>
#include "Conjunto.hpp"

#include "mini_test.h"


void si_no_lo_agrego_no_pertenece() {
  Conjunto<char> c;
  ASSERT( !c.pertenece('a') );
}

void insertar_inserta() {
  Conjunto<int> c;
  c.insertar(42);
  ASSERT( c.pertenece(42) );
}

void insertar_noPertenece() {
	Conjunto<int> c;
  c.insertar(42);
  c.insertar(35);
  c.insertar(98);
  c.insertar(23);
  ASSERT( !c.pertenece(64) );
}

void maximo() {
	Conjunto<int> c;
  c.insertar(42);
  c.insertar(35);
  c.insertar(98);
  c.insertar(23);
  ASSERT(c.maximo() == 98);
}

void minimo() {
	Conjunto<int> c;
  c.insertar(42);
  c.insertar(35);
  c.insertar(98);
  c.insertar(23);
  ASSERT(c.minimo() == 23);
}

void cardinal_cero() {
	Conjunto<int> c;
	ASSERT(c.cardinal() == 0);
}

void cardinal_noCero() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(35);
	c.insertar(98);
	c.insertar(23);
	ASSERT(c.cardinal() == 4);
}

void cardinal_repetido() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(35);
	c.insertar(42);
	c.insertar(23);
	ASSERT(c.cardinal() == 3);
}

void remover() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(65);
	c.insertar(34);
	ASSERT(c.pertenece(42));
	c.remover(42);
	ASSERT(!c.pertenece(42));
}

void remover_repetidos() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(65);
	c.insertar(42);
	c.insertar(34);
	ASSERT(c.pertenece(42));
	c.remover(42);
	ASSERT(!c.pertenece(42));
}

void remover_vacio() {
	Conjunto<int> c;
	c.remover(42);
	ASSERT(!c.pertenece(42));
}

void remover_noPertenece() {
	Conjunto<int> c;
	c.insertar(65);
	c.insertar(12);
	c.insertar(34);
	c.remover(42);
	ASSERT(!c.pertenece(42));
}

void mostrar() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(65);
	c.insertar(34);
	c.insertar(42);
	c.mostrar(cout);
	ASSERT(true);
}

int main() {
    RUN_TEST(si_no_lo_agrego_no_pertenece);
    RUN_TEST(insertar_inserta);
    RUN_TEST(insertar_noPertenece);
    RUN_TEST(maximo);
    RUN_TEST(minimo);
    RUN_TEST(cardinal_cero);
    RUN_TEST(cardinal_noCero);
    RUN_TEST(cardinal_repetido);
    RUN_TEST(remover);
    RUN_TEST(remover_repetidos);
    RUN_TEST(remover_vacio);
    RUN_TEST(remover_noPertenece);
    RUN_TEST(mostrar);
    return 0;
}

