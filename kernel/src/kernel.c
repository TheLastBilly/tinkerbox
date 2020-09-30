#include <kernel/include/x86/vga/13/vga_13.h>
#include <kernel/include/x86/8042.h>
#include <kernel/include/kernel.h>

#include <kernel/include/x86/terminal.h>

#include <libc/include/string.h>

char test[16] = "This is aXtest";

void kmain()
{   
    const char * n_test = " trst";
    memcpy(&test[9], n_test, 5);
    k_text_mode_print(test);
    k_text_mode_new_line();
    return;
}