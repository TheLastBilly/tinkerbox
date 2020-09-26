#pragma once

#include <x86/vga/vga_generic.h>

void vga_13_draw_pixels(uint16_t x, uint16_t y, uint16_t pixel );
void vga_13_draw_character(uint16_t p_x, uint16_t p_y, uint8_t c, uint16_t color);
void vga_13_draw_string(const char * str, unsigned int size, uint16_t color);
void vga_13_new_line();

uint16_t vga_13_get_13_cursor_x();
uint16_t vga_13_get_13_cursor_y();

void vga_13_set_13_cursor_x(uint16_t value);
void vga_13_set_13_cursor_y(uint16_t value);