#include "hardware/uart.h"

UART::UART(UART::Port port, uint32_t baud, GPIO::Port gpio, uint8_t tx,
           uint8_t rx)
    : port(port), regs(portregs[port]), baud(baud),
      tx_pin(gpio, tx, GPIO::Mode::AlternatePP, GPIO::Resistor::None,
             gpio_afs[port]),
      rx_pin(gpio, rx, GPIO::Mode::AlternatePP, GPIO::Resistor::None,
             gpio_afs[port]) {
    uarts[port] = this;
}

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
    en_funcs[port]();
    HAL_NVIC_SetPriority(irqns[port], 14, 15);
    HAL_NVIC_EnableIRQ(irqns[port]);

    HAL_UART_Init(&handle);

    uart_handles[port] = &handle;
}

void UART::deinit() {
    HAL_UART_DeInit(&handle);
    dis_funcs[port]();
    HAL_NVIC_DisableIRQ(irqns[port]);

    rx_pin.deinit();
    tx_pin.deinit();
}

Async<int> UART::transmit(uint8_t *data, size_t len) {
    HAL_UART_Transmit_IT(&handle, data, len);
    return sender.promise();
}

UART *UART::uarts[8];
UART_HandleTypeDef *UART::uart_handles[8];

// TODO: fill this in later
const uint8_t UART::gpio_afs[] = {
    0, 0, GPIO_AF7_USART3, 0, 0, 0, 0, 0,
};

const IRQn_Type UART::irqns[8] = {
    USART1_IRQn, USART2_IRQn, USART3_IRQn, UART4_IRQn,
    UART5_IRQn,  USART6_IRQn, UART7_IRQn,  UART8_IRQn,
};

USART_TypeDef *const UART::portregs[] = {
    USART1, USART2, USART3, UART4, UART5, USART6, UART7, UART8,
};

void (*const UART::en_funcs[8])() = {
    []() { __HAL_RCC_USART1_CLK_ENABLE(); },
    []() { __HAL_RCC_USART2_CLK_ENABLE(); },
    []() { __HAL_RCC_USART3_CLK_ENABLE(); },
    []() { __HAL_RCC_UART4_CLK_ENABLE(); },
    []() { __HAL_RCC_UART5_CLK_ENABLE(); },
    []() { __HAL_RCC_USART6_CLK_ENABLE(); },
    []() { __HAL_RCC_UART7_CLK_ENABLE(); },
    []() { __HAL_RCC_UART8_CLK_ENABLE(); },
};

void (*const UART::dis_funcs[8])() = {
    []() { __HAL_RCC_USART1_CLK_DISABLE(); },
    []() { __HAL_RCC_USART2_CLK_DISABLE(); },
    []() { __HAL_RCC_USART3_CLK_DISABLE(); },
    []() { __HAL_RCC_UART4_CLK_DISABLE(); },
    []() { __HAL_RCC_UART5_CLK_DISABLE(); },
    []() { __HAL_RCC_USART6_CLK_DISABLE(); },
    []() { __HAL_RCC_UART7_CLK_DISABLE(); },
    []() { __HAL_RCC_UART8_CLK_DISABLE(); },
};

void HAL_UART_TxCpltCallback(void *d, UART_HandleTypeDef *handle) {
    static_cast<UART *>(d)->sender.fulfill_isr(123);
}

void handle_usart1_irq() {
    HAL_UART_IRQHandler(UART::uarts[0], UART::uart_handles[0]);
}

void handle_usart2_irq() {
    HAL_UART_IRQHandler(UART::uarts[1], UART::uart_handles[1]);
}

void handle_usart3_irq() {
    HAL_UART_IRQHandler(UART::uarts[2], UART::uart_handles[2]);
}

void handle_uart4_irq() {
    HAL_UART_IRQHandler(UART::uarts[3], UART::uart_handles[3]);
}

void handle_uart5_irq() {
    HAL_UART_IRQHandler(UART::uarts[4], UART::uart_handles[4]);
}

void handle_usart6_irq() {
    HAL_UART_IRQHandler(UART::uarts[5], UART::uart_handles[5]);
}

void handle_uart7_irq() {
    HAL_UART_IRQHandler(UART::uarts[6], UART::uart_handles[6]);
}

void handle_uart8_irq() {
    HAL_UART_IRQHandler(UART::uarts[7], UART::uart_handles[7]);
}
