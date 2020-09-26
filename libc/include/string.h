#pragma once

#include <stdint.h>

typedef uint32_t size_t;

void * memcpy(void *src, void *dest, size_t size);
void * memset(void *ptr, uint8_t value, size_t size);