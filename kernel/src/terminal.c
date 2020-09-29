#include <kernel/include/terminal.h>

static int current_col = 0;
static int current_row = 0;

static uint16_t* screen_video_ptr = KERNEL_TEXT_BUFFER_ADDR;

void k_text_mode_print(const char* str)
{
    size_t size = strlen(str);
    for(int i = 0; i < size; i++)
    {
        if(current_col > KERNEL_TEXT_COLS)
        {
            current_col = 0;
            current_row ++;
        }

        if(current_row > KERNEL_TEXT_ROWS)
        {
            memcpy(
                &screen_video_ptr[KERNEL_TEXT_COLS], 
                screen_video_ptr, 
                ((KERNEL_TEXT_COLS-1)*KERNEL_TEXT_ROWS)*2
            );
            memset(
                &screen_video_ptr[(KERNEL_TEXT_COLS-2)*KERNEL_TEXT_ROWS],
                0,
                KERNEL_TEXT_COLS*2
            );
        }

        screen_video_ptr[i] = KERNEL_TEXT_ATTRIBUTE | str[i];
        current_row++;
    }
}