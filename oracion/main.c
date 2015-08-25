#include <stdlib.h>
#include "lista.h"


int main (void){
	// COMPLETAR AQUI EL CODIGO
	unsigned char a = palabraLongitud("gato");
	unsigned char b = palabraLongitud("perro");
	unsigned char c = palabraLongitud("");
	printf("gato: %d\nperro: %d\n<vacio>: %d\n", a, b, c);
	
	bool d = palabraMenor("hola", "chau");
	bool e = palabraMenor("abc", "j");
	bool f = palabraMenor("hola", "hola");
	
	printf("hola chau: %d\nabc j: %d\nhola hola: %d\n", d, e, f);
	
	FILE *archivo = fopen("/dev/stdout", "a");
	palabraImprimir("Casa, arbol!", archivo); //File pointer!
	
	char* p = palabraCopiar("palabrita");
	palabraImprimir(p, archivo);
	free(p);
	
	nodo* n = nodoCrear("Buenos dias");
	palabraImprimir(n->palabra, archivo); 
	nodoBorrar(n);
	fclose(archivo);
	return 0;
}
