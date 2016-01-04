
#include "game.h"
#include "mmu.h"
#include "screen.h"
#include "tss.h"


// realiza inicialización básica de un perro. El perro aun no está vivo ni por lanzarse. Setea jugador, indice, etc
void game_perro_inicializar(perro_t *perro, jugador_t *j, uint index, uint id)
{
	perro->id = id;
	perro->index = index; 
	perro->jugador = j;
	perro->libre = TRUE;

//	~~~ completar si es necesario ~~~

}

// toma un perro ya existente libre y lo recicla seteando x e y a la cucha.
// luego inicializa su mapeo de memoria, tss, lo agrega al sched y pinta la pantalla
void game_perro_reciclar_y_lanzar(perro_t *perro, uint tipo)
{
	jugador_t *j = perro->jugador;

	uint px = perro->x;
	uint py = perro->y;

	perro->x = j->x_cucha;
	perro->y = j->y_cucha;
	perro->tipo = tipo;
	perro->libre = FALSE;

	// ahora debo llamar a rutinas que inicialicen un nuevo mapa de
	// memoria para el nuevo perro, que carguen su tss correspondiente,
	// lo scheduleen y finalmente lo pinten en pantalla
	sched_agregar_tarea(perro);
	
	tss* tssperro;
	if(perro->jugador->index == 0){
		tssperro = &tss_jugadorA[perro->index];
	}else{
		tssperro = &tss_jugadorB[perro->index];
	}
	uint cr3 = mmu_inicializar_memoria_perro(perro, perro->jugador->index, perro->tipo);
	tss_completar(tssperro, cr3, perro->id);

	screen_pintar_perro(perro);
	// ~~~ completar ~~~
	//llenar la pila! x | y | retorno
	uint cr3Actual = rcr3();
	lcr3(0x27000);
	tlbflush();
	uint* pila = (uint *) (mmu_xy2fisica(j->x_cucha + 1, j->y_cucha) - 0x0C);
	pila[0] = px;
	pila[1] = py;
	pila[2] = 0x16000;//placeholder 

	lcr3(cr3Actual);
	tlbflush();
}

// el perro descargó sus huesos o realizó una acción no válida y caputó, hay que sacarlo del sistema.
void game_perro_termino(perro_t *perro)
{
	//Basicamente, como el destructor hay que revertir el proceso de inicializacion en orden inverso
	breakpoint();	
	screen_borrar_perro(perro);
	uint gdt_index = perro->index;
	sched_remover_tarea(gdt_index);
	perro->libre = TRUE;
//	perro->x = -1;
//	perro->y = -1;
	screen_actualizar_reloj_perro(perro);
}

// transforma código de dirección en valores x e y 
uint game_dir2xy(/* in */ direccion dir, /* out */ int *x, /* out */ int *y)
{
	switch (dir)
	{
		case IZQ: *x = -1; *y =  0; break;
		case DER: *x =  1; *y =  0; break;
		case ABA: *x =  0; *y =  1; break;
		case ARR: *x =  0; *y = -1; break;
    		case AQUI:*x =  0; *y =  0; break;
	default: return -1;
	}

	return 0;
}

// recibe una direccion y un perro, al cual debe mover en esa dirección
// *** viene del syscall mover ***
uint game_perro_mover(perro_t *perro, direccion dir)
{
	if(dir == AQUI) return 0; //la direccion recibida es AQUI
	int x, y;
	uint res = game_dir2xy(dir, &x, &y);
	int nuevo_x = perro->x + x;
	int nuevo_y = perro->y + y;
	int viejo_x = perro->x;
	int viejo_y = perro->y;
	
	if(res == -1){ 
		game_perro_termino(perro);
		return res;//me llamaste con parametro erroneo
	}
	perro_t *otroperro = game_perro_en_posicion(nuevo_x, nuevo_y);
	
	if(otroperro != NULL) game_perro_termino(otroperro);
	
	uint vcodigo = 0X401000; // direccion virtual codigo
	uint src = mmu_xy2fisica(viejo_x,viejo_y);
	uint dst = mmu_xy2fisica(nuevo_x, nuevo_y);
	uint vdst = mmu_xy2virtual(nuevo_x, nuevo_y);
    	uint cr3Tarea = rcr3();
	uint cr3 = 0x27000;
	
	lcr3(cr3);
	tlbflush(); //lo que va a tardar esta funcion dios
	mmu_mapear_pagina(dst, cr3, dst, 0x03);
	mmu_copiar_pagina(src,dst);
	mmu_mapear_pagina(vcodigo, cr3Tarea, dst, 0x07);
	mmu_mapear_pagina(vdst, cr3Tarea, dst, 0x05);
	
	lcr3(cr3Tarea);
	tlbflush();
	perro->x = nuevo_x;
	perro->y = nuevo_y;
    // capaz falte lo de matar al perro
	screen_pintar_perro(perro);
	breakpoint();
    return nuevo_x + nuevo_y + viejo_x + viejo_y + res; // uso todas las variables para que no tire warning->error.
}

// recibe un perro, el cual debe cavar en su posición
// *** viene del syscall cavar ***
uint game_perro_cavar(perro_t *perro)
{
	int cantHuesos = game_huesos_en_posicion(perro->x,perro->y);
	if(cantHuesos > 0)
	{
		if(perro->huesos < 9)
		{
			perro->huesos = perro->huesos+1;
			int i;
	for (i = 0; i < ESCONDITES_CANTIDAD; i++)
	{
		if (escondites[i][0] == perro->x && escondites[i][1] == perro->y)
			escondites[i][2] = escondites[i][2]-1;
	}
		}
	}
	return 0;
}

// recibe un perro, devueve la dirección del hueso más cercano
// *** viene del syscall olfatear ***
uint game_perro_olfatear(perro_t *perro)
{
	int x_actual_diff = 1000, y_actual_diff = 1000;

	int i;
	for (i = 0; i < ESCONDITES_CANTIDAD; i++)
	{
		if (escondites[i][2] == 0) continue;

		int diff_x = escondites[i][0] - (int)perro->x;
		int diff_y = escondites[i][1] - (int)perro->y;

		if (x_actual_diff * x_actual_diff + y_actual_diff * y_actual_diff > diff_x * diff_x + diff_y * diff_y)
		{
			x_actual_diff = diff_x;
			y_actual_diff = diff_y;
		}
   	}

	if (x_actual_diff == 0 && y_actual_diff == 0)
		return AQUI;

	if (x_actual_diff * x_actual_diff > y_actual_diff * y_actual_diff)
	{
		return x_actual_diff > 0 ? DER : IZQ;
	}
	else 
	{
		return y_actual_diff > 0 ? ABA : ARR;
	}
    return 0;
}

float game_perro_recibirOrden(perro_t *perro) //wat
{
return perro->id << 16 | perro->jugador->y << 8 | perro->jugador->x;
}


// chequea si el perro está en la cucha y suma punto al jugador o lo manda a dormir
void game_perro_ver_si_en_cucha(perro_t *perro)
{
	if (perro->x != perro->jugador->x_cucha || perro->y != perro->jugador->y_cucha)
		return;

	if (perro->huesos == 0)
		return;

	game_jugador_anotar_punto(perro->jugador);
	perro->huesos--;
	if (perro->huesos == 0)
		game_perro_termino(perro);
}

