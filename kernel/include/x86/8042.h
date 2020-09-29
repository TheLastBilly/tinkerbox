#pragma once

#include <kernel/include/x86/io.h>
#include <libc/include/stdint.h>

void i8042_send_cmd(uint8_t cmd);
