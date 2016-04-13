#include "tdt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main (void){

	tdt* tabla = tdt_crear("sa");
   	
	FILE* salidaEstandar = fopen("./test.txt", "a");	
   		
	tdt_imprimirTraducciones(tabla, salidaEstandar);
    tdt_destruir(&(tabla));
    
	fclose(salidaEstandar);

    return 0;    
}
