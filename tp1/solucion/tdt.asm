; FUNCIONES de C
  extern malloc
  extern free
  extern strcpy
  extern tdt_agregar
  extern tdt_borrar
  
; FUNCIONES
  global tdt_crear
  global tdt_recrear
  global tdt_cantidad
  global tdt_agregarBloque
  global tdt_agregarBloques
  global tdt_borrarBloque
  global tdt_borrarBloques
  global tdt_traducir
  global tdt_traducirBloque
  global tdt_traducirBloques
  global tdt_destruir

; /** defines offsets y size **/
  %define TDT_OFFSET_IDENTIFICACION   0
  %define TDT_OFFSET_PRIMERA          8
  %define TDT_OFFSET_CANTIDAD        16
  %define TDT_SIZE                   20
  %define VALOR_OFFSET_VALIDO	     15 
  %define NULL	0

section .text

; =====================================
; tdt* tdt_crear(char* identificacion)
tdt_crear:
	;rdi *identificacion
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	mov rbx, rdi ; *identificacion

	call copyString
	mov r12, rax
	
	mov rdi, TDT_SIZE	
	call malloc
	;rax *tdt
	mov [rax + TDT_OFFSET_IDENTIFICACION], r12 
 	mov qword [rax + TDT_OFFSET_PRIMERA], NULL 
	mov dword [rax + TDT_OFFSET_CANTIDAD], NULL
	
	
	pop r12
	pop rbx
	pop rbp
	ret

; =====================================
; void tdt_recrear(tdt** tabla, char* identificacion)
tdt_recrear:
	push rbp	
	mov rbp, rsp
	push rbx
	push r12

	mov rbx, rdi; **tabla
	mov r12, rsi; *identificacion
	mov rdi, [rbx]
	call borrarTodasLasClaves
	
	cmp r12, NULL
	je .usarIdentAnterior
	
	mov rdi, r12
	call copyString
	
	mov rcx, [rbx]
	mov rdi, [rcx + TDT_OFFSET_IDENTIFICACION]
	mov [rcx + TDT_OFFSET_IDENTIFICACION], rax
	call free

.usarIdentAnterior:
	
	pop r12
	pop rbx
	pop rbp
	ret
; =====================================
; uint32_t tdt_cantidad(tdt* tabla)
tdt_cantidad:
	mov rax, [rdi + TDT_OFFSET_CANTIDAD]
	ret

; =====================================
; void tdt_agregarBloque(tdt* tabla, bloque* b)
tdt_agregarBloque:
	lea rdx, [rsi + 3]
	jmp tdt_agregar 

; ====================================:
; void tdt_agregarBloques(tdt* tabla, bloque** b)

tdt_agregarBloques:
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	mov rbx, rdi ; *tdt
	mov r12, rsi ; **bloque
.ciclo:
	mov rcx, [r12] ; *bloque
	cmp rcx, 0
	je .break
	mov rdi, rbx
	mov rsi, rcx
	call tdt_agregarBloque
	add r12, 8
	jmp .ciclo
.break:
	pop r12
	pop rbx
	pop rbp
	ret
 
; =====================================
; void tdt_borrarBloque(tdt* tabla, bloque* b)
tdt_borrarBloque:
	jmp tdt_borrar
        
; =====================================
; void tdt_borrarBloques(tdt* tabla, bloque** b)
tdt_borrarBloques:
        
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	mov rbx, rdi ; *tdt
	mov r12, rsi ; **bloque
.ciclo:
	mov rcx, [r12]
	cmp rcx, 0
	je .break
	mov rdi, rbx
	mov rsi, rcx
	call tdt_borrarBloque
	add r12, 8
	jmp .ciclo
.break:
	pop r12
	pop rbx
	pop rbp
	ret
