#include "gpio.h"

void gpio_init(gpio_t *gpio, gpio_direction_t dir) {
    if (dir == GPIO_OUTPUT)
        *(gpio->ddr) |= (1 << gpio->bit);
    else
        *(gpio->ddr) &= ~(1 << gpio->bit);
}

void gpio_write(gpio_t *gpio, gpio_level_t level) {
    if (level == GPIO_HIGH)
        *(gpio->port) |= (1 << gpio->bit);
    else
        *(gpio->port) &= ~(1 << gpio->bit);
}

gpio_level_t gpio_read(gpio_t *gpio) {
    if (*(gpio->pin) & (1 << gpio->bit))
        return GPIO_HIGH;
    else
        return GPIO_LOW;
}

/* Toggle the state of the selected GPIO
 *
 * ACCEPTS:
 * 	> The GPIO to enable pull-up on
 */
void gpio_toggle(gpio_t *gpio) {
    *(gpio->port) ^= (1 << gpio->bit);
}

/* Enable internal pull-ups on the selected GPIO
 *
 * ACCEPTS:
 * 	> The GPIO to enable pull-up on
 */
void gpio_pullup_enable(gpio_t *gpio) {
    *(gpio->port) |= (1 << gpio->bit);
}
