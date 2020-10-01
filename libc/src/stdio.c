#include <libc/include/stdio.h>

#include <libc/include/string.h>
#include <libc/include/stdbool.h>

static int nitoa(int value, char * str, int base, size_t size)
{
    bool is_n = false;
    if(value < 0)
    {
        value *= -1;
        is_n = true;
    }

    if(base < 0)
        base *= -1;

    if(base > 16)
        return NULL;

    size_t counter = 0;    
    do
    {
        char c = value % base;
        str[counter++] = c > 9 ? c + 87 : c + 48;
    }while((value /= base) > 0 && counter < size);

    if(is_n)
        str[counter++] = '-';
    
    strrev(str);

    return counter;
}

char * itoa(int value, char * str, int base)
{
    nitoa(value, str, base, 50);
    return str;
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
            int tmp = 0;

            switch (command)
            {
            case 'd':
                tmp = va_arg(va, int);
                dest_count += nitoa(tmp, &dest[dest_count], 10, size-dest_count);
                break;

            case 'x':
                tmp = va_arg(va, int);
                dest_count += nitoa(tmp, &dest[dest_count], 16, size-dest_count);
                break;
            
            case 'c':
                if(dest_count < size)
                {
                    tmp = (int)va_arg(va, char);
                    dest[dest_count] = (char)tmp;
                }
                break;
            
            case 's':
                
                break;
                
            default:
                break;
            }
        }   
    }
}