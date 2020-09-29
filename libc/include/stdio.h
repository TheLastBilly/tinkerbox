#pragma once

#include <libc/include/stdarg.h>
#include <libc/include/stddef.h>

void vsnprintf(char * dest, size_t size, const char * fmt, va_list va);