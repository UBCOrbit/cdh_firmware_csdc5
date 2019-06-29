#pragma once

#include "hardware/uart.h"

void debug_msg(const char *msg);
const char *debug_getline(UART &uart);
