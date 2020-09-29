#pragma once

#include <kernel/include/x86/vga/vesa/vesa.h>

typedef struct k_kernel_params
{
    vesa_bios_info_t vesa_bios_info;
}__attribute__ ((packed)) k_kernel_params;

void k_load_kernel_params(k_kernel_params * params);