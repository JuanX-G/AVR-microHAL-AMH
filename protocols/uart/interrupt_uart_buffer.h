#include "../../config.h"
_Static_assert(
    (UART_BUFFER_SIZE != 0) &&
    ((UART_BUFFER_SIZE & (UART_BUFFER_SIZE - 1)) == 0),
    "UART_BUFFER_SIZE must be a power of 2"
);

#ifdef INTERRUPT_UART_CEN
#ifndef INTERRUPT_UART_H
#define INTERRUPT_UART_H

#include <stdint.h>
#include "../../config.h"
#include "assert.h"
#include <stdbool.h>

#define UART_BUFFER_MASK (UART_BUFFER_SIZE - 1)

typedef struct {
	volatile uint8_t buffer[UART_BUFFER_SIZE];
	volatile uint8_t head;
	volatile uint8_t tail;
	volatile uint8_t buffer_overflow;
} uart_ring_t;

bool uart_available(void);
uint8_t uart_read_byte(uint8_t *data);
bool uart_overflow(void);
void uart_clear_overflow(void);
#endif
#endif
