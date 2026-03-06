#include <avr/io.h>
#pragma once
#include "../drivers/gpio/gpio.h"
#include "../drivers/button/button.h"

gpio_t pause_play_btn_gpio = { &DDRD, &PORTD, &PIND, PD6 };
button_t pause_play_btn;

gpio_t next_btn_gpio = { &DDRD, &PORTD, &PIND, PD5 };
button_t next_btn;

#define BTN_FULL_INIT(gpio, btn) do {\
	gpio_init(gpio, GPIO_INPUT); \
	gpio_pullup_enable(gpio); \
	button_init(btn, gpio); } while (0);
