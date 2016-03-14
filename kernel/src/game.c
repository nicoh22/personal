/* ** por compatibilidad se omiten tildes **
================================================================================
TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "mmu.h"
#include "tss.h"
#include "screen.h"

#include <stdarg.h>


int escondites[ESCONDITES_CANTIDAD][3] = { // TRIPLAS DE LA FORMA (X, Y, HUESOS)
                                        {76,  25, 50}, {12, 15, 50}, {9, 10, 100}, {47, 21, 100} ,
                                        {34,  11, 50}, {75, 38, 50}, {40, 21, 100}, {72, 17, 100}
                                    };

jugador_t jugadorA;
jugador_t jugadorB;

perro_t *game_perro_actual = NULL;
int ultimo_cambio = MAX_SIN_CAMBIOS;

void ASSERT_OR_ERROR(uint value, char* error_msg)
{
	if (!value) {
		print(error_msg, 5, 5, C_BG_LIGHT_GREY | C_FG_BLACK);
		breakpoint();
	}
}

void* error()
{
	__asm__ ("int3");
	return 0;
}

uint game_xy2lineal (uint x, uint y) {
	return (y * MAPA_ANCHO + x);
}

uint game_es_posicion_valida(int x, int y) {
	return (x >= 0 && y >= 0 && x < MAPA_ANCHO && y < MAPA_ALTO);
}


void game_inicializar()
{
	game_jugador_inicializar(&jugadorA);
	game_jugador_inicializar(&jugadorB);
    screen_pintar_puntajes();
}


// devuelve la cantidad de huesos que hay en la posición pasada como parametro
uint game_huesos_en_posicion(uint x, uint y)
{
	int i;
	for (i = 0; i < ESCONDITES_CANTIDAD; i++)
	{
		if (escondites[i][0] == x && escondites[i][1] == y)
			return escondites[i][2];
	}
	return 0;
}




// devuelve algun perro que esté en la posicion pasada (hay max 2, uno por jugador)
perro_t* game_perro_en_posicion(uint x, uint y)
{
	int i;
	for (i = 0; i < MAX_CANT_PERROS_VIVOS; i++)
	{
		if (!jugadorA.perros[i].libre && jugadorA.perros[i].x == x && jugadorA.perros[i].y == y)
			return &jugadorA.perros[i];
		if (!jugadorB.perros[i].libre && jugadorB.perros[i].x == x && jugadorB.perros[i].y == y)
			return &jugadorB.perros[i];
	}
	return NULL;
}


void game_debug()
{
//primero guarda el estado de la imagen antes de la impresion del modo debug
//no se si va a tener que ser todo en ensamblador para evitar que se pierdan los
//registros de camino


//capaz esta  va a terminar siendo una funcion pintar llamada desde un asm para conservar los registros que hay que mostrar y no pisarlos

screen_pintar_rect(' ', C_BG_BLACK   | C_FG_LIGHT_GREY,6,24,36,30);
screen_pintar_linea_h(' ', C_BG_RED   | C_FG_LIGHT_GREY,7,25,28);
screen_pintar_rect(' ', C_BG_LIGHT_GREY   | C_FG_LIGHT_GREY,8,25,33,28);
print("eax",26,9,C_FG_BLACK| C_BG_LIGHT_GREY);
print("ebx",26,11,C_FG_BLACK| C_BG_LIGHT_GREY);
print("ecx",26,13,C_FG_BLACK| C_BG_LIGHT_GREY);
print("edx",26,15,C_FG_BLACK| C_BG_LIGHT_GREY);
print("esi",26,17,C_FG_BLACK| C_BG_LIGHT_GREY);
print("edi",26,19,C_FG_BLACK| C_BG_LIGHT_GREY);
print("ebp",26,21,C_FG_BLACK| C_BG_LIGHT_GREY);
print("esp",26,23,C_FG_BLACK| C_BG_LIGHT_GREY);
print("eip",26,25,C_FG_BLACK| C_BG_LIGHT_GREY);
print("cs",27,27,C_FG_BLACK| C_BG_LIGHT_GREY);
print("ds",27,29,C_FG_BLACK| C_BG_LIGHT_GREY);
print("es",27,31,C_FG_BLACK| C_BG_LIGHT_GREY);
print("fs",27,33,C_FG_BLACK| C_BG_LIGHT_GREY);
print("gs",27,35,C_FG_BLACK| C_BG_LIGHT_GREY);
print("ss",27,37,C_FG_BLACK| C_BG_LIGHT_GREY);
print("eflags",27,39,C_FG_BLACK| C_BG_LIGHT_GREY);
print("cr0",40,9,C_FG_BLACK| C_BG_LIGHT_GREY);
print("cr2",40,11,C_FG_BLACK| C_BG_LIGHT_GREY);
print("cr3",40,13,C_FG_BLACK| C_BG_LIGHT_GREY);
print("cr4",40,15,C_FG_BLACK| C_BG_LIGHT_GREY);
print("stack",40,26,C_FG_BLACK| C_BG_LIGHT_GREY);
}


// termina si se agotaron los huesos o si hace tiempo que no hay ningun cambio
void game_terminar_si_es_hora()
{
	uint cantHueso = 0;
	int i;
	for(i=0;i<ESCONDITES_CANTIDAD;i++)
	{
	cantHueso = cantHueso + escondites[i][2];
	}

	//si cambio
	if(cantHueso == 0 /*|| sinCambio*/)
	{
		//romperTodo.com
	}
}

