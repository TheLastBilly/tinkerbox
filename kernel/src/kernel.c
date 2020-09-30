#include <kernel/include/x86/vga/13/vga_13.h>
#include <kernel/include/x86/8042.h>
#include <kernel/include/kernel.h>

#include <kernel/include/x86/terminal.h>

#include <libc/include/string.h>

char * intro = "Tinkerbox is on the way!";

void kmain()
{
    k_text_mode_print(intro);
    return;
}