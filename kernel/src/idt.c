
/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"

#include "tss.h"

idt_entry idt[255] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0, 0);
        ...
        IDT_ENTRY(19, 0);

        ...
    }
*/


// descomentar para usar, seteando segsel y attr segun corresponda

#define IDT_INTERRUPT(numero, dpl)                                                                                   \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x08 << 3;        \
    idt[numero].attr = (unsigned short) 0x8E00 | (((unsigned short)(dpl & 0x3)) << 13);                          \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);


void idt_inicializar() {
    // Excepciones
	
	IDT_INTERRUPT(0, 0);
	IDT_INTERRUPT(1, 0);
	IDT_INTERRUPT(3, 0);
	IDT_INTERRUPT(4, 0);
	IDT_INTERRUPT(5, 0);
	IDT_INTERRUPT(6, 0);
	IDT_INTERRUPT(7, 0);
	IDT_INTERRUPT(8, 0);
	IDT_INTERRUPT(9, 0);
	IDT_INTERRUPT(10, 0);
	IDT_INTERRUPT(11, 0);
	IDT_INTERRUPT(12, 0);
	IDT_INTERRUPT(13, 0);
	IDT_INTERRUPT(14, 0);
	IDT_INTERRUPT(16, 0);
	IDT_INTERRUPT(17, 0);
	IDT_INTERRUPT(18, 0);
	IDT_INTERRUPT(19, 0);
	// las basicas
	IDT_INTERRUPT(32, 0);
	IDT_INTERRUPT(33, 0);
	IDT_INTERRUPT(70, 3);
	//las de reloj y bla

//typedef struct str_idt_entry_fld {
//    unsigned short offset_0_15;
//   // unsigned short segsel;
//  unsigned short attr;
 //   unsigned short offset_16_31;
//} __attribute__((__packed__, aligned (8))) idt_entry;

 //reloj
 	
//soft


	// llamar a IDT_INTERRUPT una vez por cada entrada a configurar (es una macro que no soporta loops)
}
