#pragma once

#include <libc/include/stddef.h>

typedef void* va_list;

#define va_start(args, last)    args = &last + 1
#define va_arg(args, type)      *((type*) args); args+=sizeof(type)
#define va_end(args)            args = NULL