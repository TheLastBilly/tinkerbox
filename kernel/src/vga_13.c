#include <x86/vga/vga_13.h>
#include <string.h>

static vga_internals_t vga_internals_text =
{
    .cursor_x      = 0,
    .cursor_y      = 0,
    .screen_width   = VGA_13_SCREEN_COL,
    .screen_height  = VGA_13_SCREEN_ROW
};

static uint8_t screen_buffer[VGA_13_BUFFER_SIZE] = {0};

static uint8_t* vga_mem_ptr = (uint8_t *)VGA_13_ADDRESS_START;
static uint8_t* screen_buffer_ptr = screen_buffer;

void vga_13_draw_pixels(uint16_t x, uint16_t y, uint16_t pixel )
{
    uint16_t pos = x + y*vga_internals_text.screen_width;
    screen_buffer_ptr[pos] = pixel & 0xff;
}

void vga_13_draw_character(uint16_t p_x, uint16_t p_y, char c, uint16_t color)
{
    uint16_t pos = p_x + p_y*vga_internals_text.screen_width;

    if(c >= UTILS_ASCII_CHARACTER_START_INDEX)
        c -= UTILS_ASCII_CHARACTER_START_INDEX;

    for(int x = 0; x < UTILS_ASCII_CHAR_SIZE; x++)
    {
        uint8_t index = utils_ascii_96_char_map[c*UTILS_ASCII_CHAR_SIZE + x];
        for(int y = 0; y < UTILS_ASCII_CHAR_LENGHT; y++)
        {
            screen_buffer_ptr[pos + y*VGA_13_MAX_WIDHT + x] = ((index >> y) & UTILS_ASCII_TOP_PIXEL) ? color & 0xff : 0;
        }
    }
}

void vga_13_draw_string(const char * str, unsigned int size, uint16_t color)
{
    for(uint16_t i = 0; i < size; i++)
    {
        vga_13_draw_character(vga_internals_text.cursor_x*UTILS_ASCII_CHAR_SIZE, vga_internals_text.cursor_y*UTILS_ASCII_CHAR_SIZE, str[i], color);
        if(vga_internals_text.cursor_x < vga_internals_text.screen_width)
            vga_internals_text.cursor_x++;
        else
        {
            vga_internals_text.cursor_x = 0;
            vga_internals_text.cursor_y++;
        }
    }
}

void vga_13_swap_buffers()
{
    memcpy((void *)vga_mem_ptr, (void *)screen_buffer_ptr, VGA_13_BUFFER_SIZE);
}

uint16_t vga_13_get_text_cursor_x()
{
    return vga_internals_text.cursor_x/UTILS_ASCII_CHAR_SIZE;
}
uint16_t vga_13_get_text_cursor_y()
{
    return vga_internals_text.cursor_y/UTILS_ASCII_CHAR_SIZE;
}

void vga_13_set_text_cursor_x(uint16_t value)
{
    vga_internals_text.cursor_x = value * UTILS_ASCII_CHAR_SIZE;
}
void vga_13_set_text_cursor_y(uint16_t value)
{
    vga_internals_text.cursor_y = value * UTILS_ASCII_CHAR_SIZE;
}

void vga_13_new_line()
{
    if(vga_internals_text.cursor_y >= vga_internals_text.screen_height)
    {
        vga_13_scroll_up(1);
        vga_internals_text.cursor_y = vga_internals_text.screen_height - 1;
        vga_internals_text.cursor_x = 0;
    }
}

void vga_13_scroll_up(uint16_t lines)
{
    
}