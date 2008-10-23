GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand, _int_80_hand, write, read
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug

EXTERN  int_08
EXTERN  int_80w
EXTERN  int_80r


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

	cmp al, 03h		;llama a read
	je	myread
	cmp al, 04h		;llama a write
	je	mywrite
	jmp	exit

myread:
	push	edx
	push	ecx
	push	ebx
	call    int_80r
	jmp	exit

mywrite:
	push	edx
	push	ecx
	push	ebx
	call    int_80w
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
