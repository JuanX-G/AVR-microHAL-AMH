#include <avr/io.h>
#include "uart.h"

void uart_init(uint16_t ubrr) {
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)ubrr;

	UCSRB = (1 << RXEN) | (1 << TXEN);

	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void uart_tx(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

uint8_t uart_rx(void) {
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}

void uart_print(const char *str) {
	while (*str) {
		uart_tx(*str++);
	}
}
