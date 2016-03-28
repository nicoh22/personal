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
 	mov qword [rax + TDT_OFFSET_PRIMERA], NULL
	mov dword [rax + TDT_OFFSET_CANTIDAD], 0 
	
	pop rbp
	ret

;TODO tengo que copiar el string identificacion?	
; Si para algo esta strcpy definida arriba
;TODO implementar longString

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

; =====================================
; void tdt_agregarBloques(tdt* tabla, bloque** b)
tdt_agregarBloques:
        
; =====================================
; void tdt_borrarBloque(tdt* tabla, bloque* b)
tdt_borrarBloque:
	jmp tdt_borrar
        
; =====================================
; void tdt_borrarBloques(tdt* tabla, bloque** b)
tdt_borrarBloques:
        
; =====================================
; void tdt_traducir(tdt* tabla, uint8_t* clave, uint8_t* valor)
tdt_traducir:
        
; =====================================
; void tdt_traducirBloque(tdt* tabla, bloque* b)
tdt_traducirBloque:
	lea rdx, [rsi + 3]
	jmp tdt_traducir
; =====================================
; void tdt_traducirBloques(tdt* tabla, bloque** b)
tdt_traducirBloques:
        
; =====================================
; void tdt_destruir(tdt** tabla)
tdt_destruir:


