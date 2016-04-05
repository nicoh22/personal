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
//se le puede pasar cualquier clave, se encuentre en la tabla o no

	tdtN1* primNivel = tabla->primera;
	if(primNivel == NULL){ return; } //no hay tabla, la clave no esta
	
	tdtN2* segNivel = primNivel->entradas[clave[0]]; 
	if(segNivel == NULL){ return; } //no hay tabla, la clave no esta
	
	tdtN3* tercNivel = segNivel->entradas[clave[1]]; 
	if(tercNivel == NULL){ return; } //no hay tabla, la clave no esta
	
	if(!tercNivel->entradas[clave[2]].valido){ return; }

	tabla->cantidad--;
	tercNivel->entradas[clave[2]].valido = 0;
	
	int i = 0; 
	while( i < 256 ) {	
		if(tercNivel->entradas[i].valido){	break; }
		i++;
	}	
	
	if(i == 256){//no encontre valores validos
		free(tercNivel);
		segNivel->entradas[clave[1]] = NULL;
		int j = 0;
		while( j < 256) {
			if(segNivel->entradas[clave[j]] != NULL){ break; }
			j++;
		}
		if(j == 256){
			free(segNivel);
			primNivel->entradas[clave[0]] = NULL; 
			int k = 0;
			while( k < 256) {
				if(primNivel->entradas[clave[k]] != NULL){ break; }
				k++;
			}
			if(k == 256){
				free(primNivel);
				tabla->primera = NULL;
			}
		}
	}

}



void tdt_imprimirTraducciones(tdt* tabla, FILE *pFile) {

	fprintf(pFile, "- %s  -\n", tabla->identificacion);
	tdtN1* primNivel = tabla->primera;
	int clave[3];
	
	if(primNivel == NULL){return;} //no hay ninguna tabla

	for(int i = 0; i < 256; i++) {	
		if(primNivel->entradas[i] != NULL){
			clave[0] = i;	
			tdtN2* segNivel = primNivel->entradas[i]; 
			for(int j = 0; j < 256; j++) 
			{
				if(segNivel->entradas[j] != NULL){
					clave[1] = j;	
					tdtN3* tercNivel = segNivel->entradas[j]; 
					for(int k = 0; k < 256; k++){
						if(tercNivel->entradas[k].valido){
							clave[2] = k;
							fprintf(pFile,
								"%hhX%hhX%hhX ==>",
								clave[0],
								clave[1],
								clave[2]
							       );	
							for(int l = 0; l<15; l++){
								fprintf(
									pFile,
									"%hhX",
									tercNivel->entradas[k].valor.val[l]
								);
							}
							fprintf(pFile, "\n");	
						}	
					}
				}	
			}	
		}
	}
	//todo ese codigo repetido dios
}

maxmin* tdt_obtenerMaxMin(tdt* tabla) {
  return 0;
}
