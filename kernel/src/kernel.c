#include <x86/vga/vga_13.h>
#include <x86/8042.h>
#include <kernel.h>

static kernel_stdio_params_t kernel_stdio;

void kmain()
{   
    //Setup kstdio
    memset(kernel_stdio, 0, sizeof(kernel_stdio));

    kernel_stdio.refresh_callback = &vga_13_swap_buffers;
    kernel_stdio.new_line_ballback = &vga_13_new_line;
    kernel_stdio.putc_callback = &vga_13_putc;
    kernel_stdio.puts_callback = &vga_13_puts;
    kernel_stdio.move_cursor_callback = &vga_13_set_text_cursor;
    kernel_stdio.clear_screen_callback = &vga_13_clear_screen;

    kernel_stdio.get_max_height_callback = &vga_13_get_max_height;
    kernel_stdio.get_max_width_callback = &vga_13_get_max_width;
    kernel_stdio.get_max_cols_callback = &vga_13_get_max_cols;
    kernel_stdio.get_max_rows_callback = &vga_13_get_max_rows;

    k_system_set_stdio_params(&kernel_stdio);

    k_system_puts("Hello\t world!\n");
    k_system_puts("Hello\t world!\n");
    k_system_puts("Hello\t world!\n");
    k_system_puts("Hello\t world!\n");
}