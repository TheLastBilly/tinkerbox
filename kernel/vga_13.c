#include <x86/include/vga_13.h>

static vga_internals_t vga_internals =
{
    .cursor_x      = 0,
    .cursor_y      = 0,
    .screen_width   = VGA_13_MAX_WIDHT,
    .screen_height  = VGA_13_MAX_HEIGHT
};

static uint8_t* vga_mem_ptr = (uint8_t *)VGA_13_ADDRESS_START;

void vga_13_draw_pixels(uint16_t x, uint16_t y, uint16_t pixel )
{
    uint16_t pos = x + y*vga_internals.screen_width;
    vga_mem_ptr[pos] = pixel & 0xff;
}

void vga_13_draw_character(uint16_t p_x, uint16_t p_y, uint8_t c, uint16_t color)
{
    uint8_t * vga_mem = (uint8_t *)VGA_13_ADDRESS_START;
    uint16_t pos = p_x + p_y*vga_internals.screen_width;

    if(c > UTILS_ASCII_CHARACTER_START_INDEX)
        c -= UTILS_ASCII_CHARACTER_START_INDEX;

    uint8_t index = utils_ascii_96_char_map[c*UTILS_ASCII_CHAR_SIZE];
    for(int x = 1; x < UTILS_ASCII_CHAR_SIZE+1; x++)
    {
        for(int y = 0; y < UTILS_ASCII_CHAR_SIZE+1; y++)
        {
            vga_mem[pos + y*VGA_13_MAX_WIDHT + x] = ((index >> y) & UTILS_ASCII_TOP_PIXEL) ? color & 0xff : 0;
        }
        index = utils_ascii_96_char_map[c*UTILS_ASCII_CHAR_SIZE + x];
    }
}

void vga_13_draw_string(const char * str, unsigned int size, uint16_t color)
{
    for(uint16_t i = 0; i < size; i++)
    {
        vga_13_draw_character(vga_internals.cursor_x*UTILS_ASCII_CHAR_SIZE, vga_internals.cursor_y*UTILS_ASCII_CHAR_SIZE, str[i], color);
        if(vga_internals.cursor_x < VGA_13_SCREEN_COL)
            vga_internals.cursor_x++;
        else
        {
            vga_internals.cursor_x = 0;
            vga_internals.cursor_y++;
        }
    }
}

uint16_t vga_13_get_text_cursor_x()
{
    return vga_internals.cursor_x/UTILS_ASCII_CHAR_SIZE;
}
uint16_t vga_13_get_text_cursor_y()
{
    return vga_internals.cursor_y/UTILS_ASCII_CHAR_SIZE;
}

void vga_13_set_text_cursor_x(uint16_t value)
{
    vga_internals.cursor_x = value * UTILS_ASCII_CHAR_SIZE;
}
void vga_13_set_text_cursor_y(uint16_t value)
{
    vga_internals.cursor_y = value * UTILS_ASCII_CHAR_SIZE;
}