
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

; /** DEFINES **/    >> SE RECOMIENDA COMPLETAR LOS DEFINES CON LOS VALORES CORRECTOS
	%define NULL 		0
	%define TRUE 		1
	%define FALSE 		0

	%define LISTA_SIZE 	    	 8
	%define OFFSET_PRIMERO 		 0

	%define NODO_SIZE     		 16
	%define OFFSET_SIGUIENTE   	 0
	%define OFFSET_PALABRA 		 8


section .rodata


section .data


section .text


;/** FUNCIONES DE PALABRAS **/
;-----------------------------------------------------------

	; unsigned char palabraLongitud( char *p );
	palabraLongitud:
		; COMPLETAR AQUI EL CODIGO
	;rdi *char
	;al res
		xor rcx, rcx
	.ciclo:		
		cmp byte [rdi+rcx], NULL	
		je .fin
		inc rcx
		jmp .ciclo
	.fin:
		mov al, cl
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
		; COMPLETAR AQUI EL CODIGO
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
		
		xor rcx, rcx
	.ciclo:
		mov dl, [rsi+rcx]		
		cmp byte [rdi+rcx], dl
	
	; char *palabraCopiar( char *p );
	palabraCopiar:
		; COMPLETAR AQUI EL CODIGO


;/** FUNCIONES DE LISTA Y NODO **/
;-----------------------------------------------------------

	; nodo *nodoCrear( char *palabra );
	nodoCrear:
		; COMPLETAR AQUI EL CODIGO

	; void nodoBorrar( nodo *n );
	nodoBorrar:
		; COMPLETAR AQUI EL CODIGO

	; lista *oracionCrear( void );
	oracionCrear:
		; COMPLETAR AQUI EL CODIGO

	; void oracionBorrar( lista *l );
	oracionBorrar:
		; COMPLETAR AQUI EL CODIGO

	; void oracionImprimir( lista *l, char *archivo, void (*funcImprimirPalabra)(char*,FILE*) );
	oracionImprimir:
		; COMPLETAR AQUI EL CODIGO


;/** FUNCIONES AVANZADAS **/
;-----------------------------------------------------------

	; float longitudMedia( lista *l );
	longitudMedia:
		; COMPLETAR AQUI EL CODIGO

	; void insertarOrdenado( lista *l, char *palabra, bool (*funcCompararPalabra)(char*,char*) );
	insertarOrdenado:
		; COMPLETAR AQUI EL CODIGO

	; void filtrarAltaLista( lista *l, bool (*funcCompararPalabra)(char*,char*), char *palabraCmp );
	filtrarPalabra:
		; COMPLETAR AQUI EL CODIGO

	; void descifrarMensajeDiabolico( lista *l, char *archivo, void (*funcImpPbr)(char*,FILE* ) );
	descifrarMensajeDiabolico:
		; COMPLETAR AQUI EL CODIGO
