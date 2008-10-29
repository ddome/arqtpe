GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand, _int_80_hand, write, read, _int_09_hand
GLOBAL myin, myout, myinw, myoutw, myinl, myoutl
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug

EXTERN  int_08
EXTERN  int_80w
EXTERN  int_80r
EXTERN  int_09


SECTION .text


_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret

_mascaraPIC1:			; Escribe mascara del PIC 1
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	21h,al
        pop     ebp
        retn

_mascaraPIC2:			; Escribe mascara del PIC 2
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	0A1h,al
        pop     ebp
        retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn


_lidt:				; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR
	rol	ebx,16
	lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn


_int_08_hand:				; Handler de INT 8 ( Timer tick)
        push    ds
        push    es          ; Se salvan los registros
        pusha               ; Carga de DS y ES con el valor del selector
        mov     ax, 10h		; a utilizar.
        mov     ds, ax
        mov     es, ax
        call    int_08
        mov	al,20h			; Envio de EOI generico al PIC
		out	20h,al
		popa
        pop     es
        pop     ds
        iret



_int_80_hand:
	push	ds
	push	es
	pusha

	push eax

	mov	ax, 10h
	mov	ds, ax
	mov	es, ax

	pop eax

	cmp al, 03h		;llama a myread
	je	myread
	cmp al, 04h		;llama a mywrite
	je	mywrite
	jmp	exit

myread:
	push	edx
	push	ecx
	push	ebx
	call    int_80r ; funcion implementada en c
	jmp	exit

mywrite:
	push	edx
	push	ecx
	push	ebx
	call    int_80w ; funcion implementada en c
	jmp	exit

exit:
	pop	ebx
	pop	ecx
	pop	edx

	mov	al, 20h
	out	20h, al
	popa
	pop	es
	pop	ds
	iret

write:

		push    ebp
    	mov     ebp, esp

    	mov     ebx, [ebp+8]    ; fd
    	mov     ecx, [ebp+12]   ; buffer
    	mov     edx, [ebp+16]   ; cant
		mov		al, 04h
    	int     080h

	    mov     esp, ebp
	    pop     ebp
	    ret

read:

		push    ebp
    	mov     ebp, esp

    	mov     ebx, [ebp+8]    ; fd
    	mov     ecx, [ebp+12]   ; buffer
    	mov     edx, [ebp+16]   ; cant
		mov		al, 03h
    	int     080h



	    mov     esp, ebp
	    pop     ebp
	    ret

myout:
	push EBP
	mov EBP, ESP
	mov EAX, [EBP+12]
	mov EDX, [EBP+8]
	out DX, AL
	pop EBP
	ret

myin:
	push EBP
    mov EBP, ESP
	mov EDX, [EBP+8]
	mov ECX, [EBP+12]
	in AL, DX
	mov [ECX], AL
	pop	EBP
	ret
	
myoutw:
	push EBP
	mov EBP, ESP
	mov EAX, [EBP+12]
	mov EDX, [EBP+8]
	out DX, AX
	pop EBP
	ret

myinw:
	push EBP
    mov EBP, ESP
	mov EDX, [EBP+8]
	mov ECX, [EBP+12]
	in AX, DX
	mov [ECX], AX
	pop	EBP
	ret

myoutl:
	push EBP
	mov EBP, ESP
	mov EAX, [EBP+12]
	mov EDX, [EBP+8]
	out DX, EAX
	pop EBP
	ret

myinl:
	push EBP
    mov EBP, ESP
	mov EDX, [EBP+8]
	mov ECX, [EBP+12]
	in EAX, DX
	mov [ECX], EAX
	pop	EBP
	ret

; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;


_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
        retn


; Handler del teclado
_int_09_hand:			; Handler de INT 9 ( Teclado ).
	cli			; Deshabilito las interrupciones
	push    ds
        push    es
        pusha  			; Armo stack frame.

	mov     ax, 10h		; Carga en DS y ES con el valor del selector.
        mov     ds, ax		; a utilizar.
        mov     es, ax

	mov eax,0		; Lee del teclado el scancode y se lo pasa
	in al,60h		; a la funcion int_09 a travez del stack.
	push eax

	call int_09

	mov	al,20h		; Envio de EOI generico al PIC
	out	20h,al
	pop eax

	popa			; Armo stack frame.
        pop     es
        pop     ds
	sti			; Vuelvo a habilitar las interrupciones
        iret


_Lights:
    push	ebp
	mov		ebp, esp
	mov		al,[EBP+8]
	mov		ah,al

    cli                             ; Deshabilito interrupciones
    mov     al,0edh                 ; Cargo el Set/Reset Mode Indicator
    out     60h,al

l1: in      al,60h                  ; Espero el ACK del 8042
    cmp     al,0fah
    jnz     l1
    mov     al,ah                   ; Mando las nuevas luces
    out     60h,al
l2: in      al,60h                  ; Espero el ACK del 8042
    cmp     al,0fah
    jnz     l2
    sti                             ; habilito interrupciones de nuevo
	pop		ebp
    ret









