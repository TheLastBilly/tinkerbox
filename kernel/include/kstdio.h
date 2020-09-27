#pragma once

#include <kdef.h>

#define KSTDIO_TAB_SIZE 4

typedef struct kernel_stdio_params_t
{
    //Screen controls
    k_void_callback_t               refresh_callback;
    k_void_callback_t               new_line_ballback;
    k_void_callback_t               clear_screen_callback;
    k_void_char_callback_t          putc_callback;
    k_void_string_size_callback_t   puts_callback;
    k_void_int_int_callback_t       move_cursor_callback;

    //Data
    k_int_void_callback_t           get_cursor_row_callback;
    k_int_void_callback_t           get_cursor_column_callback;
    k_int_void_callback_t           get_max_height_callback;
    k_int_void_callback_t           get_max_width_callback;
    k_int_void_callback_t           get_max_cols_callback;
    k_int_void_callback_t           get_max_rows_callback;

} kernel_stdio_params_t;

void k_system_set_stdio_params(kernel_stdio_params_t* params);

void k_system_putc(char c);
void k_system_puts(const char* str);