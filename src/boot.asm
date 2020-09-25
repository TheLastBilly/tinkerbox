section .boot
bits 16
global boot

boot:
    ; Load disk id
    mov [disk_id], dl

    ;Turns on A20 line
    mov ax, 0x2401
    int 0x15

    ;Sets vga to vga mode
    mov ax, 0x13
    int 0x10

    ;load image from disk
    mov ah, 0x02
    mov al, 8
    mov ch, 0
    mov dh, 0
    mov cl, 2
    mov dl, [disk_id] 
    mov bx, kernel_entry
    int 0x13

    cli

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
    
    jmp CODE_SEG:kernel_init

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
    
done:
    cli
.loop:
    nop
    nop
    jmp .loop

welcome: db "Welcome to the makaloader!", 0x00
disk_id: db 0x00
    
times 510- ($-$$) db 0
dw 0xaa55

bits 32
kernel_entry:

kernel_init:
    mov esp, kernel_stack_top
    extern kentry
    call kentry
    cli
    hlt

section .bss
align 4

kernel_stack_bottom: equ $
	resb 16384 ; 16 KB
kernel_stack_top: