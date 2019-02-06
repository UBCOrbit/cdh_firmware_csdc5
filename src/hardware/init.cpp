#include <stm32h7xx_hal.h>

#include "hardware/gpio.h"
#include "hardware/init.h"

/**
 * @brief Initialize peripherals and the HAL.
 *
 * This is temporary, and will be refactored into a more robust system for
 * initializing GPIOs.
 */
void hardware_init() {
    HAL_Init();

    __SYSCFG_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef c;
    c.Mode = GPIO_MODE_OUTPUT_PP;
    c.Speed = GPIO_SPEED_FREQ_LOW;
    c.Pin = GPIO_PIN_7 | GPIO_PIN_14 | GPIO_PIN_0;
    c.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &c);

    __GPIOC_CLK_ENABLE();
    c.Mode = GPIO_MODE_IT_RISING;
    c.Speed = GPIO_SPEED_FREQ_LOW;
    c.Pin = GPIO_PIN_13;
    c.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &c);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    uart_init();
}

UART_HandleTypeDef uart;

void uart_init() {
    __GPIOD_CLK_ENABLE();
    __USART3_CLK_ENABLE();

    GPIO_InitTypeDef c;
    c.Mode = GPIO_MODE_AF_PP;
    c.Pull = GPIO_PULLUP;
    c.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    c.Speed = GPIO_SPEED_FREQ_LOW;
    c.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &c);

    uart.Init.WordLength = UART_WORDLENGTH_8B;
    uart.Init.StopBits = UART_STOPBITS_1;
    uart.Init.BaudRate = 115200;
    uart.Instance = USART3;
    uart.Init.Parity = UART_PARITY_NONE;
    uart.Init.Mode = UART_MODE_TX_RX;
    uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart.Init.OverSampling = UART_OVERSAMPLING_16;
    uart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    uart.Init.Prescaler = UART_PRESCALER_DIV1;
    uart.Init.FIFOMode = UART_FIFOMODE_DISABLE;
    uart.Init.TXFIFOThreshold = UART_TXFIFO_THRESHOLD_1_8;
    uart.Init.RXFIFOThreshold = UART_RXFIFO_THRESHOLD_1_8;
    uart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&uart);
}

TIM_HandleTypeDef tim2;

/**
 * @brief Force the HAL to use a hardware timer instead of the SysTick.
 */
extern "C" HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
    __HAL_RCC_TIM2_CLK_ENABLE();

    // todo

    return HAL_OK;
}