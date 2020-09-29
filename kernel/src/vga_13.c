#include <kernel/include/x86/vga/13/vga_13.h>
#include <libc/include/string.h>

static vga_internals_t vga_internals =
{
    .cursor_x       = 0,
    .cursor_y       = 0,
    .x              = 0,
    .y              = 0,
    .screen_width   = VGA_13_SCREEN_COL,
    .screen_height  = VGA_13_SCREEN_ROW
};

static uint8_t screen_buffer[VGA_13_BUFFER_SIZE] = {0};

static uint8_t* vga_mem_ptr = (uint8_t *)VGA_13_ADDRESS_START;
static uint8_t* screen_buffer_ptr = screen_buffer;

void vga_13_draw_pixels(uint16_t x, uint16_t y, uint16_t pixel )
{
    uint16_t pos = x + y*vga_internals.screen_width;
    screen_buffer_ptr[pos] = pixel & 0xff;
}

void vga_13_draw_character(uint16_t p_x, uint16_t p_y, char c, uint16_t color)
{
    uint16_t pos = p_x + p_y*VGA_13_MAX_WIDTH;

    if(c >= VGA_13_ASCII_CHARACTER_START_INDEX)
        c -= VGA_13_ASCII_CHARACTER_START_INDEX;

    for(int x = 0; x < VGA_13_ASCII_CHAR_SIZE; x++)
    {
        uint8_t index = VGA_13_ASCII_96_char_map[c*VGA_13_ASCII_CHAR_SIZE + x];
        for(int y = 0; y < VGA_13_ASCII_CHAR_LENGHT; y++)
        {
            screen_buffer_ptr[pos + y*VGA_13_MAX_WIDTH + x] = ((index >> y) & VGA_13_ASCII_TOP_PIXEL) ? color & 0xff : 0;
        }
    }
}

void vga_13_puts(const char * str, unsigned int size)
{
    for(uint16_t i = 0; i < size; i++)
    {
        vga_13_putc(str[i]);
    }
}

void vga_13_putc(char c)
{
    vga_13_draw_character(
        vga_internals.cursor_x * VGA_13_ASCII_CHAR_SIZE, 
        vga_internals.cursor_y * VGA_13_ASCII_CHAR_LENGHT + vga_internals.y, 
        c, 
        VGA_13_TEXT_DEFAULT_COLOR
    );
    
    if(vga_internals.cursor_x < vga_internals.screen_width)
        vga_internals.cursor_x++;
    else
    {
        vga_internals.cursor_x = 0;
        vga_13_new_line();
    }
}

void vga_13_swap_buffers()
{
    memcpy((void *)vga_mem_ptr, (void *)screen_buffer_ptr, VGA_13_BUFFER_SIZE);
}

uint16_t vga_13_get_max_height()
{
    return VGA_13_MAX_HEIGHT;
}

uint16_t vga_13_get_max_width()
{
    return VGA_13_MAX_WIDTH;
}

uint16_t vga_13_get_max_cols()
{
    return VGA_13_SCREEN_COL;
}

uint16_t vga_13_get_max_rows()
{
    return VGA_13_SCREEN_ROW;
}

uint16_t vga_13_get_cursor_row()
{
    return vga_internals.cursor_x/VGA_13_ASCII_CHAR_SIZE;
}
uint16_t vga_13_get_cursor_column()
{
    return vga_internals.cursor_y/VGA_13_ASCII_CHAR_SIZE;
}

void vga_13_set_text_cursor(uint16_t c, uint16_t r)
{
    vga_internals.cursor_x = c;
    vga_internals.cursor_y = r;
}

void vga_13_new_line()
{
    if(vga_internals.cursor_y >= VGA_13_SCREEN_ROW)
    {
        vga_13_scroll_up(VGA_13_ASCII_CHAR_LENGHT);
        return;
    }

    vga_internals.cursor_y++;
    vga_internals.cursor_x = 0;

    vga_internals.y += VGA_13_TEXT_LINE_SEPARATION;
}

void vga_13_scroll_up(uint16_t lines)
{
    vga_internals.cursor_y--;
    vga_internals.y--;
    memcpy(screen_buffer_ptr, &screen_buffer_ptr[lines*VGA_13_MAX_WIDTH], VGA_13_BUFFER_SIZE - lines * VGA_13_MAX_WIDTH);
}

void vga_13_clear_screen()
{
    memset(screen_buffer_ptr, 0, VGA_13_BUFFER_SIZE);
    vga_internals.cursor_x = vga_internals.cursor_y = 0;

    vga_internals.y = 0;
}