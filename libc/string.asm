bits 32
global memcpy
memcpy:
    push ebp
    mov ebp,esp
    push ax
    push ecx

    mov esi, dword [ebp+12]     ; Save the source into esi
    mov edi, dword [ebp+8]      ; Save the dest into ebx
    mov ecx, dword [ebp+16]     ; Save the size into ecx

.loop:
    mov al, byte [esi]              ; Get value to move
    mov byte [edi], al              ; Move value to next dest
    add esi, 1                  ; Increment
    add edi, 1

    sub ecx, 1
    cmp ecx, 0
    jne .loop

memcpy.done:

    mov ecx, [ebp+8]
    mov dword [ebp-4], ecx

    pop ecx
    pop ax
    pop ebp
    ret

global memset
memset:
    push ebp
    mov ebp,esp


    pop ebp
    ret