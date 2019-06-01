#include <stm32h7xx_hal.h>

/**
 * @brief Stores the CPU clockrate.
 *
 * This is equivalent to `rcc_c_ck`, which is the same as `sys_ck` scaled by
 * `D1CPRE`.
 */
uint32_t SystemCoreClock = 64000000;

/**
 * @brief Stores the Domain 2 AHB 1&2 clocks.
 *
 * This is eqiuvalent to `rcc_hclk`, which is the same as @ref SystemCoreClock
 * scaled by `HPRE`.
 */
uint32_t SystemD2Clock = 64000000;

/**
 * @brief Map from prescale register values to powers of two.
 */
const uint8_t D1CorePrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4,
                                      1, 2, 3, 4, 6, 7, 8, 9};

/**
 * @brief Initialize the clock source.
 *
 * Later on, this will configure the clock in a smarter way to balance power and
 * run peripherals at their optimal speeds, but for now, it justs leaves
 * everything as the default and sets @ref SystemCoreClock so that FreeRTOS and
 * the HAL know how it's configured.
 */
void clock_init() {
    HAL_RCCEx_GetD1SysClockFreq();
    HAL_RCC_GetHCLKFreq();

    __HAL_RCC_PLL_ENABLE();
    __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVQ);
    __HAL_RCC_PLL_CONFIG(RCC_PLLSOURCE_HSI, 32, 128, 2, 1, 1);

    SET_BIT(RCC->D2CCIP2R, RCC_D2CCIP2R_RNGSEL_0);
    CLEAR_BIT(RCC->D2CCIP2R, RCC_D2CCIP2R_RNGSEL_1);
}
