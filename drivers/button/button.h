#pragma once
#include <stdint.h>
#include "../gpio/gpio.h"

typedef struct {
    gpio_t *gpio;
    uint8_t state;
    uint8_t last_raw;
    uint8_t last_state;
    uint16_t counter;
} button_t;

void button_init(button_t *btn, gpio_t *gpio);
void button_update(button_t *btn);      
uint8_t button_is_pressed(button_t *btn);
uint8_t button_just_pressed(button_t *btn);
uint8_t button_just_released(button_t *btn);

