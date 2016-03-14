/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Tipos basicos */
/* -------------------------------------------------------------------------- */
#define NULL                    0
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

/* Constantes basicas */
/* -------------------------------------------------------------------------- */
#define PAGE_SIZE               0x00001000
#define TASK_SIZE               4096

#define BOOTSECTOR              0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                  0x0000210 /* direccion fisica de comienzo del kernel */


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 32

#define GDT_IDX_NULL_DESC           	0
#define GDT_IDX_CODE_KERNEL	            8
#define GDT_IDX_CODE_USER	            9
#define GDT_IDX_DATA_KERNEL             10
#define GDT_IDX_DATA_USER	            11
#define GDT_IDX_STACK_KERNEL	        12
#define GDT_IDX_KERNEL_SCREEN           13
#define GDT_IDX_INITIAL_TASK            14
#define GDT_IDX_IDLE_TASK               15

#define GDT_IDX_PLAYER_1_DOG_1          16
#define GDT_IDX_PLAYER_1_DOG_2          17
#define GDT_IDX_PLAYER_1_DOG_3          18
#define GDT_IDX_PLAYER_1_DOG_4          19
#define GDT_IDX_PLAYER_1_DOG_5         	20
#define GDT_IDX_PLAYER_1_DOG_6          21
#define GDT_IDX_PLAYER_1_DOG_7          22
#define GDT_IDX_PLAYER_1_DOG_8          23

#define GDT_IDX_PLAYER_2_DOG_1          24
#define GDT_IDX_PLAYER_2_DOG_2          25
#define GDT_IDX_PLAYER_2_DOG_3          26
#define GDT_IDX_PLAYER_2_DOG_4          27
#define GDT_IDX_PLAYER_2_DOG_5          28
#define GDT_IDX_PLAYER_2_DOG_6          29
#define GDT_IDX_PLAYER_2_DOG_7          30
#define GDT_IDX_PLAYER_2_DOG_8          31

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */

#define GDT_OFF_NULL_DESC           	(GDT_IDX_NULL_DESC      	 << 3)
#define GDT_OFF_CODE_KERNEL	            (GDT_IDX_CODE_KERNEL	     << 3)
#define GDT_OFF_CODE_USER	            (GDT_IDX_CODE_USER	         << 3) + 0x3
#define GDT_OFF_DATA_KERNEL             (GDT_IDX_DATA_KERNEL         << 3)
#define GDT_OFF_DATA_USER	            (GDT_IDX_DATA_USER	         << 3)+ 0x3
#define GDT_OFF_STACK_KERNEL	        (GDT_IDX_STACK_KERNEL	     << 3)
#define GDT_OFF_KERNEL_SCREEN           (GDT_IDX_KERNEL_SCREEN       << 3)
#define GDT_OFF_INITIAL_TASK            (GDT_IDX_INITIAL_TASK        << 3)
#define GDT_OFF_IDLE_TASK               (GDT_IDX_IDLE_TASK           << 3)

#define GDT_OFF_PLAYER_1_DOG_1          (GDT_IDX_PLAYER_1_DOG_1      << 3)
#define GDT_OFF_PLAYER_1_DOG_2          (GDT_IDX_PLAYER_1_DOG_2      << 3)
#define GDT_OFF_PLAYER_1_DOG_3          (GDT_IDX_PLAYER_1_DOG_3      << 3)
#define GDT_OFF_PLAYER_1_DOG_4          (GDT_IDX_PLAYER_1_DOG_4      << 3)
#define GDT_OFF_PLAYER_1_DOG_5         	(GDT_IDX_PLAYER_1_DOG_5      << 3)
#define GDT_OFF_PLAYER_1_DOG_6          (GDT_IDX_PLAYER_1_DOG_6      << 3)
#define GDT_OFF_PLAYER_1_DOG_7          (GDT_IDX_PLAYER_1_DOG_7      << 3)
#define GDT_OFF_PLAYER_1_DOG_8          (GDT_IDX_PLAYER_1_DOG_8      << 3)

#define GDT_OFF_PLAYER_2_DOG_1          (GDT_IDX_PLAYER_2_DOG_1      << 3)
#define GDT_OFF_PLAYER_2_DOG_2          (GDT_IDX_PLAYER_2_DOG_2      << 3)
#define GDT_OFF_PLAYER_2_DOG_3          (GDT_IDX_PLAYER_2_DOG_3      << 3)
#define GDT_OFF_PLAYER_2_DOG_4          (GDT_IDX_PLAYER_2_DOG_4      << 3)
#define GDT_OFF_PLAYER_2_DOG_5          (GDT_IDX_PLAYER_2_DOG_5      << 3)
#define GDT_OFF_PLAYER_2_DOG_6          (GDT_IDX_PLAYER_2_DOG_6      << 3)
#define GDT_OFF_PLAYER_2_DOG_7          (GDT_IDX_PLAYER_2_DOG_7      << 3)
#define GDT_OFF_PLAYER_2_DOG_8          (GDT_IDX_PLAYER_2_DOG_8      << 3)


/* Selectores de segmentos */
/* -------------------------------------------------------------------------- */


#endif  /* !__DEFINES_H__ */
