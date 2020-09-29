#include <kernel/include/x86/vga/13/vga_13.h>
#include <kernel/include/x86/8042.h>
#include <kernel/include/kernel.h>

void kmain()
{   
    k_text_mode_print("I'm in");
    return;
}