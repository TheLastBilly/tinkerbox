#pragma once

#include <x86/io.h>
#include <stdint.h>

void i8042_send_cmd(uint8_t cmd);
