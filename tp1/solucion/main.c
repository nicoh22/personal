#include "tdt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void hexToValor(uint8_t* valor, long int hexAlta, long int hexBaja){
	uint8_t *baja = (uint8_t *) &hexBaja;
	uint8_t *alta = (uint8_t *) &hexAlta;
	for(int i = 0; i < 8; i++){
		valor[i] = baja[i];
	}
	for(int i = 0; i < 7; i++){
		valor[i + 8] = alta[i];
	}
}

int main (void){

  /*  tdt* tabla = tdt_crear("sa");
   	
	FILE* salidaEstandar = fopen("./test.txt", "a");	
   		
	tdt_imprimirTraducciones(tabla, salidaEstandar);
    tdt_destruir(&(tabla));
    
	fclose(salidaEstandar);
*/	
	//Ej 2.1

	

	tdt* tabla = tdt_crear("pepe");
	
	//Ej 2.2
	bloque a, b, c, d, e, f;
	
	a.clave[0] = 0x00;
	a.clave[1] = 0x00;
	a.clave[2] = 0x00;


	b.clave[0] = 0xFF;
	b.clave[1] = 0xFF;
	b.clave[2] = 0xFF;
	
	for(int i = 0; i < 15; i++){
		a.valor[i] = 0xFF;
		b.valor[i] = 0x00;
	}

	tdt_agregar(tabla, a.clave, a.valor);
	tdt_agregar(tabla, b.clave, b.valor);

	//Ej 2.3
	
	bloque* cadena[5];

	cadena[0] = &c;
	cadena[1] = &d;
	cadena[2] = &e;
	cadena[3] = &f;

	cadena[0]->clave[2] = 0x05;
	cadena[0]->clave[1] = 0x05;
	cadena[0]->clave[0] = 0x05;
	cadena[1]->clave[2] = 0xFF;
	cadena[1]->clave[1] = 0xFF;
	cadena[1]->clave[0] = 0xFF;
	cadena[2]->clave[2] = 0x53;
	cadena[2]->clave[1] = 0xFF;
	cadena[2]->clave[0] = 0xAA;
	cadena[3]->clave[2] = 0x10;
	cadena[3]->clave[1] = 0xEE;
	cadena[3]->clave[0] = 0x05;

	hexToValor(cadena[0]->valor, 0x123456789ABCDE, 0xF123456789ABCDEF);
	hexToValor(cadena[1]->valor, 0x11223344556677, 0x8899AABBCCDDEEFF);
	hexToValor(cadena[2]->valor, 0x11122233344455, 0x5666777888999AAA);
	hexToValor(cadena[3]->valor, 0x11112222333344, 0x4455556666777788);

	cadena[4] = NULL;

	tdt_agregarBloques(tabla, (bloque **)&cadena); 
	//Ej 2.4
	
	tdt_borrarBloque(tabla, &e);
	tdt_borrarBloque(tabla, &b); 

	//Ej 2.5

	
	maxmin* infoMaxMin = tdt_obtenerMaxMin(tabla);
	printf("Clave Minima: %02X%02X%02X  \n", infoMaxMin->min_clave[2], infoMaxMin->min_clave[1],infoMaxMin->min_clave[0]);
	printf("Clave Maxima: %02X%02X%02X  \n", infoMaxMin->max_clave[2], infoMaxMin->max_clave[1],infoMaxMin->max_clave[0]);
	
	printf("Valor Minimo: ");
	for( int j = 0; j<15 ; j++ ){ printf("%02X", infoMaxMin->min_valor[j]); }
	printf("\n");

	printf("Valor Maximo: ");
	for( int j = 0; j < 15 ; j++ ){ printf("%02X", infoMaxMin->max_valor[j]); }
	printf("\n ");
	free(infoMaxMin);
	

	//Ej 2.6
	
	FILE* salidaEstandar = fopen("/dev/stdout", "a");	
	
	tdt_imprimirTraducciones(tabla, salidaEstandar);
	
	fclose(salidaEstandar);
	//Ej 2.7
	
	printf("Cantidad de traducciones: %d \n", tdt_cantidad(tabla));

	//Ej 2.8
	tdt_destruir(&tabla);
    return 0;    
}
