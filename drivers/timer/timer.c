#include "timer.h"

volatile uint16_t system_ticks;
volatile uint16_t system_ticks_hi;

void timer0_init(void) {
	TCCR0 = (1 << WGM01);
	OCR0 = 124;
	TCCR0 |= (1 << CS01) | (1 << CS00);
	TIMSK |= (1 << OCIE0);
}

ISR(TIMER0_COMP_vect) {
	if (++system_ticks == 0)
        system_ticks_hi++;
}

uint32_t millis(void) {
    uint16_t lo, hi;

    do {
        hi = system_ticks_hi;
        lo = system_ticks;
    } while (hi != system_ticks_hi);

    return ((uint32_t)hi << 16) | lo;
}
