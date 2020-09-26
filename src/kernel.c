#define VGA_MAX_HEIGHT  320
#define VGA_MAX_WIDHT   200

#define VGA_ADDRESS_START 0xA0000

#include "ascii.h"

void vga_draw_pixels(unsigned short x, unsigned short y, unsigned short pixel )
{
    unsigned char * vga_mem = (unsigned char *)VGA_ADDRESS_START;
    unsigned short pos = x + y*VGA_MAX_WIDHT;
    vga_mem[pos] = pixel & 0xff;
}

void vga_draw_character(unsigned short p_x, unsigned short p_y, unsigned char c, unsigned short color)
{
    unsigned char * vga_mem = (unsigned char *)VGA_ADDRESS_START;
    unsigned short pos = p_x + p_y*VGA_MAX_WIDHT;

    unsigned char index = ascii_256_char_map[c*ASCII_CHAR_SIZE];
    for(unsigned short y = 0; y < ASCII_CHAR_SIZE; y++)
    {
        for(unsigned short x = 0; x < ASCII_CHAR_SIZE; x++)
        {
            vga_mem[pos + x + y*VGA_MAX_WIDHT] = ((index >> x) & 0x7) ? (color & 0xff) : 0x0;
        }
        index = ascii_256_char_map[c*ASCII_CHAR_SIZE + y];
    }
}

void kentry()
{
    for(int x = 0; x < VGA_MAX_WIDHT; x++)
        vga_draw_character(x*16, 0, 33, 10);
}