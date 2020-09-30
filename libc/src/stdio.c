#include <libc/include/stdio.h>

#include <libc/include/string.h>

char * itoa(int value, char * str, int base)
{

}

void vsnprintf(char * dest, size_t size, const char * fmt, va_list va)
{
    size_t dest_count = 0;
    short ii = 0;
    for(size_t i = 0; fmt[i] != '\0'; i++)
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