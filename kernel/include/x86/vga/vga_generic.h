#pragma once

#include <stdint.h>
#include <x86/vga/ascii.h>

typedef struct vga_internals_t
{
    uint16_t cursor_x;
    uint16_t cursor_y;

    const uint16_t screen_width;
    const uint16_t screen_height;
} vga_internals_t;