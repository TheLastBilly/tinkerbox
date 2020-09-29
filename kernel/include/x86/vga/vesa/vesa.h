#pragma once

#include <libc/include/stdint.h>

//Taken from https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
typedef struct vesa_bios_info_t
{
    char signature[4];
    uint16_t version;			
	uint32_t oem;			

	uint32_t capabilities;		
	uint32_t video_modes;		
	uint16_t video_memory;		
	
    uint16_t software_rev;		
	uint32_t vendor;			
	uint32_t product_name;		
	uint32_t product_rev;		
	
    char reserved[222];		
	char oem_data[256];		
}__attribute__ ((packed)) vesa_bios_info_t;