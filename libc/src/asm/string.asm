bits 32

global memcpy
memcpy:
    push ebp
    mov ebp,esp
    push ax
    push esi
    push edi

    mov esi, dword [ebp+12]     ; Save the source into esi
    mov edi, dword [ebp+8]      ; Save the dest into edi
    mov ecx, dword [ebp+16]     ; Save the size into ecx

.loop:
    mov al, byte [esi]              ; Get value to move
    mov byte [edi], al              ; Move value to next dest
    add esi, 1                  ; Increment
    add edi, 1

    sub ecx, 1
    cmp ecx, 0
    jne .loop

    mov ecx, [ebp+8]
    mov dword [ebp-4], ecx

    pop edi
    pop esi
    pop ax
    mov esp, ebp
    pop ebp
    ret


; Taken from https://stackoverflow.com/a/20340917/8620560
global memset
memset:
    push edi

    mov ecx, [esp+16] ; Get the size
    mov al,  [esp+12] ; Get the value
    mov edi, [esp+8]  ; Get the ptr
    rep stosb         ; Repeat until ecx is 0
    
    mov eax, [esp+8]

    pop edi
    ret

global strlen
strlen:
    push edi
    
    mov edi, dword [esp+8]
    mov ecx, 0x00

.loop:
    add edi, 1
    add ecx, 1
    cmp [edi], byte 0
    jne .loop

    mov eax, ecx

    pop edi
    ret