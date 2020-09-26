#define VGA_MAX_HEIGHT  200
#define VGA_MAX_WIDHT   320

#define VGA_ADDRESS_START 0xA0000

#include "utils/ascii.h"

#define VGA_SCREEN_COL VGA_MAX_WIDHT/ASCII_CHAR_SIZE
#define VGA_SCREEN_ROW VGA_MAX_HEIGHT/ASCII_CHAR_SIZE

unsigned short screen_pointer_x = 0;
unsigned short screen_pointer_y = 0;

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

    if(c > ASCII_CHARACTER_START_INDEX)
        c -= ASCII_CHARACTER_START_INDEX;

    unsigned char index = ascii_96_char_map[c*ASCII_CHAR_SIZE];
    for(int x = 1; x < ASCII_CHAR_SIZE+1; x++)
    {
        for(int y = 0; y < ASCII_CHAR_SIZE+1; y++)
        {
            vga_mem[pos + y*VGA_MAX_WIDHT + x] = ((index >> y) & ASCII_TOP_PIXEL) ? color & 0xff : 0;
        }
        index = ascii_96_char_map[c*ASCII_CHAR_SIZE + x];
    }
}

void vga_draw_string(const char * str, unsigned int size, unsigned short color)
{
    for(unsigned short i = 0; i < size; i++)
    {
        vga_draw_character(screen_pointer_x*ASCII_CHAR_SIZE, screen_pointer_y*ASCII_CHAR_SIZE, str[i], color);
        if(screen_pointer_x < VGA_SCREEN_COL)
            screen_pointer_x++;
        else
        {
            screen_pointer_x = 0;
            screen_pointer_y++;
        }
    }
}

void kentry()
{
    const char * str = "Hello_World!_";
    vga_draw_string(str, 14, 15);
    vga_draw_string(str, 14, 15);
}