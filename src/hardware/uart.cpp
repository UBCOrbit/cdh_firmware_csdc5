#include <cstring>

#include "hardware/uart.h"

/**
 * @brief Construct a UART peripheral.
 *
 * @param port Which UART peripheral to communicate with. Refer
 * to ST documentation for which UARTs can be used on which pins.
 * @param baud Baud rate.  Most of the time, you will want 9600
 * or 115200.
 * @param gpio Which GPIO port both `tx` and `rx` belong to.
 * @param tx The pin to transmit on.
 * @param rx The pin to receive on.
 */
UART::UART(UART::Port port, uint32_t baud, HwOwner<GPIOPort>& gpio_port, uint8_t tx,
           uint8_t rx)
    : port(port), regs(uart_registers[port]), baud(baud), gpio_port_access(gpio_port.get_access()),
      tx_pin(gpio_port_access->get_pin(tx)), rx_pin(gpio_port_access->get_pin(rx))
{
    tx_pin.configure(GPIOPin::Mode::AlternatePP, GPIOPin::Resistor::None, gpio_afs[port]);
    rx_pin.configure(GPIOPin::Mode::AlternatePP, GPIOPin::Resistor::None, gpio_afs[port]);
    uarts[port] = this;
}

/**
 * @brief Initialize a UART.  This handles initializing the necessary
 * GPIOs and installing interrupt handlers, too.
 */
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
    // initialize the clock and interrupt
    clk_en_funcs[port]();
    HAL_NVIC_SetPriority(irqns[port], 14, 15);
    HAL_NVIC_EnableIRQ(irqns[port]);

    HAL_UART_Init(&handle);

    uart_handles[port] = &handle;
}

/**
 * @brief De-initialize a UART, and power off its dependencies, too
 * (GPIOs and interrupt handler).
 */
void UART::deinit() {
    HAL_UART_DeInit(&handle);
    clk_dis_funcs[port]();
    HAL_NVIC_DisableIRQ(irqns[port]);
}

/**
 * @brief Transmit a message over the UART (byte array).
 *
 * @param data Pointer to the start of the byte array.
 * @param len Its length.
 *
 * @return A promise that can be blocked on to retrieve the status of
 * the transmission.
 */
Async<UART::Status> UART::transmit(const uint8_t *data, size_t len) {
    tx = true;
    HAL_UART_Transmit_IT(&handle, data, len);
    return sender.promise();
}

/**
 * @brief Transmit a C string over the UART.
 *
 * This is just a helper function specifically for null-terminated
 * strings.  Do NOT use this to send binary data; it will be mangled.
 *
 * @param msg The C string to be transmitted.
 *
 * @return A promise with the transmission status.
 */
Async<UART::Status> UART::transmit(const char *msg) {
    size_t len = strlen(msg);
    const uint8_t *data = reinterpret_cast<const uint8_t *>(msg);
    return transmit(data, len);
}

/**
 * @brief Receive raw bytes over the UART.
 *
 * @param data Pointer to a buffer at least `len` bytes long.
 * @param len Length of the buffer to receive the data.
 *
 * @return A promise with the receive status.
 */
Async<UART::Status> UART::receive(uint8_t *data, size_t len) {
    rx = true;
    HAL_UART_Receive_IT(&handle, data, len);
    return receiver.promise();
}

UART *UART::uarts[8]; //< Pointers to any UARTs in use, so
                      //  interrupt handlers can access them.
UART_HandleTypeDef *UART::uart_handles[8]; //< The interrupt callbacks
                                           //  demand we give them HAL
                                           //  handles.

/**
 * Which alternate function configuration is necessary to use a UART.
 * TODO: this is not currently complete, add these as more UARTs are
 * used.
 */
const uint8_t UART::gpio_afs[] = {
    0, 0, GPIO_AF7_USART3, 0, 0, 0, 0, 0,
};

/**
 * The interrupt number for each UART.  We need these to know which to
 * enable/disable upon initialization.
 */
const IRQn_Type UART::irqns[8] = {
    USART1_IRQn, USART2_IRQn, USART3_IRQn, UART4_IRQn,
    UART5_IRQn,  USART6_IRQn, UART7_IRQn,  UART8_IRQn,
};

