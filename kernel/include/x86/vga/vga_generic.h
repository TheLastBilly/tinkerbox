#pragma once

#include <libc/include/stdint.h>
#include "ascii.h"

typedef struct vga_internals_t
{
    uint16_t cursor_x;
    uint16_t cursor_y;
    uint16_t x;
    uint16_t y;

    const uint16_t screen_width;
    const uint16_t screen_height;
} vga_internals_t;