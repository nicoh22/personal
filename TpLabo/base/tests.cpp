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

void check_comparacion(){
	Arturo <int> mesa1;
	Arturo <int> mesa2;
	Arturo <int> mesa3;
	Arturo <int> mesa4;
	Arturo < Arturo<int> > mesa5;
	Arturo < Arturo<int> > mesa6;
	int i = 1;
	
	ASSERT(mesa2 == mesa1);
	
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
	
	mesa1.proximoCaballero();
	ASSERT_EQ(mesa1 == mesa2, false);
	
	
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

void check_arturo_de_arturo_avanz(){
	Arturo<char> mesa1;
	Arturo< Arturo<char> > mesa2;
	Arturo<char> mesa3;
	mesa2.sentarArturo(mesa1);
	mesa2.incorporarCaballero(mesa3);
	
	cout << "\n" << " Mesa0.1: " << mesa2 << "\n";
	mesa1.sentarArturo('a');
	mesa1.incorporarCaballero('e');
	mesa1.incorporarCaballero('d');
	mesa1.incorporarCaballero('c');
	mesa1.incorporarCaballero('b');
	
	mesa2.incorporarCaballero(mesa1);
	cout << " Mesa1.0: " << mesa2 << "\n";
	
	mesa1.proximoCaballero();
	mesa1.hablaArturo();
	
	mesa2.incorporarCaballero(mesa1);
	cout << " Mesa2.0: " << mesa2 << "\n";
	mesa2.proximoCaballero();
	cout << " Mesa2.5: " << mesa2 << "\n";
	mesa2.expulsarCaballero(mesa1);
	cout << " Mesa3.0: " << mesa2 << "\n";
	
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
	
	mesa1.proximoCaballero();
	mesa1.proximoCaballero();
	mesa1.expulsarCaballero('e');
	
	Arturo<char> mesa3(mesa1);
	ASSERT(mesa1 == mesa3);
	
	
}

void check_cambio_lugar(){
	Arturo<int> mesa1;
	
	mesa1.sentarArturo(0);
	mesa1.incorporarCaballero(4);
	mesa1.incorporarCaballero(3);
	mesa1.incorporarCaballero(2);
	mesa1.incorporarCaballero(1);
	
	mesa1.cambioDeLugar(1);
	
	ASSERT_EQ(mesa1.caballeroActual(), 0);
	mesa1.proximoCaballero();
	ASSERT_EQ(mesa1.caballeroActual(), 2);
	
	Arturo<char> mesa2;
	mesa2.sentarArturo('a');
	mesa2.incorporarCaballero('c');
	mesa2.incorporarCaballero('b');
	
	mesa2.cambioDeLugar('b');
	ASSERT_EQ(mesa2.caballeroActual(), 'a');
	mesa2.proximoCaballero();
	ASSERT_EQ(mesa2.caballeroActual(), 'c');
	mesa2.caballeroAnterior();
	mesa2.caballeroAnterior();
	ASSERT_EQ(mesa2.caballeroActual(), 'b');
	
	mesa2.cambioDeLugar('b'); //cambio de lugar al anterior de el
	mesa2.proximoCaballero();
	ASSERT_EQ(mesa2.caballeroActual(), 'a');// el rey se mantiene en el mismo lugar?
	
}

void check_proxAnt(){
	Arturo<char> mesa1;
	Arturo< Arturo<char> > mesa2;
	char c = 'k';
	mesa1.sentarArturo('a');
	int i = 0;
	
	while(i < 10){
		mesa1.incorporarCaballero(c);
		c--;
		i++;
	}
	
	ASSERT_EQ(mesa1.caballeroActual(), 'a');
	mesa1.proximoCaballero();
	ASSERT_EQ(mesa1.caballeroActual(), 'b');
	mesa1.caballeroAnterior();
	ASSERT_EQ(mesa1.caballeroActual(), 'a');
	mesa1.caballeroAnterior();
	ASSERT_EQ(mesa1.caballeroActual(), 'k');
	
	mesa1.proximoCaballero();
	mesa1.proximoCaballero();
	mesa1.proximoCaballero();
	mesa1.proximoCaballero();
	ASSERT_EQ(mesa1.caballeroActual(), 'd');
	
}

void imprime_Arturos(){
	Arturo<char> mesa1;
	  
	cout << "\n Arturo Vacio: " << mesa1 << "\n";
	  
	mesa1.sentarArturo('R');
	mesa1.incorporarCaballero('2');
	mesa1.incorporarCaballero('D');
	mesa1.incorporarCaballero('3');
	  
	cout << " Mesa1: " << mesa1 << "\n";
	
	mesa1.proximoCaballero();
	cout << " Mesa1.proximoCaballero(): " << mesa1 << "\n";
	
	mesa1.hablaArturo();
	cout << " Mesa1.hablaArturo(): " << mesa1 << "\n";
	
	mesa1.proximoCaballero();
	cout << " Mesa1.proximoCaballero(): " << mesa1 << "\n";
	
	Arturo< Arturo<char> > mesa2;
	cout << " Creando Mesa2: " << mesa2 << "\n";
	
	mesa2.sentarArturo(mesa1);
	Arturo<char> mesa3;
	mesa2.incorporarCaballero(mesa3);
	cout << " Mesa2.sentarArturo: " << mesa2 << "\n";
	
	ASSERT_EQ(mesa2.tamanio(), 2);
}


int main() {
  RUN_TEST(check_crear_mesa_vacia);
  RUN_TEST(check_crear_mesa_borrar_elem_da_vacia);
  RUN_TEST(check_arturo_de_arturo); 
  RUN_TEST(check_copia);
  RUN_TEST(check_comparacion);
  RUN_TEST(check_cambio_lugar);
  RUN_TEST(check_proxAnt);
  RUN_TEST(imprime_Arturos);
  RUN_TEST(check_arturo_de_arturo_avanz);
    return 0;
}

