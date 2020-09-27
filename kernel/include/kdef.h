#pragma once

#include <stddef.h>

typedef void (*k_void_callback_t)(void);
typedef void (*k_void_char_callback_t)(char);
typedef void (*k_void_string_size_callback_t)(const char *, size_t);
typedef void (*k_void_int_int_callback_t)(int, int);
typedef int (*k_int_void_callback_t)(void);