#define VIDEO_BUFFER_POINTER 0xb8000

extern void entry()
{
    const char * test = "This is a test from real mode!";
    unsigned char * vga = (unsigned char *)VIDEO_BUFFER_POINTER;
    for(int i = 0; i < 31; i++)
        vga[i] = test[i] | 0x0f00;        
}