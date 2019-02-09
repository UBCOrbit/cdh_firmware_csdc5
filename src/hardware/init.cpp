#include <stm32h7xx_hal.h>

#include "hardware/gpio.h"
#include "hardware/init.h"

/**
 * @brief Initialize peripherals and the HAL.
 *
 * This is temporary, and will be refactored into a more robust system for
 * initializing GPIOs.
 */
void hardware_init() { HAL_Init(); }

TIM_HandleTypeDef hal_timer;

/**
 * @brief Force the HAL to use a hardware timer (TIM2) instead of the SysTick.
 */
extern "C" HAL_StatusTypeDef HAL_InitTick(uint32_t priority) {
    __HAL_RCC_TIM2_CLK_ENABLE();

    // todo: should probably not have this be the highest priority
    HAL_NVIC_SetPriority(TIM2_IRQn, priority, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    uint32_t freq = HAL_RCC_GetPCLK1Freq();
    uint32_t presc = (freq / 1000000) - 1;
    uint32_t period = (1000000 / 1000) - 1;

    __HAL_DBGMCU_FREEZE_TIM2();

    hal_timer.Instance = TIM2;
    hal_timer.Init = {presc, TIM_COUNTERMODE_UP, period, 0, 0, 0};
    auto s = HAL_TIM_Base_Init(&hal_timer);
    if (s != HAL_OK)
        return s;
    s = HAL_TIM_Base_Start_IT(&hal_timer);
    if (s != HAL_OK)
        return s;

    return s;
}

/**
 * @brief Handle the TIM2 counter overflowing, and notify the HAL.
 */
extern "C" void handle_tim2_irq() { HAL_IncTick(); }