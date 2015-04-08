#include "Lista.h"
#include "mini_test.h"

void lista_vacia_mide_cero() {
  Lista<int> l;
  ASSERT_EQ( l.longitud(), 0 );
}

void listas_vacias_son_iguales() {
  Lista<int> l1, l2;
  ASSERT( l1 == l2 );
}

void agregar_un_elemento_incrementa_logitud() {
  Lista<char> l;
  l.agAdelante('a');
  ASSERT_EQ( l.longitud(), 1 );
}

void agregar_adelante_pone_al_principio() {
  Lista<char> l;
  l.agAdelante('a');
  ASSERT_EQ( l.iesimo( 0 ), 'a' );
}

void eliminar_unico_elemento_deja_lista_vacia() {
  Lista<char> l;
  l.agAdelante('a');
  ASSERT_EQ( l.longitud(), 1 );
  l.eliminar(0);
  ASSERT_EQ( l.longitud(), 0 );
}

void iesimo_puede_modificar_lista() {
  Lista<char> l;
  l.agAdelante('a');
  ASSERT_EQ(l.iesimo(0), 'a');

  l.iesimo(0) = 'c';
  ASSERT_EQ(l.iesimo(0), 'c');

  ASSERT_EQ(l.longitud(), 1);
}

int main() {
  RUN_TEST(lista_vacia_mide_cero);
  RUN_TEST(listas_vacias_son_iguales);
  RUN_TEST(agregar_un_elemento_incrementa_logitud);
  RUN_TEST(agregar_adelante_pone_al_principio);
  RUN_TEST(eliminar_unico_elemento_deja_lista_vacia);
  RUN_TEST(iesimo_puede_modificar_lista);
  return 0;
}
