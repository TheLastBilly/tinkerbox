#include <x86/vga/vga_13.h>
#include <x86/8042.h>

void kentry()
{
    vga_13_draw_string("I'm here!", 9, 15);
    uint8_t st = in_u8(0x64);
    char buff[2] = {0};
    buff[0] = st;
    if(st & 0x01)
    {
        vga_13_draw_string(buff, 2, 15);
    }
}