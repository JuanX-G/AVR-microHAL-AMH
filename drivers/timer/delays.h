#ifndef DELAYS_H
#define DELAYS_H
#include <stdint.h>
#include "timer.h"

typedef struct {
    uint32_t start;
    uint32_t period;
} delay_t;

bool delay_expired(delay_t *d);
void delay_start(delay_t *d, uint32_t ms);

#endif
