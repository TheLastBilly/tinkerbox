bits 32

global memcpy
memcpy:
    push ebp
    mov ebp,esp
    push ecx
    push esi
    push edi

    mov edi, dword [ebp+8]      ; Save the dest into edi
    mov esi, dword [ebp+12]     ; Save the source into esi
    mov ecx, dword [ebp+16]     ; Save the size into ecx

    rep movsb

    mov eax, dword [ebp+8]

    pop edi
    pop esi
    pop ecx
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

global memchr
memchr:
    push ebp
    mov ebp,esp
    push ecx
    push edi

    mov edi, [ebp + 8] ;Get source

    mov al, byte [ebp + 12] ;Get the character
    mov ecx, [ebp + 16]  ;Get the size

    ; Check if the size is over
    cmp ecx, dword 0x00
    je memchr.end.nomatch

    ; Check if the character was found    
    cld
    repne scasb
    ;Jump to the end if you found it
    je memchr.end.match

    ; Set return value to null if nothing was found
memchr.end.nomatch:
    mov eax, 0x00
    jmp memchr.end

memchr.end.match:
    dec edi
    mov eax, edi

memchr.end:

    pop edi
    pop ecx
    mov esp, ebp
    pop ebp
    ret

global strrev
strrev:
    push ebp
    mov ebp,esp
    push ecx    ; Stores the string's last character
    push edi    ; Saves the string pointer
    push ebx    ; Used for moving operations
                ; eax: Saves the current character to copy 

    mov edi, [ebp+8] ; Save string pointer to edi

    ; Get the string length and save its last character's pointer into ecx
    push edi
    call strlen
    pop edi

    mov ecx, edi
    add ecx, eax
    sub ecx, 1

.loop:
    ;Check if edi is bigger than ecx
    cmp ecx, edi
    js strrev.end

    ; Swap current ecx and edi
    mov al, byte [edi]
    mov bl, byte [ecx]
    mov byte [edi], bl
    mov byte [ecx], al

    dec ecx
    inc edi

    jmp .loop

strrev.end:

    pop ebx
    pop edi
    pop ecx
    mov esp, ebp
    pop ebp
    ret

global strncat
strncat:
    push ebp
    mov ebp,esp
    push ecx
    push esi
    push edi

    mov edi, dword [ebp+8]      ; Save the dest into edi
    mov esi, dword [ebp+12]     ; Save the source into esi
    mov ecx, dword [ebp+16]     ; Save the size into ecx

    push edi
    call strlen
    pop edi
    
    add edi, eax

    rep movsb

    mov eax, dword [ebp+8]

    pop edi
    pop esi
    pop ecx
    mov esp, ebp
    pop ebp
    ret