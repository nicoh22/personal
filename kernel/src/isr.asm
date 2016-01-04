; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00
sys_return:		dd 0x00

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_atender_tick
extern sched_tarea_actual
extern sched_to_idle
extern sched_remover_tarea	
;; Game
extern game_atender_tick
extern game_perro_mover
extern game_perro_cavar
extern game_perro_olfatear
extern game_perro_actual
extern game_perro_recibirOrden
extern game_atender_teclado
extern game_perro_termino
extern game_debug
extern game_syscall_manejar

;; Screen
extern printAux
extern screen_actualizar_reloj_global
extern print_hex
extern game_guardar_mapa
extern game_restaurar_mapa

extern globalDebug

;; Codigos error
msg0 db "Divide Error", 0
msg0_len equ    $ - msg0
msg1 db "Reserved", 0
msg1_len equ    $ - msg1
msg2 db "NMI Interrupt", 0
msg2_len equ    $ - msg2
msg3 db "Breakpoint", 0
msg3_len equ    $ - msg3
msg4 db "Overflow", 0
msg4_len equ    $ - msg4
msg5 db "BOUND Range Exceeded", 0
msg5_len equ    $ - msg5
msg6 db "Invalid Opcode (Undefined Opcode)", 0
msg6_len equ    $ - msg6
msg7 db "Device Not Available (No Math Coprocessor)", 0
msg7_len equ    $ - msg7
msg8 db "Double Fault", 0
msg8_len equ    $ - msg8
msg9 db "Coprocessor Segment Overrun (reserved)", 0
msg9_len equ    $ - msg9
msg10 db "Invalid TSS", 0
msg10_len equ    $ - msg10
msg11 db "Segment Not Present", 0
msg11_len equ    $ - msg11
msg12 db "Stack-Segment Fault", 0
msg12_len equ    $ - msg12
msg13 db "General Protection", 0
msg13_len equ    $ - msg13
msg14 db "Page Fault", 0
msg14_len equ    $ - msg14
msg16 db "x87 FPU Floating-Point Error (Math Fault)", 0
msg16_len equ    $ - msg16
msg17 db "Alignment Check", 0
msg17_len equ    $ - msg17
msg18 db "Machine Check", 0
msg18_len equ    $ - msg18
msg19 db "SIMD Floating-Point Exception", 0
msg19_len equ    $ - msg19
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;
%define GDT_TSS_IDLE 15 << 3
%macro ISR 1
global _isr%1

global _isr32
global _isr33
global _isr70


