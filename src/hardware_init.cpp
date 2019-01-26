#include "os.h"
#include <stm32h7xx_hal.h>

void hardware_init() {
    __GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef c;
    c.Mode = GPIO_MODE_OUTPUT_PP;
    c.Speed = GPIO_SPEED_FREQ_LOW;
    c.Pin = GPIO_PIN_7;
    c.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &c);

    SystemCoreClock = HAL_RCC_GetSysClockFreq();
    HAL_SYSTICK_Config(SystemCoreClock / 1000);
}
