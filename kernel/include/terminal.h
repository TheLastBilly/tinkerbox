#pragma once

#include <libc/include/string.h>
#include <libc/include/stdint.h>

#define KERNEL_TEXT_COLS        80
#define KERNEL_TEXT_ROWS        25
#define KERNEL_TEXT_BUFFER_ADDR 0xB8000
#define KERNEL_TEXT_ATTRIBUTE   0x0f00

void k_text_mode_print(const char * str);