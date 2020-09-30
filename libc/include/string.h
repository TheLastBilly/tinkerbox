#pragma once

#include <libc/include/stddef.h>

void * memcpy(void* dest, void* src, size_t size);
void * memset(void* ptr, int value, size_t size);
void * memchr(const void * src, int c, size_t size);
size_t strlen(const char* str);