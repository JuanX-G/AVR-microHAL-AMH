#ifndef TIMER_H
#define TIMER_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>
#include <util/atomic.h>

extern volatile uint32_t system_millis;

void timer0_init(void);
uint32_t millis(void);

#endif
