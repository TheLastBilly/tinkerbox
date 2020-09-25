section .boot
bits 16
global boot

boot:
    ;Turns on A20 line
    mov ax, 0x2401
    int 0x15

    ;Sets vga to text mode
    mov ah, 0x0e

    ;Print our beloved welcome message
    mov esi, welcome
    call print

    ;Loads the global descriptor table to the cpu
    lgdt [gdt_pointer]
    mov eax, cr0
    or eax, 0x01 ;Set protected mode bit
    mov cr0, eax

    ;Set segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp CODE_SEG:init ;jump to the bootloader's entry point

;Define the gdt table, more info on the subject can be found here: http://3zanders.co.uk/2017/10/16/writing-a-bootloader2/
gdt_start:
	dq 0x0
gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_end:
gdt_pointer:
    dw gdt_end - gdt_start
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start ;Code segment offset
DATA_SEG equ gdt_data - gdt_start ; Data segment offset

; Main function
init:

    jmp done


; Print a character to VGA
print:
    push eax
.loop:
    lodsb
    cmp al, 0
    je print.end
    int 0x10
    jmp .loop
print.end:
    pop eax
    ret
    
done:
    cli
.loop:
    nop
    nop
    jmp .loop

welcome: db "Welcome to the makaloader!", 0x00
    
times 510- ($-$$) db 0
dw 0xaa55