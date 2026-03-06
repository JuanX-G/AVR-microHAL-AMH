#include "delays.h"
#include <stdbool.h>

bool delay_expired(delay_t *d) {
    return millis() - d->start >= d->period;
}

void delay_start(delay_t *d, uint32_t ms) {
    d->period = ms;
    d->start = millis();
}
