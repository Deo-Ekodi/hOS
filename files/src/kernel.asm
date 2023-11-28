[BITS 32]

global _start
; global problem ;; for testing interrupt
extern kernel_main ;; entry point for C function
DATA_SEG equ 0x10
CODE_SEG equ 0x00

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ; Enable the A20 line
    in al, 0x92
    or al, 2
    out 0x92, al

    ;remap of Master Programmable interrupt Controller
    mov al, 00010001b
    out 0x20, al
    mov al, 0x20
    out 0x20, al

    mov al, 00000001b
    out 0x21, al

    sti
    
    call kernel_main

    jmp $

; problem:
;     mov eax, 0
;     div eax

times 512-($ - $$) db 0
