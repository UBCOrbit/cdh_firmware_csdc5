#include <cstring>

#include "hardware/uart.h"

/**
 * @brief Construct a SPI peripheral.
 *
 * @param port Which SPI peripheral to communicate with. Refer
 * to ST documentation for which SPI can be used on which pins.
 * @param baud Baud rate.  Most of the time, you will want 9600
 * or 115200.
 * @param 
 * @param 
 * @param 
 */

SPI::SPI(SPI::Port, uint32_t baud, GPIO::Port gpio, uint8_t miso, uint8_t mosi, 
        unit8_t slck, unit8_t nss, uint32_t mode, unit32_t direction, unit32_t nss_mode):
        port(port),regs(SpiPortregs[port]),baud(baud),
        miso(), mosi(), slck(), nss(), mode(), direction(), nss_mode(){
            spi[ports] = this;
    }

/**
 * @brief Initialize a SPI.  This handles initializing the necessary
 * GPIOs and installing interrupt handlers, too.
 */

void SPI::init(){

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

}