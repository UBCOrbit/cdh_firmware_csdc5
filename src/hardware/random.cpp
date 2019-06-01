#include "random.h"

/**
 * @brief Initialize the hardware RNG.
 */
void Random::init() {
    __HAL_RCC_RNG_CLK_ENABLE();
    HAL_RNG_Init(&handle);
}

void Random::deinit() {
    HAL_RNG_DeInit(&handle);
    __HAL_RCC_RNG_CLK_DISABLE();
}

uint32_t Random::operator()() {
    uint32_t number;
    HAL_RNG_GenerateRandomNumber(&handle, &number);
    return number;
}
