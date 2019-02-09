#include "hardware/gpio.h"

#include <array>

/**
 * @brief Construct a new GPIO object
 *
 * Right now this is acting as an example peripheral, since reading/writing to
 * GPIOs is atomic and doesn't require the use of synchronization primitives
 * from the kernel.
 *
 * @param port The register block pointing to the GPIO port. (GPIOx)
 * @param pin The pin *number*, not one of the macros provided by the HAL.
 * @param mode Input/output/alternate as well as the push-pull/open drain mode.
 * @param res Pull-up/pull-down resistor configuration.
 * @param alt If `mode` is @ref GPIO::AlternatePP or @ref GPIO::AlternateOD,
 * this selects the alternae function.
 */
GPIO::GPIO(GPIO_TypeDef *port, uint32_t pin, GPIO::Mode mode,
           GPIO::Resistor res, uint32_t alt)
    : port(port), pin(1 << pin), mode(mode), res(res), alt(alt) {}

/**
 * @brief Write to a GPIO pin.
 *
 * @param on true = HIGH, false = LOW
 */
void GPIO::set(bool on) { HAL_GPIO_WritePin(port, pin, (GPIO_PinState)on); }

/**
 * @brief Initialize this GPIO pin.
 *
 * Note: this also enables the clock for the GPIO port in question, but @ref
 * GPIO::deinnit does not disable again after, since other GPIOs might still be
 * using it.
 *
 * This mechanism should be replaced by a more robust dependency-tree based one
 * when there's time.
 */
void GPIO::init() {
    // Need to figure out which GPIO port we were given, so that we can figure
    // out which bit to twiddle in AHB4ENR. This works becuase GPIO registers
    // are layed out contiguously in memory starting at GPIOA, and the entire
    // block is 0x400 bytes long.
    int portnum = ((uint32_t)port - (uint32_t)GPIOA) / 0x400;
    SET_BIT(RCC->AHB4ENR, 1 << portnum);

    GPIO_InitTypeDef c{pin, mode, res, alt};
    HAL_GPIO_Init(port, &c);
    enabled = true;
}

void GPIO::deinit() {
    HAL_GPIO_DeInit(port, pin);
    enabled = false;
}

/**
 * GPIOs are all clocked by `rcc_hclk4`, and consume roughly 1 uW/MHz.
 */
uint32_t GPIO::idle_power() { return 1 * (HAL_RCC_GetHCLKFreq() / 1000000); }
