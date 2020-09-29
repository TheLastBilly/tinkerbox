#pragma once

#include <kernel/include/x86/vga/vga_generic.h>

#define VGA_13_ADDRESS_START 0xA0000

#define VGA_13_MAX_WIDTH   320
#define VGA_13_MAX_HEIGHT  200

#define VGA_13_TEXT_DEFAULT_COLOR 15
#define VGA_13_TEXT_LINE_SEPARATION 2

#define VGA_13_BUFFER_SIZE VGA_13_MAX_HEIGHT*VGA_13_MAX_WIDTH

#define VGA_13_SCREEN_COL VGA_13_MAX_WIDTH/VGA_13_ASCII_CHAR_WIDTH
#define VGA_13_SCREEN_ROW VGA_13_MAX_HEIGHT/VGA_13_ASCII_CHAR_LENGHT

void vga_13_draw_pixels(uint16_t x, uint16_t y, uint16_t pixel );
void vga_13_draw_character(uint16_t p_x, uint16_t p_y, char c, uint16_t color);
void vga_13_puts(const char * str, unsigned int size);
void vga_13_putc(char c);
void vga_13_new_line();
void vga_13_scroll_up(uint16_t lines);
void vga_13_clear_screen();

void vga_13_swap_buffers();

uint16_t vga_13_get_max_height();
uint16_t vga_13_get_max_width();

uint16_t vga_13_get_max_cols();
uint16_t vga_13_get_max_rows();

uint16_t vga_13_get_cursor_column();
uint16_t vga_13_get_cursor_row();

void vga_13_set_text_cursor(uint16_t c, uint16_t r);