bits 32

global out_u8
out_u8:
    push ebp
    mov ebp,esp
    push ax
    push dx

    mov al, byte [ebp+7]
    mov dx, word [ebp+6]
    out dx, al

    pop dx
    pop ax
    pop ebp
    ret

global out_u16
out_u16:
    push ebp
    mov ebp,esp
    push ax
    push dx

    mov ax, word [ebp+7]
    mov dx, word [ebp+6]
    out dx, ax
 
    pop dx
    pop ax   
    pop ebp
    ret

global out_u32
out_u32:
    push ebp
    mov ebp,esp
    push eax
    push dx

    mov eax, dword [ebp+7]
    mov dx, word [ebp+6]
    out dx, eax

    pop dx
    pop eax    
    pop ebp
    ret

global in_u8
in_u8:
    push ebp
    mov ebp,esp
    push ax
    push dx

    mov dx, word [esp+6]
    in al, dx
    mov byte [ebp-1], al

    pop dx
    pop ax    
    pop ebp
    ret

global in_u16
in_u16:
    push ebp
    mov ebp,esp
    push ax
    push dx

    mov dx, word [esp+6]
    in ax, dx
    mov word [ebp-2], ax

    pop dx
    pop ax    
    pop ebp
    ret

global in_u32
in_u32:
    push ebp
    mov ebp,esp
    push eax
    push dx

    mov dx, word [esp+6]
    in eax, dx
    mov word [ebp-4], ax

    pop dx
    pop eax    
    pop ebp
    ret