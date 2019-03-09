#include "hardware/uart.h"

UART::UART(UART::Port port, uint32_t baud, GPIO::Port gpio, uint8_t tx,
           uint8_t rx)
    : port(port), regs(portregs[port]), baud(baud),
      tx_pin(gpio, tx, GPIO::Mode::AlternatePP, GPIO::Resistor::None,
             gpio_afs[port]),
      rx_pin(gpio, rx, GPIO::Mode::AlternatePP, GPIO::Resistor::None,
             gpio_afs[port]) {}

void UART::init() {
    handle.Instance = regs;
    handle.Init = {baud,
                   UART_WORDLENGTH_8B,
                   UART_STOPBITS_1,
                   UART_PARITY_NONE,
                   UART_MODE_TX_RX,
                   UART_HWCONTROL_NONE,
                   UART_OVERSAMPLING_16,
                   UART_ONEBIT_SAMPLING_DISABLED,
                   UART_PRESCALER_DIV1,
                   UART_FIFOMODE_DISABLE,
                   UART_TXFIFO_THRESHOLD_1_8,
                   UART_RXFIFO_THRESHOLD_1_8};
    handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    tx_pin.init();
    rx_pin.init();

    // initialize the clock and interrupt
    clk_en_funcs[port]();
    HAL_UART_Init(&handle);
}

void UART::deinit() {
    HAL_UART_DeInit(&handle);
    clk_dis_funcs[port]();

    rx_pin.deinit();
    tx_pin.deinit();
}

void UART::transmit(uint8_t *data, size_t len) {
    HAL_UART_Transmit_IT(&handle, data, len);
}

UART_HandleTypeDef *UART::uart_handles[8];

// TODO: fill this in later
const uint8_t UART::gpio_afs[] = {
    0,
    0,
    GPIO_AF7_USART3,
    0,
    0,
    0,
    0,
    0,
};

USART_TypeDef *const UART::portregs[] = {
    USART1, USART2, USART3, UART4, UART5, USART6, UART7, UART8,
};

void (*UART::clk_en_funcs[8])() = {
    []() { __HAL_RCC_USART1_CLK_ENABLE(); },
    []() { __HAL_RCC_USART2_CLK_ENABLE(); },
    []() { __HAL_RCC_USART3_CLK_ENABLE(); },
    []() { __HAL_RCC_UART4_CLK_ENABLE(); },
    []() { __HAL_RCC_UART5_CLK_ENABLE(); },
    []() { __HAL_RCC_USART6_CLK_ENABLE(); },
    []() { __HAL_RCC_UART7_CLK_ENABLE(); },
    []() { __HAL_RCC_UART8_CLK_ENABLE(); },
};

void (*UART::clk_dis_funcs[8])() = {
    []() { __HAL_RCC_USART1_CLK_DISABLE(); },
    []() { __HAL_RCC_USART2_CLK_DISABLE(); },
    []() { __HAL_RCC_USART3_CLK_DISABLE(); },
    []() { __HAL_RCC_UART4_CLK_DISABLE(); },
    []() { __HAL_RCC_UART5_CLK_DISABLE(); },
    []() { __HAL_RCC_USART6_CLK_DISABLE(); },
    []() { __HAL_RCC_UART7_CLK_DISABLE(); },
    []() { __HAL_RCC_UART8_CLK_DISABLE(); },
};

void handle_usart1_irq() { HAL_UART_IRQHandler(UART::uart_handles[0]); }

void handle_usart2_irq() { HAL_UART_IRQHandler(UART::uart_handles[1]); }

void handle_usart3_irq() { HAL_UART_IRQHandler(UART::uart_handles[2]); }

void handle_uart4_irq() { HAL_UART_IRQHandler(UART::uart_handles[3]); }

void handle_uart5_irq() { HAL_UART_IRQHandler(UART::uart_handles[4]); }

void handle_usart6_irq() { HAL_UART_IRQHandler(UART::uart_handles[5]); }

void handle_uart7_irq() { HAL_UART_IRQHandler(UART::uart_handles[6]); }

void handle_uart8_irq() { HAL_UART_IRQHandler(UART::uart_handles[7]); }
