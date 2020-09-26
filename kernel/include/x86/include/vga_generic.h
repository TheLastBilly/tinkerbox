#pragma once

#include <stdint.h>
#include <utils/ascii.h>

#define VGA_13_ADDRESS_START 0xA0000

#define VGA_13_MAX_HEIGHT  200
#define VGA_13_MAX_WIDHT   320

#define VGA_13_SCREEN_COL VGA_13_MAX_WIDHT/UTILS_ASCII_CHAR_SIZE
#define VGA_13_SCREEN_ROW VGA_13_MAX_HEIGHT/UTILS_ASCII_CHAR_SIZE

typedef struct vga_internals_t
{
    uint16_t cursor_x;
    uint16_t cursor_y;

    const uint16_t screen_width;
    const uint16_t screen_height;
} vga_internals_t;