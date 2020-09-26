#!/bin/bash

nasm -f elf32 boot.asm -o boot.o
gcc -c -ggdb3 -m32 -ffreestanding -fno-PIE -mno-red-zone -fno-exceptions -nostartfiles -O0 -nostdlib -o kernel.o -std=c99 kernel.c 
gcc -c -ggdb3 -m32 -ffreestanding -fno-PIE -mno-red-zone -fno-exceptions -nostartfiles -O0 -nostdlib -o chars.o -std=c99 chars.c 
ld -m elf_i386 -o boot.elf -T boot.ld boot.o kernel.o chars.o
objcopy -O binary boot.elf boot.bin