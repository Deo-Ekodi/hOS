ORG 0			; initial
BITS 16				; 16 bits mode
_start:
	jmp short start
	nop

times 33 db 0

start:
	jmp 0x7c0:step2


; below are interrupts
;handle_zero:				; responnsible for handling interrupt zero '0'
; 	mov ah, 0eh
; 	mov al, 'A'
; 	mov bx, 0x00
; 	int 0x10
; 	iret					; return from interrupt
; 
; handle_one:
; 	mov ah, 0eh
; 	mov al, 'V'
; 	mov bx, 0x00
; 	int 0x10
; 	iret

step2:
	cli				;clear interrupts
	mov ax, 0x7c0
	mov ds, ax
	mov es, ax
	mov ax, 0x00
	mov ss, ax
	mov sp, 0x7c00
	sti				;enable interrupts

;	mov word[ss:0x00], handle_zero	; first two bytes take offset
;	mov word[ss:0x02], 0x7c00		; next two bytes take segment
;
;	mov word[ss:0x04], handle_one
;	mov word[ss:0x06], 0x7c0
;	int 1
	
;	mov si, message
;	call print

	mov ah, 2		;move sector command
	mov al, 1 		;one sector to read
	mov ch, 0 		;cylinder number
	mov cl, 2		;read sector 2
	mov dh, 0 		;head number
	mov bx, buffer
	int 0x13
	jc error
	mov si, buffer
	call print
	jmp $

error:
	mov si, error_message
	call print
	jmp $


print:
	mov bx, 0
.loop:
	lodsb
	cmp al, 0
	je .done
	call print_char
	jmp .loop
.done:
	ret
	
print_char:
	mov ah, 0eh
	int 0x10
	ret

;message: db 'This is hOS', 0
error_message: db 'Failed to load sector', 0

times 510-($ - $$) db 0 	;510 bytes to be used
dw 0xAA55

buffer:
