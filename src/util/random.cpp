#include <stm32h7xx_hal.h>

#include "util/random.h"

std::mt19937 rng;

void rng_init() {
    RNG_HandleTypeDef hrng;

    __HAL_RCC_RNG_CLK_ENABLE();
    HAL_RNG_Init(&hrng);

    uint32_t seed;
    HAL_RNG_GenerateRandomNumber(&hrng, &seed);
    rng.seed(seed);

    __HAL_RCC_RNG_CLK_DISABLE();
}
