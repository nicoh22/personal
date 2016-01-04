/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

//TODO completar mejor esto

/* Atributos paginas */
/* -------------------------------------------------------------------------- */

#define ATTR_KERNEL_PR 0x03
#define ATTR_KERNEL_NPR 0x02

#define ATTR_USER_PR 0x07
#define ATTR_USER_NPR 0x06
#define ATTR_USER_PR_RO 0x05

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
#define FCODE_P1_T1 0x10000
#define FCODE_P1_T2 0x11000
#define FCODE_P2_T1 0x12000
#define FCODE_P2_T2 0x13000
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
#define KERNEL_DIRECTORY 0x27000
#define KERNEL_TABLE_1 0x28000
#define KERNEL_TABLE_2 0x29000
#define MEM_LIBRE_BASE	0x100000

uint paginas_ocupadas;
uint compartidaA;
uint compartidaB;

void mmu_inicializar(){
	paginas_ocupadas = 0;
	compartidaA = mmu_proxima_pagina_fisica_libre();
	compartidaB = mmu_proxima_pagina_fisica_libre();
	//creo que tengo que inicializar el_mapa
		//enunciado dice que no viene mapeada por defecto
		//solo la mapeo cuando lo voy a usar
}


void mmu_mapear_pagina(uint virtual, uint cr3, uint fisica, uint attrs)
{
	uint *pd, *pt;
	uint pde, pte;	
	uint virtualaux = virtual;
	pd = (uint *)(cr3 & 0xFFFFF000);
	virtualaux = (virtualaux >> 22);
	pde = pd[virtualaux];	//entry de la tabla de directorios
	if(pde == ATTR_KERNEL_NPR || pde == ATTR_USER_NPR){ // si nunca mapee algo que use esta page table
		pde = (mmu_proxima_pagina_fisica_libre() & 0xFFFFF000) | (ATTR_USER_PR & 0x00000FFF);
		pd[virtualaux] = pde; 
	}
	virtualaux = ((virtual & 0x003FF000) >> 12);
	pt = (uint *) (pde & 0xFFFFF000);	
	pte = pt[virtualaux]; //entry de la tabla de pagina
	pte =  (fisica & 0xFFFFF000) | (attrs & 0x00000FFF);
	pt[virtualaux] = pte; 
	tlbflush();
}

uint mmu_inicializar_dir_kernel(){
	uint *pd = (uint *) KERNEL_DIRECTORY;
	uint pt = KERNEL_TABLE_1;
	//uint pt2 = KERNEL_TABLE_2;
	
	uint address = 0;
	uint cr3 = (uint) pd;
	
	int i = 1023;
	pd[0] = (uint) (pt | ATTR_KERNEL_PR); 
	//pd[1] = (uint) (pt2 | ATTR_KERNEL_PR);
	while(i > 0){
		pd[i] = ATTR_KERNEL_NPR; 
		i--;
	}
	i = 0;	
	while(i < 1024){
		mmu_mapear_pagina(address, cr3, address, ATTR_KERNEL_PR);
		address = address + 0x1000;
		i++;
	}
	tlbflush();
	return cr3;
}


uint mmu_proxima_pagina_fisica_libre(){
	uint offset = PAGE_SIZE * paginas_ocupadas;
	paginas_ocupadas++; 
	return MEM_LIBRE_BASE + offset;
}

void mmu_unmapear_pagina(uint virtual, uint cr3){
	uint *pd, *pt;
	uint pde;	
	uint virtualaux = virtual;
	pd = (uint *)(cr3 & 0xFFFFF000);
	virtualaux = (virtualaux >> 22);
	pde = pd[virtualaux];	//entry de la tabla de directorios
	virtualaux = ((virtual & 0x003FF000) >> 12);
	pt = (uint *) (pde & 0xFFFFF000);	
	pt[virtualaux] = NULL; //entry de la tabla de pagina	
	tlbflush();
}

uint mmu_inicializar_memoria_perro(perro_t *perro, int index_jugador, int index_tipo){
	//tener en cuenta que me pueden llamar de cualquier contexto
	//cr3 kernel->estalla si soy tarea en mmu_copiar
	uint fcodigo;
	uint pcompartida; 	
	if(index_jugador == 0){
		if(index_tipo == 0){
			fcodigo = FCODE_P1_T1;
		}else{
			fcodigo = FCODE_P1_T2;
		}
		pcompartida = compartidaA;
	}else{
		if(index_tipo == 0){
			fcodigo = FCODE_P2_T1;
		}else{
			fcodigo = FCODE_P1_T2;
		}
		pcompartida = compartidaB;
	}
	uint cr3 = mmu_proxima_pagina_fisica_libre();
	uint *pd = (uint *) cr3;
	uint pt = mmu_proxima_pagina_fisica_libre();
	//uint pt2 = mmu_proxima_pagina_fisica_libre();
	uint address = 0;		
	int i = 1023;
	pd[0] = (uint) (pt | ATTR_KERNEL_PR);
	//pd[1] = (uint) (pt2 | ATTR_KERNEL_PR);
	while(i > 0){
		pd[i] = ATTR_KERNEL_NPR; 
		i--;
	}
	i = 0;	
	while(i < 1024){ //identity mapping
		mmu_mapear_pagina(address, cr3, address, ATTR_KERNEL_PR);
		address = address + 0x1000;
		i++;
	}
	//copiar codigo
	mmu_mapear_pagina(0x400000, cr3, pcompartida, ATTR_USER_PR);
	uint vcodigo = 0x401000;
	uint posx = perro->jugador->x_cucha;
	uint posy = perro->jugador->y_cucha;
	uint fcucha = mmu_xy2fisica(posx, posy);
	uint vcucha = mmu_xy2virtual(posx, posy);

	mmu_mapear_pagina(fcucha, KERNEL_DIRECTORY, fcucha, ATTR_KERNEL_PR);//mapeo la cucha FISICA
	mmu_copiar_pagina(fcodigo, fcucha);//fcodigo esta bajo id map. fcucha?
	mmu_mapear_pagina(vcucha, cr3, fcucha, ATTR_USER_PR_RO);//mapeo la cucha read only
	mmu_mapear_pagina(vcodigo, cr3, fcucha, ATTR_USER_PR);//Es decir,
	return cr3;
}

void mmu_copiar_pagina(uint src, uint dst){//funciona solo con fisicas
	uint cr3Actual = rcr3();
	lcr3(KERNEL_DIRECTORY);
	tlbflush();
	uint *origen = (uint *) src;
	uint *destino = (uint *) dst;
	uint i = 0;
	while(i < 256){
		destino[i] = origen[i];
		i++;
	}
	lcr3(cr3Actual);
	tlbflush();
}

uint mmu_xy2fisica(uint x, uint y){
	return (x+80*y)*PAGE_SIZE + MAPA_BASE_FISICA;
}

uint mmu_xy2virtual(uint x, uint y){
	return (x+80*y)*PAGE_SIZE + MAPA_BASE_VIRTUAL;
}

void mmu_inicializar_pagina(uint * pagina){
	uint i = 0;
	while(i < 256){
		pagina[i] = NULL;
		i++;
	}
}
