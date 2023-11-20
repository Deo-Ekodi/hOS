ORG 0			; initial
BITS 16				; 16 bits mode

jmp 0x7c0:start
start:
	cli				;clear interrupts
	mov ax, 0x7c0
	mov ds, ax
	mov es, ax
	mov ax, 0x00
	mov ss, ax
	mov sp, 0x7c00
	sti				;enable interrupts
	mov si, message
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

message: db 'This is hOS', 0

times 510-($ - $$) db 0 	;510 bytes to be used
dw 0xAA55
