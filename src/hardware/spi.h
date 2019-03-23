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
//extern "C" void HAL_SPI_TxCpltCallback(void *, SPI_HandleTypeDef *);
//extern "C" void HAL_SPI_TxAbortCallback(void *, SPI_HandleTypeDef *);
//extern "C" void HAL_SPI_ErrorCallback(void *, SPI_HandleTypeDef *);

class SPI : public Hardware {
public:
    SPI();

    /**
     * @brief Type-safe SPI port selection.
     */
    enum Port { S1, S2, S3, S4, S5, S6 };

    /**
     * @brief Possible results for a SPI transmission.
     *
     * A transmission can either complete successfully, be aborted
     * (successfully) by the user, or fail because of a hardware
     * issue.
     */
    enum class SendStatus { COMPLETE, ABORTED, ERROR };

    SPI(Port port, uint32_t baud, GPIO::Port gpio, uint8_t miso, uint8_t mosi,
        uint8_t slck, uint8_t nss, uint32_t mode, uint32_t direction,
        uint32_t nss_mode);

    void init() override;
    void deinit() override;

    Async<SendStatus> transmit(uint8_t *, size_t len);
    Async<SendStatus> transmit(char *);

protected:
    Port port;                //< The SPI we own.
    SPI_TypeDef *regs;        //< Pointer to our register block;
    uint32_t baud;            //< Intended baudrate.
    SPI_HandleTypeDef handle; //< HAL Handle for the SPI.

    GPIO miso; //< GPIO miso pin that we own
    GPIO mosi; //< GPIO mosi pin that we own
    GPIO slck; //< GPIO serial-clock pin that we own
    GPIO nss;  //< GPIO NSS pin that we own

    Producer<SendStatus> sender; //< Creates @ref Async instances for us.

    static SPI_TypeDef *const portregs[6];
    static const uint8_t gpio_afs[6];
    static void (*const en_funcs[6])();
    static void (*const dis_funcs[6])();
    static const IRQn_Type irqns[6];

    static SPI *spis[6];
    static SPI_HandleTypeDef *spi_handles[6];

    /*
     * These handlers and callbacks need to be friends so that they
     * can access uarts and uart_handles.
     */
    //friend void ::HAL_SPI_TxCpltCallback(void *, SPI_HandleTypeDef *);
    //friend void ::HAL_SPI_TxAbortCallback(void *, SPI_HandleTypeDef *);
    //friend void ::HAL_SPI_ErrorCallback(void *, SPI_HandleTypeDef *);

    // friend void ::handle_usart1_irq();
    // friend void ::handle_usart2_irq();
    // friend void ::handle_usart3_irq();
    // friend void ::handle_uart4_irq();
    // friend void ::handle_uart5_irq();
    // friend void ::handle_usart6_irq();
    // friend void ::handle_uart7_irq();
    // friend void ::handle_uart8_irq();
};