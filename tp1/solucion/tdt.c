#include "tdt.h"

void tdt_agregar(tdt* tabla, uint8_t* clave, uint8_t* valor) {
	tabla->cantidad++;
	tdtN1 *primNivel = tabla->primera;
	if(primNivel == NULL){
		tabla->primera = malloc(256*8);
	}

	tdtN2 *segNivel = primNivel->entradas[clave[1]];
	if(segNivel == NULL){
		primNivel->entradas[clave[1]] = malloc(256*8);
	}
	
	tdtN3 *tercNivel = segNivel->entradas[clave[2]];
	
	if(tercNivel == NULL){
		segNivel->entradas[clave[2]] = malloc(256*16);
	//TODO: poner los campos "valido" en NULL
	}
	int8_t *valorInterno = tercNivel->entradas[clave[3]].valor.val;
	int i = 0;
	while (i<15){
		valorInterno[i] = valor[i];
		i++;
	}
	tercNivel->entradas[clave[3]].valido = 1;
}

void tdt_borrar(tdt* tabla, uint8_t* clave) {
}

void tdt_imprimirTraducciones(tdt* tabla, FILE *pFile) {
}

maxmin* tdt_obtenerMaxMin(tdt* tabla) {
  return 0;
}
