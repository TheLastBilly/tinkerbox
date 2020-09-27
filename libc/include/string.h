#pragma once

#include <stdint.h>

typedef uint32_t size_t;

void * memcpy(void *src, void *dest, size_t size);
void * memset(void *ptr, int value, size_t size);