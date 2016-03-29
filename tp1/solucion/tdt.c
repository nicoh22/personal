#include "tdt.h"

void tdt_agregar(tdt* tabla, uint8_t* clave, uint8_t* valor) {
	tabla->cantidad++;
	tdtN1 *primNivel = tabla->primera;
	if(primNivel == NULL){
		tabla->primera = malloc(256*8);
		primNivel = tabla->primera;
		int j = 0;
		while(j<256){
			primNivel->entradas[j] = NULL;
		}
	}

	tdtN2 *segNivel = primNivel->entradas[clave[1]];
	if(segNivel == NULL){
		segNivel = malloc(256*8);
		primNivel->entradas[clave[1]] = segNivel;
		int j = 0;
		while(j<256){
			segNivel->entradas[j] = NULL;
		}
	}
	
	tdtN3 *tercNivel = segNivel->entradas[clave[2]];
	
	if(tercNivel == NULL){
		tercNivel = malloc(256*16);
		segNivel->entradas[clave[2]] = tercNivel; 
	//TODO: poner los campos "valido" en NULL
		int j = 0;
		while(j <256){
			tercNivel->entradas[j].valido = 0;
			j++;
		}
	}
	uint8_t *valorInterno = tercNivel->entradas[clave[3]].valor.val;
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
