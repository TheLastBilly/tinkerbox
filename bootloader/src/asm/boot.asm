section .boot
bits 16
global boot

KERNEL_STACK_SIZE equ 16384

boot:
    ; Load disk id
    mov [disk_id], dl

    ;Sets vga to text mode
    mov ax, 0x03
    int 0x10
    
    ;Enable interrups and cleac segment regs
    sti
    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ;Gets VESA bios info
    push es
    mov ax, 0x4f00
    mov di, vesa_params
    int 0x10
    pop es
    cmp ax, 0x4f
    jne print_vesa_error

    ;Turns on A20 line
    mov ax, 0x2401
    int 0x15

    ;load image from disk
    mov ah, 0x02
    mov al, 0x60
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

disk_id: db 0x00
    
print:
    lodsb
    
    cmp al,0
    je .done
    
    mov ah, 0x0e
    int 0x10

    jmp print

.done:
    ret

print_vesa_error:
    mov si, vesa_error
    call print
    jmp done
    
done:
    cli
    hlt

vesa_error: db "error getting vesa info",0x00 

times 510- ($-$$) db 0
dw 0xaa55

bits 32
kernel_entry:

kernel_init:
    ;Give the kernel the position of the kernel params
    mov esi, [kernel_params]
    mov ecx, (kernel_params_end - kernel_params)

    ;Set the stack pointer
    mov esp, kernel_stack_top

    ;Call kernel
    extern kmain
    call kmain
    cli
    hlt

kernel_params:
    vesa_return: db 0x00
    vesa_params:
        resb 512
    vesa_params_end:
kernel_params_end:

section .bss
align 4
kernel_stack_bottom: equ $
	resb KERNEL_STACK_SIZE 
kernel_stack_top: