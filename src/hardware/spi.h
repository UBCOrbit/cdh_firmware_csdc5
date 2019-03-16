#pragma once

#include <stm32h7xx_hal.h>

#include "hardware/gpio.h"
#include "hardware/hardware.h"
#include "os/async.h"
#include "util/lookup.h"

class SPI : public Hardware{
    public:

        /**
         * @brief Type-safe SPI port selection.
        */
        enum Port{S1, S2, S3, S4, S5, S6};

        /**
         * @brief Possible results for a SPI transmission.
         *
         * A transmission can either complete successfully, be aborted
         * (successfully) by the user, or fail because of a hardware
         * issue.
         */
        enum class SendStatus { COMPLETE, ABORTED, ERROR };

        SPI(Port port, uint32_t baud, GPIO::Port gpio, uint8_t miso, uint8_t mosi, 
        unit8_t slck, unit8_t nss, uint32_t mode, unit32_t direction, unit32_t nss_mode);

        void init() override;
        void deinit() override;

    protected:

        Port port;                 //< The SPI we own.
        SPI_TypeDef *regs;         //< Pointer to our register block;
        uint32_t baud;             //< Intended baudrate.
        SPI_HandleTypeDef handle;  //< HAL Handle for the SPI.

        GPIO miso;                 //< GPIO miso pin that we own
        GPIO mosi;                 //< GPIO mosi pin that we own
        GPIO slck;                 //< GPIO serial-clock pin that we own
        GPIO nss;                  //< GPIO NSS pin that we own

        Producer<SendStatus> sender;  //< Creates @ref Async instances for us.

        static SPI_TypeDef *const SpiPortregs[8];
        static const uint8_t gpio_afs[8];
        static void (*const en_funcs[8])();
        static void (*const dis_funcs[8])();
        static const IRQn_Type irqns[8];

        static SPI *spi[8];
        static SPI_HandleTypeDef *spi_handles[8];

        // Friend stuff
}