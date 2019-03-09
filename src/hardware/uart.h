#pragma once

#include <stm32h7xx_hal.h>
#include <tuple>

#include "hardware/gpio.h"
#include "hardware/hardware.h"
#include "util/lookup.h"

extern "C" void handle_usart1_irq();
extern "C" void handle_usart2_irq();
extern "C" void handle_usart3_irq();
extern "C" void handle_uart4_irq();
extern "C" void handle_uart5_irq();
extern "C" void handle_usart6_irq();
extern "C" void handle_uart7_irq();
extern "C" void handle_uart8_irq();

class UART : public Hardware {
public:
    enum Port { U1, U2, U3, U4, U5, U6, U7, U8 };

    UART(Port port, uint32_t baud, GPIO::Port gpio, uint8_t tx, uint8_t rx);

    void init() override;
    void deinit() override;

    void transmit(uint8_t *, size_t len);

protected:
    Port port;
    USART_TypeDef *regs;
    uint32_t baud;
    UART_HandleTypeDef handle;

    GPIO tx_pin;
    GPIO rx_pin;

    USART_TypeDef *get_regs();

    static USART_TypeDef *const portregs[8];
    static const uint8_t gpio_afs[8];
    static void (*clk_en_funcs[8])();
    static void (*clk_dis_funcs[8])();

    static UART_HandleTypeDef *uart_handles[8];

    friend void ::handle_usart1_irq();
    friend void ::handle_usart2_irq();
    friend void ::handle_usart3_irq();
    friend void ::handle_uart4_irq();
    friend void ::handle_uart5_irq();
    friend void ::handle_usart6_irq();
    friend void ::handle_uart7_irq();
    friend void ::handle_uart8_irq();
};
