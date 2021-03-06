#pragma once

#include <libc/include/stdint.h>

void out_u8(uint16_t port, uint8_t byte);
void out_u16(uint16_t port, uint16_t word);
void out_u32(uint16_t port, uint32_t lword);

uint8_t in_u8(uint16_t port);
uint16_t in_u16(uint16_t port);
uint32_t in_u32(uint16_t port);