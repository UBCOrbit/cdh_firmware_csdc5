#include "hardware/gpio.h"

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
GPIO::GPIO(GPIO::Port port, uint32_t pin, GPIO::Mode mode, GPIO::Resistor res,
           uint32_t alt)
    : port(port), regs(get_regs()), pin(1 << pin), mode(mode), res(res),
      alt(alt) {}

/**
 * @brief Write to a GPIO pin.
 *
 * @param on true = HIGH, false = LOW
 */
void GPIO::write(bool on) { HAL_GPIO_WritePin(regs, pin, (GPIO_PinState)on); }

/**
 * @brief Read a digital pin.
 *
 * @return true = HIGH, false = LOW
 */
bool GPIO::read() { return HAL_GPIO_ReadPin(regs, pin); }

/**
 * Figures out which GPIO port we were given, so that we can figure
 * out which bit to twiddle in AHB4ENR. This works becuase GPIO registers
 * are layed out contiguously in memory starting at GPIOA, and the entire
 * block is 0x400 bytes long.
 *
 * @return The number corresponding to the PORT (A = 0, B = 1, ...).
 */
GPIO_TypeDef *GPIO::get_regs() {
    return (GPIO_TypeDef *)((port * 0x400) + (uint32_t)GPIOA);
}

/**
 * @brief Initialize this GPIO pin.
 *
 * Note: this also enables the clock for the GPIO port in question, but @ref
 * GPIO::deinit does not disable again after, since other GPIOs might still be
 * using it.
 *
 * This mechanism should be replaced by a more robust dependency-tree based one
 * when there's time.
 */
void GPIO::init() {
    pins[port]++;

    // Enable the port we're using.
    SET_BIT(RCC->AHB4ENR, 1 << port);

    GPIO_InitTypeDef c{pin, mode, res, GPIO_SPEED_FREQ_LOW, alt};
    HAL_GPIO_Init(regs, &c);
}

void GPIO::deinit() {
    pins[port]--;

    // If no more pins are using this port, shut off its clock to save
    // some power.
    if (!pins[port])
        CLEAR_BIT(RCC->AHB4ENR, 1 << port);

    HAL_GPIO_DeInit(regs, pin);
}

uint8_t GPIO::pins[11] = {0};
