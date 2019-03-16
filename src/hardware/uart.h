#pragma once

#include <stm32h7xx_hal.h>

#include "hardware/gpio.h"
#include "hardware/hardware.h"
#include "os/async.h"
#include "util/lookup.h"

/*
 * Need to forward-declare interrupt handlers and callbacks so they
 * can be declared friends later.
 */
extern "C" void HAL_UART_TxCpltCallback(void *, UART_HandleTypeDef *);
extern "C" void HAL_UART_TxAbortCallback(void *, UART_HandleTypeDef *);
extern "C" void HAL_UART_ErrorCallback(void *, UART_HandleTypeDef *);

extern "C" void handle_usart1_irq();
extern "C" void handle_usart2_irq();
extern "C" void handle_usart3_irq();
extern "C" void handle_uart4_irq();
extern "C" void handle_uart5_irq();
extern "C" void handle_usart6_irq();
extern "C" void handle_uart7_irq();
extern "C" void handle_uart8_irq();

/**
 * @brief Nonblocking UART peripheral.
 *
 * Example usage:
 * ```
 * // ST-Link uart on nucleo-144 boards
 * UART uart{UART::U3, 9600, GPIO::D, 8, 9};
 * uart.init();
 * uart.transmit("hello!\n\r").block();
 * uart.deinit();
 * ```
 */
class UART : public Hardware {
public:
    /**
     * @brief Type-safe UART port selection.
     */
    enum Port { U1, U2, U3, U4, U5, U6, U7, U8 };

    /**
     * @brief Possible results for a UART transmission.
     *
     * A transmission can either complete successfully, be aborted
     * (successfully) by the user, or fail because of a hardware
     * issue.
     */
    enum class SendStatus { COMPLETE, ABORTED, ERROR };

    UART(Port port, uint32_t baud, GPIO::Port gpio, uint8_t tx, uint8_t rx);

    void init() override;
    void deinit() override;

    Async<SendStatus> transmit(const uint8_t *, size_t len);
    Async<SendStatus> transmit(const char *);

protected:
    Port port;                 //< The UART we own.
    USART_TypeDef *regs;       //< Pointer to our register block;
    uint32_t baud;             //< Intended baudrate.
    UART_HandleTypeDef handle; //< HAL Handle for the UART.

    GPIO tx_pin; //< GPIO tx pin that we own.
    GPIO rx_pin; //< GPIO rx pin that we own.

    Producer<SendStatus> sender; //< Creates @ref Async instances for us.

    static USART_TypeDef *const portregs[8];
    static const uint8_t gpio_afs[8];
    static void (*const en_funcs[8])();
    static void (*const dis_funcs[8])();
    static const IRQn_Type irqns[8];

    static UART *uarts[8];
    static UART_HandleTypeDef *uart_handles[8];

    /*
     * These handlers and callbacks need to be friends so that they
     * can access uarts and uart_handles.
     */
    friend void ::HAL_UART_TxCpltCallback(void *, UART_HandleTypeDef *);
    friend void ::HAL_UART_TxAbortCallback(void *, UART_HandleTypeDef *);
    friend void ::HAL_UART_ErrorCallback(void *, UART_HandleTypeDef *);

    friend void ::handle_usart1_irq();
    friend void ::handle_usart2_irq();
    friend void ::handle_usart3_irq();
    friend void ::handle_uart4_irq();
    friend void ::handle_uart5_irq();
    friend void ::handle_usart6_irq();
    friend void ::handle_uart7_irq();
    friend void ::handle_uart8_irq();
};
