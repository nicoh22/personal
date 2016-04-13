#include "tdt.h"

void tdt_agregar(tdt* tabla, uint8_t* clave, uint8_t* valor) {
	tdtN1 *primNivel = tabla->primera;
	if(primNivel == NULL){
		tabla->primera = malloc(256*8);
		primNivel = tabla->primera;
		int j = 0;
		while(j<256){
			primNivel->entradas[j] = NULL;
			j++;
		}
	}

	tdtN2 *segNivel = primNivel->entradas[clave[2]];
	if(segNivel == NULL){
		segNivel = malloc(256*8);
		primNivel->entradas[clave[2]] = segNivel;
		int j = 0;
		while(j<256){
			segNivel->entradas[j] = NULL;
			j++;
		}
	}
	
	tdtN3 *tercNivel = segNivel->entradas[clave[1]];
	
	if(tercNivel == NULL){
		tercNivel = malloc(256*16);
		segNivel->entradas[clave[1]] = tercNivel; 
		int j = 0;
		while(j <256){
			tercNivel->entradas[j].valido = 0;
			j++;
		}
	}
	uint8_t *valorInterno = tercNivel->entradas[clave[0]].valor.val;
	int i = 0;
	while (i<15){
		valorInterno[i] = valor[i];
		i++;
	}
	if(!tercNivel->entradas[clave[0]].valido){ //si el valor no es valido
		tabla->cantidad++;
		tercNivel->entradas[clave[0]].valido = 1;
	}
}



void tdt_borrar(tdt* tabla, uint8_t* clave) {
//se le puede pasar cualquier clave, se encuentre en la tabla o no
	if(tabla == NULL){ return; }
	tdtN1* primNivel = tabla->primera;
	if(primNivel == NULL){ return; } //no hay tabla, la clave no esta
	
	tdtN2* segNivel = primNivel->entradas[clave[2]]; 
	if(segNivel == NULL){ return; }
	
	tdtN3* tercNivel = segNivel->entradas[clave[1]]; 
	if(tercNivel == NULL){ return; }
	
	if(!(tercNivel->entradas[clave[0]].valido)){ return; }

	tabla->cantidad--;
	tercNivel->entradas[clave[0]].valido = 0;
	
	int i = 0; 
	while( i < 256 ) {	
		if(tercNivel->entradas[i].valido){ break; }
		i++;
	}	
	
	if(i == 256){//no encontre valores validos
		free(tercNivel);
		segNivel->entradas[clave[1]] = NULL;
		int j = 0;
		while( j < 256) {
			tdtN3* unaTdtN3 = segNivel->entradas[j];
			if( unaTdtN3 != NULL ){ break; }
			j++;
		}
		if(j == 256){
			free(segNivel);
			primNivel->entradas[clave[2]] = NULL; 
			int k = 0;
			while( k < 256) {
				tdtN2* unaTdtN2 = primNivel->entradas[k];
				if( unaTdtN2 != NULL ){ break; }
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

	fprintf(pFile, "- %s -\n", tabla->identificacion);
	tdtN1* primNivel = tabla->primera;
	int clave[3];
	
	if(primNivel == NULL){return;} //no hay ninguna tabla

	for(int i = 0; i < 256; i++) {	
		if(primNivel->entradas[i] != NULL){
			clave[2] = i;	
			tdtN2* segNivel = primNivel->entradas[i]; 
			for(int j = 0; j < 256; j++) 
			{
				if(segNivel->entradas[j] != NULL){
					clave[1] = j;	
					tdtN3* tercNivel = segNivel->entradas[j]; 
					for(int k = 0; k < 256; k++){
						if(tercNivel->entradas[k].valido){
							clave[0] = k;
							fprintf(pFile,
								"%02X%02X%02X => ",
								clave[0],
								clave[1],
								clave[2]
							       );	
							for(int l = 0; l<15; l++){
								fprintf(
									pFile,
									"%02X",
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
}

maxmin* tdt_obtenerMaxMin(tdt* tabla) {
	//el que me llama tiene la responsabilidad
	//de liberar memoria
	maxmin* res = malloc(sizeof(maxmin));
	for(int m = 0; m < 15; m++){ res->min_valor[m] = 0xFF; }
	for(int m = 0; m < 15; m++){ res->max_valor[m] = 0x00; }

	for(int m = 0; m < 3; m++){ res->max_clave[m] = 0x00; }
	for(int m = 0; m < 3; m++){ res->min_clave[m] = 0xFF; }

	uint8_t encontreMinClave = 0;
	tdtN1* primNivel = tabla->primera;
	if(tabla->primera == NULL){ return res; }	

	for(int i = 0; i < 256; i++) {	
		if(primNivel->entradas[i] != NULL){
			tdtN2* segNivel = primNivel->entradas[i]; 
			for(int j = 0; j < 256; j++) {
				if(segNivel->entradas[j] != NULL){
					tdtN3* tercNivel = segNivel->entradas[j]; 
					for(int k = 0; k < 256; k++) {
						if(tercNivel->entradas[k].valido){
							// si llego aca estoy en algun valor valido
							// clave = {k,j,i}
							if(!encontreMinClave){
								encontreMinClave = 1;
								res->min_clave[2] = i;
								res->min_clave[1] = j;
								res->min_clave[0] = k;
							}
							res->max_clave[2] = i;
							res->max_clave[1] = j;
							res->max_clave[0] = k;
							
							int h = 0;
							while( h < 15){
								if(tercNivel->entradas[k].valor.val[h] < res->max_valor[h]){ h = 15; break;}
								if(tercNivel->entradas[k].valor.val[h] > res->max_valor[h]){ break;}
								h++;
							}
							
							if( h != 15 ){
								//copiar a max_valor
								for(int m = 0; m < 15; m++){ res->max_valor[m] = tercNivel->entradas[k].valor.val[m]; }
							}

							h = 0;	
							while( h < 15 ){
								if(tercNivel->entradas[k].valor.val[h] > res->min_valor[h]){ h = 15; break;}
								if(tercNivel->entradas[k].valor.val[h] < res->min_valor[h]){ break;}
								h++;
							}
							if(h != 15){
								//copiar a min_valor
								for(int m = 0; m < 15; m++){ res->min_valor[m] = tercNivel->entradas[k].valor.val[m]; }
							}	
						}
					}
				}
			}
		}

	}





	return res;
}
