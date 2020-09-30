#pragma once

#include <libc/include/stdarg.h>
#include <libc/include/stddef.h>

char * itoa(int value, char *str, int base);
void vsnprintf(char * dest, size_t size, const char * fmt, va_list va);