; =====================================
; void tdt_traducir(tdt* tabla, uint8_t* clave, uint8_t* valor)
tdt_traducir:
	; rdi *tabla, rsi *clave, rdx *valor
	push rbp
	mov rbp, rsp
	push rbx

	xor rax, rax
	mov rbx, [rdi + TDT_OFFSET_PRIMERA]; *tdtN1
	
	cmp rbx, NULL
	je .fin
	
	mov al, [rsi + 2]
	mov rbx, [rbx + rax*8]; *tdtN2
	
	cmp rbx, NULL
	je .fin
	
	mov al, [rsi + 1]
	mov rbx, [rbx + rax*8]; *tdtN3
	
	cmp rbx, NULL
	je .fin
	
	mov al, [rsi]
	shl rax, 1
	lea rbx, [rbx + rax*8]; *valorvalido
	
	cmp byte [rbx + VALOR_OFFSET_VALIDO], 0
	je .fin
	xor rcx, rcx	
.ciclo:	
	cmp rcx, 15
	jge .fin
	mov al, [rbx + rcx]
	mov [rdx + rcx], al
	inc rcx
	jmp .ciclo
.fin: 
	pop rbx
	pop rbp
	ret
        
; =====================================
; void tdt_traducirBloque(tdt* tabla, bloque* b)
tdt_traducirBloque:
	lea rdx, [rsi + 3]
	jmp tdt_traducir
; =====================================
; void tdt_traducirBloques(tdt* tabla, bloque** b)
tdt_traducirBloques:        
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	mov rbx, rdi ; *tdt
	mov r12, rsi ; **bloque
.ciclo:
	mov rcx, [r12]
	cmp rcx, 0
	je .break
	mov rdi, rbx
	mov rsi, rcx
	call tdt_traducirBloque
	add r12, 8
	jmp .ciclo
.break:
	pop r12
	pop rbx
	pop rbp
	ret

; =====================================
; void tdt_destruir(tdt** tabla)
tdt_destruir:
	;rdi **tabla
	push rbp
	mov rbp, rsp
	push rbx
	sub rsp, 8; alineada 
	
	mov rbx, [rdi]	
	mov rdi, [rdi]
	call borrarTodasLasClaves
      
.fin:
	mov rdi, [rbx + TDT_OFFSET_IDENTIFICACION]	
	call free
        
	mov rdi, rbx
	call free
    
	sub rsp, 8
	pop r14
	pop r13
	pop r12
	pop rbp
	ret

; =======AUXILIARES=======

copyString:
; esto devuelve un nuevo string por rax 
; con los mismos caracteres del string recibido en rdi

	;rdi *string
	push rbp
	mov rbp, rsp
	push rbx
	sub rsp, 8; alineada	

	mov rbx, rdi; *string original	
	xor rax, rax
.ciclo:
	cmp byte [rdi + rax], 0
	je .break
	inc rax
	jmp .ciclo
.break:
	mov rdi, rax
	inc rdi		;longitud del string + caracter terminacion
	call malloc
	
	mov rdi, rax
	mov rsi, rbx
	
	call strcpy
	
	add rsp, 8
	pop rbx
	pop rbp
	ret



borrarTodasLasClaves:
;Borra todas las claves existentes en una tdt    
;pero deja intacto el struct

	;rdi *tdt
	;TODO iterar solo por las claves que existen y no todas las posibles. 
	push rbp
	mov rbp, rsp
	sub rsp, 16; alineada
	push rbx
	push r12
	push r13
	push r14; alineada


	mov rbx, rdi

	xor r12, r12
	xor r13, r13
	xor r14, r14

.tercNivel:

	xor rax, rax
	mov al, r12b
	shl rax, 8 
	mov al, r13b
	shl rax, 8
	mov al, r14b

	mov [rbp], rax

	mov rdi, rbx
	mov rsi, rbp
	call tdt_borrar

	inc r14
	cmp r14, 256
	je .segNivel
	jmp .tercNivel

.segNivel:
	xor r14, r14
	inc r13
	cmp r13, 256
	je .primNivel	
	jmp .tercNivel

.primNivel:
	xor r13, r13
	inc r12
	cmp r12, 256
	je .fin
	jmp .tercNivel

.fin:
	pop r14
	pop r13
	pop r12
	pop rbx
	add rsp, 16
	pop rbp
	ret



