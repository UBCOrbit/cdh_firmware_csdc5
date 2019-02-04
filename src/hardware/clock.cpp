#include <stm32h7xx_hal.h>

uint32_t SystemCoreClock = 64000000;
uint32_t SystemD2Clock = 64000000;
const uint8_t D1CorePrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4,
                                      1, 2, 3, 4, 6, 7, 8, 9};

void clock_init() {}