_isr%1:
	push edi;;salvo porque lo tengo que mostrar en el debug
	mov edi, [globalDebug]
	cmp edi,0x00
	je .seguirImprimiendo

	push eax
	push ebx
	push ecx
	push edx
	push esi
	push ebp
	;push eip
	push cs
	push ds
	push es
	push fs
	push gs
	push ss
	pushf
	push eax
	call game_guardar_mapa
	call game_debug;;algo pisaba seguro sino
	;;print_hex(uint numero, int size, uint x, uint y, unsigned short attr)

	;;siguiente	
	pop eax	
	mov esi,0x7F
	push esi
	mov esi,25
	push esi
	mov esi, 30
	push esi
	mov esi,8
	push esi
	push eax
	call print_hex

	add esp, 5*4
	
	;;siguiente	
	pop eax	
	mov esi,0x7F
	push esi
	mov esi,39
	push esi
	mov esi, 34
	push esi
	mov esi,8
	push esi
	push eax
	call print_hex

	add esp, 5*4


	;;siguiente	
	pop ss	
	mov esi,0x7F
	push esi
	mov esi,37
	push esi
	mov esi, 30
	push esi
	mov esi,4
	push esi
	push ss
	call print_hex

	add esp, 5*4

	;;siguiente
	pop gs	
	mov esi,0x7F
	push esi
	mov esi,35
	push esi
	mov esi, 30
	push esi
	mov esi,4
	push esi
	push gs
	call print_hex

	add esp, 5*4

	;;siguiente
	pop fs	
	mov esi,0x7F
	push esi
	mov esi,33
	push esi
	mov esi, 30
	push esi
	mov esi,4
	push esi
	push fs
	call print_hex

	add esp, 5*4

	;;siguiente
	pop es	
	mov esi,0x7F
	push esi
	mov esi,31
	push esi
	mov esi, 30
	push esi
	mov esi,4
	push esi
	push es
	call print_hex

	add esp, 5*4

	;;siguiente
	pop ds	
	mov esi,0x7F
	push esi
	mov esi,29
	push esi
	mov esi, 30
	push esi
	mov esi,4
	push esi
	push ds
	call print_hex

	add esp, 5*4
	
	;;siguiente
	pop cs	
	mov edi,0x7F
	push edi
	mov edi,27
	push edi
	mov edi, 30
	push edi
	mov edi,4
	push edi
	push cs
	call print_hex

	add esp, 5*4

	;;siguiente	
	mov esi,0x7F
	push esi
	mov esi,23
	push esi
	mov esi, 30
	push esi
	mov esi,8
	push esi
	mov esi, esp
	add esi,6*4
	push esi
	call print_hex
	
	add esp, 5*4

	;;siguiente
	pop ebp	
	mov esi,0x7F
	push esi
	mov esi,21
	push esi
	mov esi, 30
	push esi
	mov esi,8
	push esi
	push ebp
	call print_hex

	add esp, 5*4

	;;siguiente
	pop edi	
	mov esi,0x7F
	push esi
	mov esi,19
	push esi
	mov esi, 30
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex

	add esp, 5*4

	;;siguiente
	pop esi	
	mov edi,0x7F
	push edi
	mov edi,17
	push edi
	mov edi, 30
	push edi
	mov edi,8
	push edi
	push esi
	call print_hex

	add esp, 5*4

	;;siguiente
	pop edx	
	mov esi,0x7F
	push esi
	mov esi,15
	push esi
	mov esi, 30
	push esi
	mov esi,8
	push esi
	push edx
	call print_hex

	add esp, 5*4

	;;siguiente
	pop ecx	
	mov esi,0x7F
	push esi
	mov esi,13
	push esi
	mov esi, 30
	push esi
	mov esi,8
	push esi
	push ecx
	call print_hex

	add esp, 5*4

	;;siguiente
	pop ebx	
	mov esi,0x7F
	push esi
	mov esi,11
	push esi
	mov esi, 30
	push esi
	mov esi,8
	push esi
	push ebx
	call print_hex

	add esp, 5*4

	;;siguiente
	pop eax	
	mov esi,0x7F
	push esi
	mov esi,9
	push esi
	mov esi, 30
	push esi
	mov esi,8
	push esi
	push eax
	call print_hex

	add esp, 5*4

	;;siguiente
	mov edi,[esp-8]	
	mov esi,0x7F
	push esi
	mov esi,29
	push esi
	mov esi, 40
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4

	;;siguiente
	mov edi,[esp-12]	
	mov esi,0x7F
	push esi
	mov esi,30
	push esi
	mov esi, 40
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4

		;;siguiente
	mov edi,[esp-16]	
	mov esi,0x7F
	push esi
	mov esi,31
	push esi
	mov esi,40
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4
	
	;;siguiente
	mov edi,[esp-20]	
	mov esi,0x7F
	push esi
	mov esi,32
	push esi
	mov esi,40
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4

	;;siguiente
	mov edi,[esp-24]	
	mov esi,0x7F
	push esi
	mov esi,33
	push esi
	mov esi,40
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4

	;;siguiente
	mov edi,cr0	
	mov esi,0x7F
	push esi
	mov esi,9
	push esi
	mov esi,44
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4

	;;siguiente
	mov edi,cr2	
	mov esi,0x7F
	push esi
	mov esi,11
	push esi
	mov esi,44
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4

	;;siguiente
	mov edi,cr3	
	mov esi,0x7F
	push esi
	mov esi,13
	push esi
	mov esi,44
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4

	;;siguiente
	mov edi,cr4	
	mov esi,0x7F
	push esi
	mov esi,15
	push esi
	mov esi,44
	push esi
	mov esi,8
	push esi
	push edi
	call print_hex
	add esp, 5*4
	
.loopHastaY:
	in al, 0x60
	cmp al, 0x15
	jne .loopHastaY
	mov dword [globalDebug], 0x00 
	call game_restaurar_mapa
.seguirImprimiendo:
	;pushad	
	imprimir_texto_mp msg%1, msg%1_len, 0x07, 0x0, 0x0
	xor eax, eax
	str ax
	cmp ax, GDT_TSS_IDLE
	je .loopear
	push game_perro_actual
	call game_perro_termino	
	pop eax
	call sched_to_idle
	xor ax, ax
	mov ax, GDT_TSS_IDLE
	mov [sched_tarea_selector], ax
	jmp far [sched_tarea_offset] 
.loopear:
	mov eax, 1
	jmp $
	;me fui a otro lado y no me importa mas esta tss
	;popad
	;iret

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0

ISR 1

ISR 2

ISR 3

ISR 4

ISR 5

ISR 6

ISR 7

ISR 8

ISR 9

ISR 10

ISR 11

ISR 12

ISR 13

ISR 14

ISR 16

ISR 17

ISR 18

ISR 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

_isr32:
;que registros rompe?
pushad
call fin_intr_pic1
call sched_atender_tick
mov bx, ax
shl bx, 3
str ax
cmp ax, bx
je .salir
mov [sched_tarea_selector], bx
jmp far [sched_tarea_offset]
.salir:
popad
iret 

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
_isr33:
pushad
push eax 
call fin_intr_pic1
xor eax, eax
in al, 0x60
mov ebx, eax
push eax 
call game_atender_teclado
push ebx
call printAux
pop ebx
pop eax
pop eax
popad
iret

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
_isr70:
pushad
push ecx
push game_perro_actual
call game_syscall_manejar
mov [sys_return], eax ;me guardo el resultado
;si alguno llamo si o si cambio a la idle
;la idle nunca llama a esta int
call sched_to_idle
xor ax, ax
mov ax, GDT_TSS_IDLE 
mov [sched_tarea_selector], ax
jmp far [sched_tarea_offset]
pop ecx
pop ecx
;pop ecx;;por 32?
popad
mov eax, [sys_return]
iret





