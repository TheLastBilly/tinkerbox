bits 32

global out_u8
out_u8:
    push edx 

    mov al, byte [ebp+7]
    mov dx, word [ebp+6]
    out dx, al

    pop edx
    ret

global out_u16
out_u16:
    push edx

    mov ax, word [ebp+8]
    mov dx, word [ebp+6]
    out dx, ax
 
    pop edx
    ret

global out_u32
out_u32:
    push edx

    mov eax, dword [ebp+10]
    mov dx, word [ebp+6]
    out dx, eax

    pop edx
    ret

global in_u8
in_u8:
    push edx

    mov dx, word [esp+6]
    in al, dx

    pop edx
    ret

global in_u16
in_u16:
    push edx

    mov dx, word [esp+6]
    in ax, dx

    pop edx
    ret

global in_u32
in_u32:
    push edx

    mov dx, word [esp+6]
    in eax, dx

    pop edx
    ret