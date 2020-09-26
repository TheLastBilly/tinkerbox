#pragma once

#include <x86/vga/vga_generic.h>

#define VGA_13_ADDRESS_START 0xA0000

#define VGA_13_MAX_HEIGHT  200
#define VGA_13_MAX_WIDHT   320

#define VGA_13_BUFFER_SIZE VGA_13_MAX_HEIGHT*VGA_13_MAX_WIDHT

#define VGA_13_SCREEN_COL VGA_13_MAX_WIDHT/UTILS_ASCII_CHAR_WIDTH
#define VGA_13_SCREEN_ROW VGA_13_MAX_HEIGHT/UTILS_ASCII_CHAR_LENGHT

void vga_13_draw_pixels(uint16_t x, uint16_t y, uint16_t pixel );
void vga_13_draw_character(uint16_t p_x, uint16_t p_y, char c, uint16_t color);
void vga_13_draw_string(const char * str, unsigned int size, uint16_t color);
void vga_13_new_line();
void vga_13_scroll_up(uint16_t lines);

void vga_13_swap_buffers();

uint16_t vga_13_get_13_cursor_x();
uint16_t vga_13_get_13_cursor_y();
void vga_13_set_13_cursor_x(uint16_t value);
void vga_13_set_13_cursor_y(uint16_t value);