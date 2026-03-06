#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "../../config.h"

void uart_init(uint16_t ubrr);
void uart_tx(uint8_t data);
uint8_t uart_rx(void);
void uart_print(const char *str);

#endif