/**
 * Port number to port registers lookup table.  (The HAL wants a register
 * block.)
 */
USART_TypeDef *const UART::uart_registers[] = {
    USART1, USART2, USART3, UART4, UART5, USART6, UART7, UART8,
};

/**
 * Functions to enable UART clocks by number.
 */
void (*const UART::clk_en_funcs[8])() = {
    []() { __HAL_RCC_USART1_CLK_ENABLE(); },
    []() { __HAL_RCC_USART2_CLK_ENABLE(); },
    []() { __HAL_RCC_USART3_CLK_ENABLE(); },
    []() { __HAL_RCC_UART4_CLK_ENABLE(); },
    []() { __HAL_RCC_UART5_CLK_ENABLE(); },
    []() { __HAL_RCC_USART6_CLK_ENABLE(); },
    []() { __HAL_RCC_UART7_CLK_ENABLE(); },
    []() { __HAL_RCC_UART8_CLK_ENABLE(); },
};

/**
 * Functions to disable UART clocks by number.
 */
void (*const UART::clk_dis_funcs[8])() = {
    []() { __HAL_RCC_USART1_CLK_DISABLE(); },
    []() { __HAL_RCC_USART2_CLK_DISABLE(); },
    []() { __HAL_RCC_USART3_CLK_DISABLE(); },
    []() { __HAL_RCC_UART4_CLK_DISABLE(); },
    []() { __HAL_RCC_UART5_CLK_DISABLE(); },
    []() { __HAL_RCC_USART6_CLK_DISABLE(); },
    []() { __HAL_RCC_UART7_CLK_DISABLE(); },
    []() { __HAL_RCC_UART8_CLK_DISABLE(); },
};

/**
 * @brief Called by the HAL when a nonblocking UART transmission is
 * complete.
 */
void HAL_UART_TxCpltCallback(void *d, UART_HandleTypeDef *) {
    UART *u = static_cast<UART *>(d);
    bool wake_up;
    u->tx = false;
    wake_up = u->sender.fulfill_isr(UART::Status::COMPLETE);
    Producer<UART::Status>::yield_isr(wake_up);
}

/**
 * @brief Called by the HAL when a nonblocking UART transmission has
 * been aborted by @ref UART::abort().
 */
void HAL_UART_TxAbortCallback(void *d, UART_HandleTypeDef *) {
    UART *u = static_cast<UART *>(d);
    bool wake_up;
    u->tx = false;
    wake_up = u->sender.fulfill_isr(UART::Status::ABORTED);
    Producer<UART::Status>::yield_isr(wake_up);
}

/**
 * @brief Called by the HAL when a nonblocking UART receive is
 * complete.
 */
void HAL_UART_RxCpltCallback(void *d, UART_HandleTypeDef *) {
    UART *u = static_cast<UART *>(d);
    bool wake_up;
    u->rx = false;
    wake_up = u->receiver.fulfill_isr(UART::Status::COMPLETE);
    Producer<UART::Status>::yield_isr(wake_up);
}

/**
 * @brief Called by the HAL when a nonblocking UART operation has
 * failed.
 */
void HAL_UART_ErrorCallback(void *d, UART_HandleTypeDef *uart) {
    UART *u = static_cast<UART *>(d);
    UART::Status err;
    switch (uart->ErrorCode) {
    case HAL_UART_ERROR_PE:
        err = UART::Status::ERROR_PARITY;
        break;
    case HAL_UART_ERROR_NE:
        err = UART::Status::ERROR_NOISE;
        break;
    case HAL_UART_ERROR_FE:
        err = UART::Status::ERROR_FRAME;
        break;
    case HAL_UART_ERROR_ORE:
        err = UART::Status::ERROR_OVERRUN;
        break;
    default:
        err = UART::Status::ERROR_UNKNOWN;
    }

    bool wake_up = false;
    if (u->tx) {
        wake_up |= u->sender.fulfill_isr(err);
        u->tx = false;
    }
    if (u->rx) {
        wake_up |= u->receiver.fulfill_isr(err);
        u->rx = false;
    }

    // If a task was woken up, we have to yield to the kernel.
    Producer<UART::Status>::yield_isr(wake_up);
}

/**
 * @defgroup UART IRQ Handlers
 * @{
 */
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
/** @} */
