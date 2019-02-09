#include <stm32h7xx_hal.h>

#include "hardware/random.h"

/**
 * @brief Initialize the hardware RNG.
 *
 * Callers beware: this will briefly spinlock while the hardware RNG is used
 * once to initialize the mersenne twister.
 */
void Random::init() {
    __HAL_RCC_RNG_CLK_ENABLE();
    HAL_RNG_Init(&handle);

    uint32_t seed;
    HAL_RNG_GenerateRandomNumber(&handle, &seed);
    twister.seed(seed);
}

void Random::deinit() {
    HAL_RNG_DeInit(&handle);
    __HAL_RCC_RNG_CLK_DISABLE();
}

/**
 * @brief Get a fast, software random number.
 *
 * @return uint32_t Non-cryptographically secure random number.
 */
uint32_t Random::operator()() { return twister(); }
