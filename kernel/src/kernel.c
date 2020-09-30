#include <kernel/include/x86/vga/13/vga_13.h>
#include <kernel/include/x86/8042.h>
#include <kernel/include/kernel.h>

#include <kernel/include/x86/terminal.h>

#include <libc/include/string.h>

const char * test = "This is a Xtest";

void kmain()
{   
    k_text_mode_print("Testing memchr\n");
    char * ptr = (char *)memchr(test, 'Y', 16);
    if(ptr == NULL)
        k_text_mode_print("not found");
    else
        k_text_mode_print("found");
    return;
}