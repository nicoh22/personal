/* ** por compatibilidad se omiten tildes **
================================================================================
TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
definicion de funciones del scheduler
*/

#include "sched.h"
#include "i386.h"
#include "screen.h"

sched_t scheduler;
int ultimoEjecutado[] = {-1, -1};
jugador_t* jugadorPrev = &jugadorB;

void sched_to_idle();

void sched_inicializar()
{
	scheduler.current = 0;
	//calculo que pongo la idle?
	int i = 0;
	while(i <= MAX_CANT_TAREAS_VIVAS){
		scheduler.tasks[i].gdt_index = NULL;
		i++;
	}
	scheduler.tasks[0].gdt_index = GDT_IDX_IDLE_TASK;
	scheduler.tasks[0].perro = NULL;
}


int sched_buscar_indice_tarea(uint gdt_index) {
	int i = 0;
	while(i <= MAX_CANT_TAREAS_VIVAS){
		if(scheduler.tasks[i].gdt_index == gdt_index){
			return i;
		}
		i++;
	}
	return -1;
}


int sched_buscar_tarea_libre()
{
	int i = 0;
	while(i <= MAX_CANT_TAREAS_VIVAS){
		if(scheduler.tasks[i].gdt_index == NULL){
			return i;
		}
		i++;
	}
	return -1;
}


perro_t* sched_tarea_actual()
{
    return scheduler.tasks[scheduler.current].perro;
}

void sched_agregar_tarea(perro_t *perro)
{
	//checkear si puedo agregar
	int indice = sched_buscar_tarea_libre();
	if(indice == -1){
		return; //!!!
	}
	scheduler.tasks[indice].perro = perro;
	scheduler.tasks[indice].gdt_index = perro->id + 16;
	
}

void sched_remover_tarea(unsigned int gdt_index)
{
	int indice = sched_buscar_indice_tarea(gdt_index);
	if(indice == -1){
		return; //!!!
	}
	scheduler.tasks[indice].gdt_index = 0;
	
	//sched_to_idle?	
}

uint sched_proxima_a_ejecutar()
{

	jugador_t *jprox;
	jugador_t *jaux = jugadorPrev;

	if( jugadorPrev == &jugadorB){
		jprox = &jugadorA;
	}else{
		jprox = &jugadorB;
	}
	ushort contador; 
	uint registreAmbos = FALSE;
	uint indice;
	while(!registreAmbos){
		indice = jprox->index;
		contador = ultimoEjecutado[indice] + 1;
		uint mepase = FALSE; 
		while(!mepase || contador <= ultimoEjecutado[indice]){ 
			if(jprox->perros[contador].libre == FALSE){//libre: perros sin lanzar/invalidos
				uint gdt_index = jprox->perros[contador].id + 16;
				ultimoEjecutado[indice] = contador; 
				uint proxima = sched_buscar_indice_tarea(gdt_index);
				return proxima; 
			}
			contador++;
			if(contador == MAX_CANT_PERROS_VIVOS){
				contador = 0; 
				mepase = TRUE;
			}
		}
		if(jprox == jugadorPrev){
			registreAmbos = TRUE;
		}
		jprox = jugadorPrev;
		jugadorPrev = jprox;
	}
	jugadorPrev = jaux;
	return 0;//aka error, podria retornar 0 o sea donde esta la idle
}


ushort sched_atender_tick()
{
	if(scheduler.current != 0){
		game_atender_tick(game_perro_actual);
	}
	uint prox_tarea = sched_proxima_a_ejecutar();
	game_perro_actual = scheduler.tasks[prox_tarea].perro; 
	if(prox_tarea == 0){
		sched_to_idle();
	}else{
		scheduler.current = prox_tarea;
	}
	screen_actualizar_reloj_global();
	return scheduler.tasks[prox_tarea].gdt_index; 
}

void sched_to_idle()
{
//lo que se tendria que llamar en caso de excepcion/syscall
	scheduler.current = 0;
	game_perro_actual = NULL;
}
