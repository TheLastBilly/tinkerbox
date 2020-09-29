#pragma once

#include <kernel/include/x86/regs.h>

// Call an interrupt from real mode (implemented by Naplm)
void int32(uint8_t itr, regs16_s * regs);