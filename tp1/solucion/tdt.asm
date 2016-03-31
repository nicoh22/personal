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

section .text

; =====================================
; tdt* tdt_crear(char* identificacion)
tdt_crear:
	;rdi *identificacion
	push rbp
	mov rbp, rsp
	sub rsp, 8
	push rdi 
;	
	call longString
	mov rdi, rax
	inc rdi		;longitud del string + caracter terminacion
	call malloc
	mov rdi, rax
	pop rsi
	add rsp, 8
	call strcpy 

	push rax	
	sub rsp, 8

	mov rdi, TDT_SIZE	
	call malloc
	;rax *tdt
	add rsp, 8
	pop rdi
	mov [rax + TDT_OFFSET_IDENTIFICACION], rdi
 	mov qword [rax + TDT_OFFSET_PRIMERA], 0 
	mov dword [rax + TDT_OFFSET_CANTIDAD], 0 
	
	pop rbp
	ret

; =====================================
; void tdt_recrear(tdt** tabla, char* identificacion)
tdt_recrear:

	
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

; =====================================:
; void tdt_agregarBloques(tdt* tabla, bloque** b)

tdt_agregarBloques:
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
	xor rax, rax
	mov rbx, [rdi + TDT_OFFSET_PRIMERA]; *tdtN1
	
	mov al, [rsi]
	mov rbx, [rbx + rax*8]; *tdtN2
	
	mov al, [rsi + 1]
	mov rbx, [rbx + rax*8]; *tdtN3
	
	
	mov al, [rsi + 2]
	shl rax, 1
	lea rbx, [rbx + rax*8]; *valorvalido

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
	sub rsp, 24
	push rbx
	push r12
	push r13

	mov rbx, rdi
	
	xor r12, r12
	xor r13, r13
	xor r14, r14

.tercNivel:
	
	xor rax, rax
	mov al, r12b
	shl rax, 1
	mov al, r13b
	shl rax, 1
	mov al, r14b
	
	mov [rbp + 24], rax
	
	mov rdi, rbx
	lea rsi, [rbp + 24]
	call tdt_borrar

	inc r14
	cmp r14, 255
	je .segNivel
	jmp .tercNivel

.segNivel:
	xor r14, r14
	inc r13
	cmp r13, 255
	je .primNivel	
	jmp .tercNivel

.primNivel:
	xor r13, r13
	inc r12
	cmp r12, 255
	je .fin
	jmp .tercNivel
	
.fin:
	mov rdi, rbx	
	call free

	pop rbp
	ret

; =======AUXILIARES=======

longString:
	;rdi *string

	xor rax, rax
.ciclo:
	cmp byte [rdi + rax], 0
	je .break
	inc rax
.break:
	ret

; esto devuelve la longitud del string sin contar el 
; caracter de terminacion de string (0)

