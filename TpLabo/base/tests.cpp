// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include "mini_test.h"
#include "arturo.h"


template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }

/*
 * Crea una mesa de int vacia y no agrega elementos
 */
void check_crear_mesa_vacia() {
  Arturo<int> mesa;

  ASSERT_EQ(mesa.esVacia(), true);

  ASSERT_EQ(mesa.tamanio(), 0);
}


void check_crear_mesa_borrar_elem_da_vacia() {
	Arturo <int> mesa;
	mesa.sentarArturo(0);
	int i, j;
	for(i = 1 ; i < 10; ++i){
		mesa.incorporarCaballero(i);
	}
	
	ASSERT_EQ(mesa.tamanio(), 10);
	for(j = 9; j >= 0; --j){
		mesa.expulsarCaballero(j);
	}
	ASSERT_EQ(mesa.esVacia(), true);
}

void check_comparacion_mesas_construidas_igual(){
	Arturo <int> mesa1;
	Arturo <int> mesa2;
	Arturo <int> mesa3;
	Arturo <int> mesa4;
	Arturo < Arturo<int> > mesa5;
	Arturo < Arturo<int> > mesa6;
	int i = 1;
	
	mesa1.sentarArturo(0);
	mesa2.sentarArturo(0);
	mesa3.sentarArturo(0);
	
	while(i < 20){
		mesa1.incorporarCaballero(i * i);
		mesa2.incorporarCaballero(i * i);
		mesa3.incorporarCaballero(i * i);
		i++;
	}
	
	mesa3.incorporarCaballero(1000);
	
	ASSERT(mesa2 == mesa1);
	ASSERT_EQ(mesa3 == mesa1, false);
	ASSERT_EQ(mesa2 == mesa4, false);
	ASSERT_EQ(mesa3 == mesa4, false);
	
	mesa5.sentarArturo(mesa1);
	mesa6.sentarArturo(mesa1);
	
	ASSERT(mesa5 == mesa6);
	
	mesa5.incorporarCaballero(mesa4);
	mesa6.incorporarCaballero(mesa3);
	
	ASSERT_EQ(mesa5 == mesa6, false);
}

/*
 * Crea un Arturo de Arturos.
 */
void check_arturo_de_arturo(){
	Arturo<string> mesa1;
	Arturo<string> mesa2;		
	
	Arturo< Arturo<string> > dobleMesa;
	
	dobleMesa.sentarArturo(mesa1);

	mesa2.sentarArturo("ARTURO");

	dobleMesa.incorporarCaballero(mesa2);

	ASSERT(dobleMesa.caballeroActual() == mesa1);
}
void check_copia(){
	Arturo<char> mesa1;
	int i = 1;
	char c = 'b';
	mesa1.sentarArturo('a');
	while (i < 20){
		mesa1.incorporarCaballero(c);
		c++;
		i++;
	}
	
	Arturo<char> mesa2(mesa1);

	ASSERT(mesa1.tamanio() == mesa2.tamanio());
	ASSERT(mesa1 == mesa2);
}


int main() {
  RUN_TEST(check_crear_mesa_vacia);
  RUN_TEST(check_crear_mesa_borrar_elem_da_vacia);
  RUN_TEST(check_arturo_de_arturo); 
  RUN_TEST(check_copia);
  RUN_TEST(check_comparacion_mesas_construidas_igual)

  return 0;
}

