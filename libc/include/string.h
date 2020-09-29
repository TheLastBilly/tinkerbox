#pragma once

#include <libc/include/stddef.h>

void * memcpy(void* src, void* dest, size_t size);
void * memset(void* ptr, int value, size_t size);
size_t strlen(const char* str);