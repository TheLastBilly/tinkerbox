#include <libc/include/stdio.h>

static int find_next_char(const char * str, size_t size, char c);

void vsnprintf(char * dest, size_t size, const char * fmt, va_list va)
{
    for(size_t i = 0; i < size || fmt[i] != '\0'; i++)
    {
        if(fmt[i] == '%' && i < size -2)
        {
            char command = fmt[i+1];
            switch (command)
            {
            case 'd':
                
                break;
            
            default:
                break;
            }
        }   
    }
}