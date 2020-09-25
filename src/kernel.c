#define VGA_MAX_HEIGHT  200
#define VGA_MAX_WIDHT   320

#define VGA_ADDRESS_START 0xA0000

void vga_draw_pixels(unsigned short x, unsigned short y, unsigned short pixel )
{
    unsigned char * vga_mem = (unsigned char *)VGA_ADDRESS_START;
    unsigned short pos = x + y*VGA_MAX_WIDHT;
    vga_mem[pos] = pixel & 0xff;
}

void kentry()
{
    for(int y = 0; y < VGA_MAX_HEIGHT; y++)
        vga_draw_pixels(y, y, 10);
}