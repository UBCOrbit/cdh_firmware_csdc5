#include "hardware/spi.h"
#include <cstring>

SPI::SPI(SPI::Port port, uint32_t baud, GPIO::Port gpio, uint8_t miso, uint8_t mosi, 
        uint8_t slck, uint8_t nss, uint32_t mode, uint32_t direction, uint32_t nss_mode):
        port(port),
        baud(baud),
        miso(gpio,miso, GPIO::Mode::AlternatePP, GPIO::Resistor::None,
             gpio_afs[port]), 
        mosi(gpio,mosi, GPIO::Mode::AlternatePP, GPIO::Resistor::None,
             gpio_afs[port]), 
        slck(gpio,slck, GPIO::Mode::AlternatePP, GPIO::Resistor::None,
             gpio_afs[port]), 
        nss(gpio,nss, GPIO::Mode::AlternatePP, GPIO::Resistor::None,
             gpio_afs[port]){
        spis[port] = this;
    }

/**
 * @brief Initialize a SPI.  This handles initializing the necessary
 * GPIOs and installing interrupt handlers, too.
 */
 void SPI::init(){

    miso.init();
    mosi.init();
    slck.init();
    nss.init();

 }

 /**
 * @brief De-initialize a SPI, and power off its dependencies, too
 * (GPIOs and interrupt handler).
 */
void SPI::deinit() {
    HAL_SPI_DeInit(&handle);
    dis_funcs[port]();
    HAL_NVIC_DisableIRQ(irqns[port]);

    miso.deinit();
    mosi.deinit();
    slck.deinit();
    nss.deinit();
}

 /**
 * @brief Transmit a message over the SPI (byte array).
 *
 * @param data Pointer to the start of the byte array.
 * @param len Its length.
 *
 * @return A promise that can be blocked on to retrieve the status of
 * the transmission.
 */
Async<SPI::SendStatus> SPI::transmit(uint8_t *data, size_t len) {
    HAL_SPI_Transmit_IT(&handle, data, len);
    return sender.promise();
}

/**
 * @brief Transmit a C string over the SPI.
 *
 * This is just a helper function specifically for null-terminated
 * strings.  Do NOT use this to send binary data; it will be mangled.
 *
 * @param msg The C string to be transmitted.
 *
 * @return A promise with the transmission status.
 */
Async<SPI::SendStatus> SPI::transmit(char *msg) {
    size_t len = strlen(msg);
    uint8_t *data = reinterpret_cast<uint8_t *>(msg);
    
    return transmit(data, len);
}

SPI *SPI::spis[6];           //< Pointers to any SPIs in use, so
                                //  interrupt handlers can access them.
SPI_HandleTypeDef *SPI::spi_handles[6]; //< The interrupt callbacks
                                           //  demand we give them HAL
                                           //  handles.

//TODO: Finish below

/**
 * Which alternate function configuration is necessary to use a SPI.
 * TODO: this is not currently complete, add these as more SPIs are
 * used.
 */
const uint8_t SPI::gpio_afs[] = {
    0, 0, GPIO_AF7_SPI3, 0, 0, 0,
};

/**
 * The interrupt number for each SPI.  We need these to know which to
 * enable/disable upon initialization.
 */
const IRQn_Type SPI::irqns[6] = {
    SPI1_IRQn, SPI2_IRQn, SPI3_IRQn, SPI4_IRQn,
    SPI5_IRQn,  SPI6_IRQn, 
};

/**
 * Port number to port registers lookup table.  (The HAL wants a register block.)
 */
SPI_TypeDef *const SPI::portregs[] = {
    SPI1, SPI2, SPI3, SPI4, SPI5, SPI6,
};

/**
 * Functions to enable SPI clocks by number.
 */
void (*const SPI::en_funcs[6])() = {
    []() { __HAL_RCC_SPI1_CLK_ENABLE(); },
    []() { __HAL_RCC_SPI2_CLK_ENABLE(); },
    []() { __HAL_RCC_SPI3_CLK_ENABLE(); },
    []() { __HAL_RCC_SPI4_CLK_ENABLE(); },
    []() { __HAL_RCC_SPI5_CLK_ENABLE(); },
    []() { __HAL_RCC_SPI6_CLK_ENABLE(); },
};

/**
 * Functions to disable SPI clocks by number.
 */
void (*const SPI::dis_funcs[6])() = {
    []() { __HAL_RCC_SPI1_CLK_DISABLE(); },
    []() { __HAL_RCC_SPI2_CLK_DISABLE(); },
    []() { __HAL_RCC_SPI3_CLK_DISABLE(); },
    []() { __HAL_RCC_SPI4_CLK_DISABLE(); },
    []() { __HAL_RCC_SPI5_CLK_DISABLE(); },
    []() { __HAL_RCC_SPI6_CLK_DISABLE(); },
};


// /**
//  * @brief Called by the HAL when a nonblocking UART transmission is
//  * complete.
//  */
// void HAL_SPI_TxCpltCallback(void *d, SPI_HandleTypeDef *) {
//     static_cast<SPI *>(d)->sender.fulfill_isr(SPI::SendStatus::COMPLETE);
// }

// /**
//  * @brief Called by the HAL when a nonblocking UART transmission has
//  * been aborted by @ref UART::abort().
//  */
// void HAL_SPI_TxAbortCallback(void *d, SPI_HandleTypeDef *) {
//     static_cast<SPI *>(d)->sender.fulfill_isr(SPI::SendStatus::ABORTED);
// }

// /**
//  * @brief Called by the HAL when a nonblocking UART operation has
//  * failed.
//  */
// void HAL_SPI_ErrorCallback(void *d, SPI_HandleTypeDef *) {
//     static_cast<SPI *>(d)->sender.fulfill_isr(SPI::SendStatus::ERROR);
// }
