#include <kernel/include/x86/vga/13/vga_13.h>
#include <kernel/include/x86/8042.h>
#include <kernel/include/kernel.h>

#include <kernel/include/x86/terminal.h>

#include <libc/include/string.h>
#include <libc/include/stdio.h>

void kmain()
{
    char dest[17] = "this is ";
    char src[6] = "a test";
    strncat(dest, src, 6);
    k_text_mode_print(dest);
    return;
}