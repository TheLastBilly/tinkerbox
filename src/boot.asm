bits 16
org 0x7c00

boot:
    mov si, welcome
    mov ah, 0x0e

printf:
    lodsb
    cmp al, 0
    je done
    int 0x10
    jmp printf

done:
    hlt
welcome: db "Welcome to SimpleBoot!"

times 510- ($-$$) db 0
dw 0xaa55