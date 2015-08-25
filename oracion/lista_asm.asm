
; PALABRA
	global palabraLongitud
	global palabraMenor
	global palabraFormatear
	global palabraImprimir
	global palabraCopiar

; LISTA y NODO
	global nodoCrear
	global nodoBorrar
	global oracionCrear
	global oracionBorrar
	global oracionImprimir

; AVANZADAS
	global longitudMedia
	global insertarOrdenado
	global filtrarPalabra
	global descifrarMensajeDiabolico

; YA IMPLEMENTADAS EN C
	extern palabraIgual
	extern insertarAtras
	extern malloc
	extern fprintf
	extern free
	extern fopen
	extern fclose
; /** DEFINES **/    >> SE RECOMIENDA COMPLETAR LOS DEFINES CON LOS VALORES CORRECTOS
	%define NULL 		0
	%define TRUE 		1
	%define FALSE		0

	%define LISTA_SIZE 	    	 8
	%define OFFSET_PRIMERO 		 0

	%define NODO_SIZE     		 16
	%define OFFSET_SIGUIENTE   	 0
	%define OFFSET_PALABRA 		 8


section .rodata
format: DB "%s", 10, 0
append: DB "a", 0
section .data


section .text


;/** FUNCIONES DE PALABRAS **/
;-----------------------------------------------------------

	; unsigned char palabraLongitud( char *p );
	palabraLongitud:
		; COMPLETAR AQUI EL CODIGO
	;rdi *char
	;al res
		xor rax, rax
	.ciclo:
		cmp byte [rdi+rax], NULL
		je .fin
		inc rax
		jmp .ciclo
	.fin:
		ret

	; bool palabraMenor( char *p1, char *p2 );
	palabraMenor:
		; COMPLETAR AQUI EL CODIGO
		;rdi p1
		;rsi p2
		;al bool
		xor rcx, rcx
	.ciclo:
		mov dl, [rsi+rcx]
		cmp byte [rdi+rcx], dl
		jne .break
		;control de fin de string?
		cmp dl, NULL
		je .break
		cmp byte [rdi+rcx], NULL
		je .break
		inc rcx
		jmp .ciclo
	.break:
		cmp byte [rdi+rcx], dl
		jge .mayor
		mov rax, TRUE
		ret
	.mayor:
		mov rax, FALSE
		ret

	; void palabraFormatear( char *p, void (*funcModificarString)(char*) );
	palabraFormatear:
		;rdi p
		;rsi funcion
		push rbp
		mov rbp, rsp

		call rsi

		pop rbp
		ret

	; void palabraImprimir( char *p, FILE *file );
	palabraImprimir:
		;rdi *char
		;rsi *FILE
		push rbp
		mov rbp, rsp

		mov rdx, rdi
		mov rdi, rsi
		mov rsi, format

		call fprintf ; rdi *FILE rsi *format + parametros(rdx, rcx)

		pop rbp
		ret



	; char *palabraCopiar( char *p );
	palabraCopiar:
		;rdi *char
		push rbp
		mov rbp, rsp
		push rbx
		push r12
		mov r12, rdi 
		call palabraLongitud ; al
		
		xor rbx, rbx
		mov bl, al
		
		xor rdi, rdi
		mov dil, al 
		inc rdi
		call malloc ; rax *char
		
		xor rcx, rcx
	.ciclo:
		; rbx longitud	
		; rax *res
		; r12 *p
		
		mov dl, [r12 + rcx]
		mov [rax + rcx], dl
		inc rcx
		cmp rbx, rcx
		jne .ciclo
		
		mov byte [rax + rcx], NULL
		
		pop r12
		pop rbx
		pop rbp
		ret


