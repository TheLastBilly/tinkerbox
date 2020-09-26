#include <x86/include/vga_13.h>

void kentry()
{
    const char * str = "Hello World!";
    vga_13_draw_string(str, 14, 15);
}