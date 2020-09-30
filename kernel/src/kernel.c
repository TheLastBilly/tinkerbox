#include <kernel/include/x86/vga/13/vga_13.h>
#include <kernel/include/x86/8042.h>
#include <kernel/include/kernel.h>

#include <kernel/include/x86/terminal.h>

#include <libc/include/string.h>
#include <libc/include/stdio.h>

char * intro = "Tinkerbox is on the way!\n";

void kmain()
{
    k_text_mode_print(intro);
    char buffer[10] = {0};
    itoa(1234, buffer, 10);
    k_text_mode_print(buffer);
    return;
}