;/** FUNCIONES DE LISTA Y NODO **/
;-----------------------------------------------------------

	; nodo *nodoCrear( char *palabra );
	nodoCrear:
		;rdi *char
		push rbp
		mov rbp, rsp
		sub rsp, 8
		push rbx
		
		mov rbx, rdi
		mov rdi, NODO_SIZE
		call malloc ; rax *nodo
		
		mov qword [rax + OFFSET_SIGUIENTE], NULL
		mov [rax + OFFSET_PALABRA], rbx
		pop rbx
		add rsp, 8
		pop rbp
		ret

	; void nodoBorrar( nodo *n );
	nodoBorrar:
		; COMPLETAR AQUI EL CODIGO
		push rbp
		mov rbp, rsp
		call free
		pop rbp
		ret
		
	; lista *oracionCrear( void );
	oracionCrear:
		; void
		push rbp
		mov rbp, rsp
		
		mov rdi, LISTA_SIZE
		call malloc
		
		mov qword [rax + OFFSET_PRIMERO], NULL
		pop rbp
		ret
		
	; void oracionBorrar( lista *l );
	oracionBorrar:
		; rdi lista
		push rbp
		mov rbp, rsp
		push rbx
		push r12
		
		mov rbx, rdi
		mov r12, [rbx + OFFSET_PRIMERO]
		
	.ciclo:
		cmp r12, NULL
		je .fin
		mov rdi, r12
		mov r12, [r12 + OFFSET_SIGUIENTE]
		call nodoBorrar
		jmp .ciclo
	
	.fin:
		mov rdi, rbx
		call free
		pop r12
		pop rbx
		pop rbp
		ret
		
		
		
	; void oracionImprimir( lista *l, char *archivo, void (*funcImprimirPalabra)(char*,FILE*) );
	oracionImprimir:
		;rdi lista 
		;rsi *char
		;rdx funcion 
		push rbp
		mov rbp, rsp
		sub rsp, 16
		push rbx
		push r12
		
		mov [rbp - 8], rdi
		mov [rbp - 16], rdx
		mov rdi, rsi 
		mov rsi, append
		call fopen
		mov rbx, rax
		
	.ciclo:
		cmp r12, NULL
		je .fin
		mov rdi, r12
		mov rsi, rbx
		call [rbp - 16]
		mov r12, [r12 + OFFSET_SIGUIENTE]
		jmp .ciclo
		
	.fin:
		mov rdi, rbx
		call fclose
		
		pop r12
		pop rbx
		add rsp, 16
		pop rbp
		ret

;/** FUNCIONES AVANZADAS **/
;-----------------------------------------------------------

	; float longitudMedia( lista *l );
	longitudMedia:
		; rdi lista
		; xmm0 float
		push rbp
		mov rbp, rsp
		sub rsp, 16
		push rbx
		push r12
		mov qword [rsp - 8], 0
		xor rbx, rbx
		mov r12, [rdi + OFFSET_PRIMERO]
		
	.ciclo:
		cmp r12, NULL
		je .fin
		mov rdi, r12	
		call palabraLongitud
		add bl, al
		inc qword [rsp - 8]
		jmp .ciclo
		
	.fin:
		xorpd xmm0, xmm0
		cmp rbx, 0
		je .volver
			
		  
	.volver:
		pop r12
		pop rbx
		pop rbp
		ret

	; void insertarOrdenado( lista *l, char *palabra, bool (*funcCompararPalabra)(char*,char*) );
	insertarOrdenado:
		; rdi lista
		; rsi palabra
		; rdx funcion
		
		push rbp
		mov rbp, rsp
		sub rsp, 24
		push r12
		
		mov r12, [rdi + OFFSET_PRIMERO]
		mov [rsp - 8], rdx
		mov [rsp - 16], rsi
		
		cmp r12, NULL
		Jne .ciclo
		lea r12, [rdi + OFFSET_PRIMERO]
		jmp .fin
		
	.ciclo:
		cmp [r12], NULL
		je .fin
		
		call [rsp - 8]
		cmp al, TRUE
		je .fin
		
		mov r12, [r12]
		add r12, OFFSET_SIGUIENTE
		jmp .ciclo
	.fin:
		mov rdi, [rsp - 16]	
		call nodoCrear
		mov rdx, [r12]
		mov [rax + OFFSET_SIGUIENTE], rdx
		mov [r12], rax
		
	
	.volver:
		pop rbp
		ret

	; void filtrarAltaLista( lista *l, bool (*funcCompararPalabra)(char*,char*), char *palabraCmp );
	filtrarPalabra:
		; COMPLETAR AQUI EL CODIGO

	; void descifrarMensajeDiabolico( lista *l, char *archivo, void (*funcImpPbr)(char*,FILE* ) );
	descifrarMensajeDiabolico:
		; COMPLETAR AQUI EL CODIGO
