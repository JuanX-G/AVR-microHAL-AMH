#pragma once

#include <avr/io.h>
#include <stdint.h>

typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT
} gpio_direction_t;

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
} gpio_level_t;

typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    volatile uint8_t *pin;
    uint8_t bit;
} gpio_t;

void gpio_init(gpio_t *gpio, gpio_direction_t dir);
void gpio_write(gpio_t *gpio, gpio_level_t level);
gpio_level_t gpio_read(gpio_t *gpio);
void gpio_toggle(gpio_t *gpio);
void gpio_pullup_enable(gpio_t *gpio);
