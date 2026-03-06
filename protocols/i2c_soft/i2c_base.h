#pragma once
#include <avr/io.h>
#include <util/delay.h>

void soft_i2c_init(void);
void soft_i2c_start(void);
void soft_i2c_stop(void);
