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
    
    ;Print our beloved welcome message
    push welcome
    call print
    call new_line

    push welcome
    call print

    jmp done

; Print a character to VGA
print:
    push ebp
    mov ebp, esp
    push esi
    push ecx
    
    ; Get the string to print and put it on esi
    mov esi, [ebp+8]

.loop:
    ; Shift string to the right
    lodsb
    cmp al, 0 ; Is it the end of the string?
    je print_end ; If so, skip to the end of the function

    ; Apply text properties to text 
    mov cx, word [text_properties]
    or ax, cx

    ; Move character to buffer, and increment buffer by one chacter (2 bytes)
    mov ecx, [screen_pointer]
    mov [ecx], ax
    add dword [screen_pointer], 2

    jmp .loop

print_end:
    pop ecx
    pop esi
    mov esp, ebp
    pop ebp
    ret

; Makes a new line for the terminal
new_line:
    push ebp
    mov ebp, esp

    push edx ; Stores the amount of characters left to for the line
    push eax
    push ebx

    ; Gets the characters remaining in the line
    mov eax, [screen_pointer]
    sub eax, screen_base_pointer
    mov edx, 0
    mov ebx, 2
    div ebx
    
    mov edx, 0
    mov ebx, 80
    div ebx
    
    sub ebx, edx
    mov edx, ebx
    
    ; Put ' ' character in ax
    mov ax, 0x0061

.loop:
    ; Check if there's more character to add
    cmp edx, 0
    je new_line_end
    
    ; Add space character to buffer
    mov ecx, [screen_pointer]
    mov [ecx], ax
    add dword [screen_pointer], 2

    ; Decrement counter
    sub edx, 1
    jmp .loop

new_line_end:    
    pop ebx
    pop eax
    pop edx

    mov esp, ebp
    pop ebp
    ret
    
done:
    cli
.loop:
    nop
    nop
    jmp .loop

welcome: db "I made a bootloader bitch!, I even made some functions in assembler!", 0x00
intro: db "A simple-ass bootloader", 0x00
text_properties: dw 0x0f00
screen_base_pointer equ 0xb8000
screen_pointer: dd screen_base_pointer

times 510- ($-$$) db 0
dw 0xaa55