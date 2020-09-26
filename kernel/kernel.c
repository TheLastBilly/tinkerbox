#include <x86/vga/vga_13.h>
#include <x86/8042.h>

#include <string.h>

void kentry()
{
    char str[9] = "I'm here!";
    memcpy(str, "sup", 3);
    vga_13_draw_string(str, 9, 15);
    vga_13_swap_buffers();
    
    uint8_t st = in_u8(0x64);
    char buff[2] = {0};
    buff[0] = st;
    if(st & 0x01)
    {
        vga_13_draw_string(buff, 2, 15);
    }
}