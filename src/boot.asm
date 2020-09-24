bits 16
org 0x7c00

boot:
    ;Turns on A20 line
    mov ax, 0x2401
    int 0x15

    ;Sets vga to text mode
    mov ax, 0x3
    int 0x10

    ;Lods the global descriptor table to the cpu
    lgdt [gdt_pointer]
    mov eax, cr0
    or eax, 0x01 ;Set protected mode bit
    mov cr0, eax
    
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

bits 32

init:
    ;Set segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ;Set VGA to blue
    mov ebx, 0xb8000
    
    ;Print our beloved welcome message
    push welcome
    call print

    push welcome
    call print

    jmp done

print:
    push ebp
    mov ebp, esp
    push esi

    mov esi, [ebp+8]; Get the string to print and put it on esi
    push ecx
.loop:
    lodsb
    cmp al, 0 ; Is it the end of the string?
    je print_end
    mov ecx, [text_properties]
    or eax, ecx ; Apply proteries to text
    mov word [ebx], ax ; Move it to the buffer
    add ebx, 2
    jmp .loop

print_end:
    pop ecx
    pop esi
    mov esp, ebp
    pop ebp
    ret

done:
    cli
    hlt
    
welcome: db "Welcome to SimpleBoot!, now we're running in 32 bit mode", 0x00
intro: db "A simple-ass bootloader", 0x00
text_properties: dw 0x0f00
screen_pointer: dd 0x00000000

times 510- ($-$$) db 0
dw 0xaa55