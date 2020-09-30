#include <kernel/include/x86/terminal.h>

static int current_col = 0;
static int current_row = 0;

static uint16_t* screen_video_ptr = (uint16_t*)KERNEL_TEXT_BUFFER_ADDR;

void k_text_mode_print(const char* str)
{
    size_t size = strlen(str);
    for(int i = 0; i < size; i++)
    {
        if(current_col > KERNEL_TEXT_COLS)
            k_text_mode_new_line();

        if(str[i] == '\n')
        {
            k_text_mode_new_line();
            continue;
        }

        screen_video_ptr[current_col + current_row*KERNEL_TEXT_COLS] = KERNEL_TEXT_ATTRIBUTE | str[i];
        current_col++;
    }
}

void k_text_mode_new_line()
{
    current_row++;
    current_col=0;

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
}