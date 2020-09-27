#include <kstdio.h>
#include <stddef.h>
#include <stdbool.h>

#include <string.h>

static struct 
{
    int max_height;
    int max_width;

    int max_cols;
    int max_rows;

    bool params_init;
    kernel_stdio_params_t params;
} kstdio_internals;

void k_system_set_stdio_params(kernel_stdio_params_t* params)
{
    kstdio_internals.params_init = true;
    memcpy(&kstdio_internals.params, params, sizeof(kernel_stdio_params_t));
}

void k_system_putc(char c)
{
    if(
        kstdio_internals.params_init && 
        kstdio_internals.params.putc_callback != NULL &&
        kstdio_internals.params.refresh_callback != NULL
    )
    {
        switch (c)
        {
        case '\n':
            (*kstdio_internals.params.new_line_ballback)();
            break;
        case '\t':
            for(size_t i = 0; i < KSTDIO_TAB_SIZE; i++)
                (*kstdio_internals.params.putc_callback)(' ');
            break;
        default:
            (*kstdio_internals.params.putc_callback)(c);
            break;
        }

        (*kstdio_internals.params.refresh_callback)();
    }
}

void k_system_puts(const char * str)
{
    size_t s = strlen(str);
    for(size_t i = 0; i < s; i++)
        k_system_putc(str[i]);
}