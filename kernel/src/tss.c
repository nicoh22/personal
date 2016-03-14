/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "mmu.h"
#include "defines.h" 


tss tss_inicial;
tss tss_idle;

tss tss_jugadorA[MAX_CANT_PERROS_VIVOS];
tss tss_jugadorB[MAX_CANT_PERROS_VIVOS];

void tss_inicializar() {

	uint inicial = (uint) &tss_inicial;
	uint limite = 103;
	gdt[14].base_0_15 = (inicial & 0x0000FFFF);
	gdt[14].base_23_16 = ((inicial >> 16) & 0x000000FF);
	gdt[14].base_31_24 = (inicial >> 24);
	gdt[14].limit_0_15 = limite & 0x0FF;
	gdt[14].limit_16_19 = (limite >> 16)& 0x00F;
	gdt[14].type = 0x9;
	gdt[14].s = 0x0;
	gdt[14].dpl = 0x00;
	gdt[14].p = 0x1;
	gdt[14].avl = 0x1;
	gdt[14].db = 0x0;
	gdt[14].l = 0x0;
	gdt[14].g = 0x0;

	uint idle = (uint) &tss_idle;
	limite = 103;
	gdt[15].base_0_15 = (idle & 0x0000FFFF);
	gdt[15].base_23_16 = ((idle >> 16) & 0x000000FF);
	gdt[15].base_31_24 = (idle >> 24);
	gdt[15].limit_0_15 = limite & 0x0FF;
	gdt[15].limit_16_19 = (limite >> 16)& 0x00F;
	gdt[15].type = 0x9;
	gdt[15].s = 0x0;
	gdt[15].dpl = 0x00;
	gdt[15].p = 0x1;
	gdt[15].avl = 0x1;
	gdt[15].db = 0x0;
	gdt[15].l = 0x0;
	gdt[15].g = 0x0;

	
	tss_inicial.ptl = NULL;
	tss_inicial.esp0 = NULL;//ss0-12
	tss_inicial.ss0 = NULL; //tss kernel
	tss_inicial.esp1 = NULL;
	tss_inicial.ss1 = NULL;
	tss_inicial.esp2 = NULL;// estos ultimos cuatro no importan
	tss_inicial.ss2 = NULL;//porque no tenemos privilegios 1 y 2 
	tss_inicial.cr3 = 0x27000; //mismo cr3 que el kernel
	tss_inicial.eip = 0x16000;
	tss_inicial.eflags = 0x0202;
	tss_inicial.eax = NULL;
	tss_inicial.ecx = NULL;	
	tss_inicial.edx = NULL;
	tss_inicial.ebx = NULL;
	tss_inicial.esp = NULL; // ebp -12
	tss_inicial.ebp = NULL; // pila (compartia con el kernel?)

		
	tss_idle.ptl = NULL;
	tss_idle.esp0 =0x27000;//ss0-12
	tss_idle.ss0 = GDT_OFF_STACK_KERNEL; //pila kernel
	tss_idle.esp1 = NULL;
	tss_idle.ss1 = NULL;
	tss_idle.esp2 = NULL;// estos ultimos cuatro no importan
	tss_idle.ss2 = NULL;//porque no tenemos privilegios 1 y 2 
	tss_idle.cr3 = 0x27000; //mismo cr3 que el kernel
	tss_idle.eip = 0x16000;
	tss_idle.eflags = 0x0202;
	tss_idle.eax = NULL;
	tss_idle.ecx = NULL;	
	tss_idle.edx = NULL;
	tss_idle.ebx = NULL;
	tss_idle.esp = 0x27000; // ebp -12
	tss_idle.ebp = 0x27000; // pila (compartia con el kernel?)
	tss_idle.esi = NULL;
	tss_idle.es = GDT_OFF_DATA_KERNEL;
	tss_idle.cs = GDT_OFF_CODE_KERNEL;
	tss_idle.ss = GDT_OFF_STACK_KERNEL;
	tss_idle.ds = GDT_OFF_DATA_KERNEL;
	tss_idle.fs = GDT_OFF_DATA_KERNEL;
	tss_idle.gs = GDT_OFF_DATA_KERNEL;
	tss_idle.ldt = NULL;
	tss_idle.dtrap = NULL;
	tss_idle.iomap = 0xffff;
    
	//Llamar a inicializar memoria perro?
	//Llenar tss de los perros
	//No, probablemente eso lo haga el scheduler
	//Cada vez que se lanza un nuevo perro


}

void tss_completar(tss* dog, uint cr3, uint id){

	uint pilakernel = mmu_proxima_pagina_fisica_libre();
	//esto viene del area libre que ya esta mapeado con permisos kernel
	//tanto en la tarea como en el kernel/idle

	dog->ptl = NULL;
	dog->esp0 = pilakernel + 0x1000;
	dog->ss0 = GDT_OFF_DATA_KERNEL; //pila kernel
	dog->esp1 = NULL;
	dog->ss1 = NULL;
	dog->esp2 = NULL;// estos ultimos cuatro no importan
	dog->ss2 = NULL;//porque no tenemos privilegios 1 y 2 
	dog->cr3 = cr3;
	dog->eip = 0x00401000;//el eip posta
	dog->eflags = 0x0202;
	dog->eax = NULL;
	dog->ecx = NULL;	
	dog->edx = NULL;
	dog->ebx = NULL;
	dog->esp = 0x00402000 - 0xC; // 3 parametros en pila (quien los carga?)
	dog->ebp = 0x00402000 - 0xC; // pila 
	dog->esi = NULL;
	dog->edi = NULL;
	
	dog->unused0 = NULL;
	dog->unused1 = NULL;
	dog->unused2 = NULL;
	dog->unused3 = NULL;
	dog->unused4 = NULL;
	dog->unused5 = NULL;
	dog->unused6 = NULL;
	dog->unused7 = NULL;
	dog->unused8 = NULL;
	dog->unused9 = NULL;
	dog->unused10 = NULL;

	dog->es = GDT_OFF_DATA_USER;
	dog->cs = GDT_OFF_CODE_USER;
	dog->ss = GDT_OFF_DATA_USER;
	dog->ds = GDT_OFF_DATA_USER;
	dog->fs = GDT_OFF_DATA_USER;
	dog->gs = GDT_OFF_DATA_USER;
	dog->ldt = NULL;
	dog->dtrap = NULL;
	dog->iomap = 0xffff;

	uint tss_dog = (uint) dog;
	uint limite = 103;
	uint indice = id + 16;
	gdt[indice].base_0_15 = (tss_dog & 0x0000FFFF);
	gdt[indice].base_23_16 = ((tss_dog >> 16) & 0x000000FF);
	gdt[indice].base_31_24 = (tss_dog  >> 24);
	gdt[indice].limit_0_15 = limite & 0x0FF;
	gdt[indice].limit_16_19 = (limite >> 16)& 0x00F;
	gdt[indice].type = 0x9;
	gdt[indice].s = 0x0;
	gdt[indice].dpl = 0x00;//sino podria saltar directamente desde una tarea
	gdt[indice].p = 0x1;
	gdt[indice].avl = 0x1;
	gdt[indice].db = 0x0;
	gdt[indice].l = 0x0;
	gdt[indice].g = 0x0;
}
