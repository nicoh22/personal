; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start
;;;;;GDT
extern GDT_DESC
%define GDT_KERNEL_CODE 8 << 3
%define GDT_USER_CODE 9 << 3
%define GDT_KERNEL_DATA 10 << 3
%define GDT_USER_DATA 11 << 3
%define GDT_KERNEL_STACK 12 << 3
%define GDT_KERNEL_SCREEN 13 << 3
%define GDT_TSS_INICIAL 14 << 3
%define GDT_TSS_IDLE 15 << 3

;;;;;Pantalla
extern screen_inicializar
extern screen_clean
;;;;;IDT
extern idt_inicializar
extern IDT_DESC

;;;;;MMU
extern mmu_inicializar_dir_kernel
extern mmu_inicializar
extern mmu_unmapear_pagina

;;;;;PIC 
extern resetear_pic
extern habilitar_pic
extern deshabilitar_pic

extern tss_inicializar
extern sched_inicializar
extern game_inicializar
; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
; Deshabilitar interrupciones
	cli

    ; Cambiar modo de video a 80 X 50
	mov ax, 0003h
	int 10h ; set mode 03h
	xor bx, bx
	mov ax, 1112h
	int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0


    ; Habilitar A20
	call habilitar_A20
    ; Cargar la GDT   
	lgdt [GDT_DESC]
    ; Setear el bit PE del registro CR0
	mov eax, cr0
	or eax, 1
	mov cr0, eax
    
	; Saltar a modo protegido
	jmp GDT_KERNEL_CODE:modo_protegido
	
BITS 32
	modo_protegido:
    ; Establecer selectores de segmentos
	mov ax, GDT_KERNEL_DATA
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ax, GDT_KERNEL_STACK
	mov ss, ax ; esta es cualquiera mepa
		
    ; Establecer la base de la pila
	mov ebp, 0x27000
	mov esp, ebp
    ; Imprimir mensaje de bienvenida
	imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 2, 0
	xor ax, ax
	mov ax, GDT_KERNEL_SCREEN
	mov gs, ax
	mov word [gs:0x00000], 0X0C50
    
	call idt_inicializar
    
	lidt [IDT_DESC]
	call screen_clean
	;;;;Prueba IDT;;;; 
	;mov eax, 0
	;div ebx
	
    ; Inicializar el juego
	call game_inicializar
    ; Inicializar pantalla
	call screen_inicializar
	xchg bx,bx
    ; Inicializar el manejador de memoria
	call mmu_inicializar 
    ; Inicializar el directorio de paginas
	call mmu_inicializar_dir_kernel

    ; Cargar directorio de paginas
	mov cr3, eax
    ; Habilitar paginacion
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
		
	;esta rutina desmapea la ultima pagina del 
	;area libre del kernel
	;xor edx, edx
	;mov edx, 0x3FF000
	;mov ebx, cr3
	;push ebx
	;push edx
	;call mmu_unmapear_pagina
   

	; Inicializar tss
	; Inicializar tss de la tarea Idle
	call tss_inicializar

    ; Inicializar el scheduler
	call sched_inicializar	
	;call game_inicializar
    ; Inicializar la IDT
	call deshabilitar_pic
	call resetear_pic  
	call habilitar_pic
	sti

    ; Cargar IDT

    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

	xchg bx,bx
	xor eax, eax
	mov ax, GDT_TSS_INICIAL
	ltr ax
	jmp GDT_TSS_IDLE:0

	;call tss_inicializar
	;xor eax, eax
	;mov ax, GDT_TSS_IDLE
	;ltr ax
	;jmp GDT_TSS_IDLE:0
    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle


    ; Ciclar infinitamente (por si algo sale mal...)
	mov eax, 0xFFFF
	mov ebx, 0xFFFF
	mov ecx, 0xFFFF
	mov edx, 0xFFFF
	xchg bx,bx
	
	jmp $
	jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
