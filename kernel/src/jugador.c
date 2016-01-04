
#include "game.h"
#include "mmu.h"
#include "screen.h"


#define POS_INIT_A_X                      1
#define POS_INIT_A_Y                      1
#define POS_INIT_B_X         MAPA_ANCHO - 2
#define POS_INIT_B_Y          MAPA_ALTO - 2


void game_jugador_inicializar(jugador_t *j)
{
	static int index = 0;

	j->index = index++;

	if (j->index == JUGADOR_A) {
		j->x = POS_INIT_A_X;
		j->y = POS_INIT_A_Y;

	} else {
		j->x = POS_INIT_B_X;
		j->y = POS_INIT_B_Y;
	}

	j->puntos = 0;
	j->x_cucha = j->x;
	j->y_cucha = j->y;


	int i;
	for (i = 0; i < MAX_CANT_PERROS_VIVOS; i++)
	{
	/*	uint gdt_index;
		if (j->index == JUGADOR_A) {
			gdt_index = 16; 
		}else{
			gdt_index = 24; 
		}
	*/		
		game_perro_inicializar(&j->perros[i], j, i, i + j->index*8);
	}
}


// debe devolver el proximo perro del arreglo que no esté siendo usado actualmente
perro_t* game_jugador_dame_perro_libre(jugador_t *j)
{
	int i = 0;

	for (; i < MAX_CANT_PERROS_VIVOS; i++)
	{
		if (j->perros[i].libre == TRUE)
		return &j->perros[i];
}

	return NULL;
}


// debe encargarse de buscar un perro libre, configurarlo, y inicializar su mapeo de memoria, tss, y lugar en el sched
void game_jugador_lanzar_perro(jugador_t *j, uint tipo, int x, int y)
{
	if (game_perro_en_posicion(j->x_cucha, j->y_cucha) != NULL)
		return;

	perro_t *perro = game_jugador_dame_perro_libre(j);
	if (perro == NULL)
		return;
	
	perro->x = x;
	perro->y = y;
	game_perro_reciclar_y_lanzar(perro, tipo);
}

// recibe un par (x, y) y un jugador, al cual debe mover en esa dirección
uint game_jugador_moverse(jugador_t *j, int x, int y)
{
	if(game_es_posicion_valida(j->x + x,j->y + y))
	{
	screen_borrar_jugador(j);
	j->x = j->x + x;
	j->y = j->y + y;
	screen_pintar_jugador(j);
	}
    // ~~~ completar ~~~
    return j->x + j->y; // uso todas las variables locales para que no tire warning -> error
}

// descarga 1 hueso en la cucha y actualiza el screen
void game_jugador_anotar_punto(jugador_t *j)
{
    ultimo_cambio = MAX_SIN_CAMBIOS;

	j->puntos++;

    screen_pintar_puntajes();

	if(j->puntos==999)
		screen_stop_game_show_winner(j);
}


// guarda la orden en el jugador para que los perros puedan preguntarla luego (mediante un syscall)
void game_jugador_dar_orden(jugador_t *jugador, int orden)
{	
	jugador->orden = orden;
}



