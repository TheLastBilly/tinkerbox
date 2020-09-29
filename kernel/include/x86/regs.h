#pragma once

#include <libc/include/stdint.h>

typedef struct regs16_s {
    uint16_t di;
    uint16_t si;

    uint16_t bp;
    uint16_t sp;

    uint16_t bx;
    uint16_t dx;
    uint16_t cx;
    uint16_t ax;

    uint16_t gs;
    uint16_t fs;
    uint16_t es;
    uint16_t ds;

    uint16_t eflags;
} __attribute__ ((packed)) regs16_t;