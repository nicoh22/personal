#include "tdt.h"

void tdt_agregar(tdt* tabla, uint8_t* clave, uint8_t* valor) {
	tabla->cantidad++;
	tdtN1_t *primNivel = tabla->primera;
	if(primNivel == NULL){
		tabla->primera = malloc(256*8);
	}

	tdtN2_t *segNivel = primNivel->entradas[clave[1]];
	if(segNivel == NULL){
		primNivel->entradas[clave[1]] = malloc(256*8);
	}
	
	tdtN3_T *tercNivel = segNivel->entradas[clave[2]];
	
	if(tercNivel == NULL){
		segNivel->entradas[clave[2]] = malloc(256*16);
	//TODO: poner los campos "valido" en NULL
	}
	tercNivel->entradas[clave[3]].valor = *valor;
	tercNivel->entradas[clave[3]].valido = 1;
}

void tdt_borrar(tdt* tabla, uint8_t* clave) {
}

void tdt_imprimirTraducciones(tdt* tabla, FILE *pFile) {
}

maxmin* tdt_obtenerMaxMin(tdt* tabla) {
  return 0;
}
