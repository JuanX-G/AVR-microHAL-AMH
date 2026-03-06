#include "interrupt_uart_buffer.h"
#ifdef INTERRUPT_UART_CEN
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/atomic.h>

volatile uart_ring_t uart_rx_buf = { {0}, 0, 0, 0};

inline bool uart_available(void) {
	return (uart_rx_buf.head != uart_rx_buf.tail);
}
inline void uart_clear_overflow(void) {
    uart_rx_buf.buffer_overflow = 0;
}
inline bool uart_overflow(void) {
    return uart_rx_buf.buffer_overflow;
}

/* Read one byte from the UART buffer
 * RETURNS: 
 * 	> 0 if there is no data to be read 
 * 	> 1 on succesful read
 * ACCEPTS:
 * 	> as its first argument the pointer to which the read dat will be stored
 * NOTES:
 * 	> It is up to the user to manage overflows, with the use of the provided helpers 
 * */
uint8_t uart_read_byte(uint8_t *data) {
	if (uart_rx_buf.head == uart_rx_buf.tail)
		return 0; 

	*data = uart_rx_buf.buffer[uart_rx_buf.tail];

	uart_rx_buf.tail = (uart_rx_buf.tail + 1) & UART_BUFFER_MASK;
	return 1; 
}

ISR(USART_RXC_vect) {
	uint8_t data = UDR;  
	uint8_t next_head = (uart_rx_buf.head + 1) & UART_BUFFER_MASK;

	if (next_head != uart_rx_buf.tail) {
		uart_rx_buf.buffer[uart_rx_buf.head] = data;
		uart_rx_buf.head = next_head;
	} else {
		uart_rx_buf.buffer_overflow = true;
	}
}

/* Read one byte from the UART buffer
 * RETURNS: 
 * ACCEPTS:
 * 	> as its first argument the value for the UBRR register --- calculation provided in the config.h file
 * 		>> This is not just the baud-rate!
 * NOTES:
 * 	> It is the user's responsibility to enable interrupts using the sei() function
 * 	> It is up to the user to manage overflows, with the use of the provided helpers 
 * */
void interrupt_uart_init(uint16_t ubrr) {
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)ubrr;

	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRB |= (1 << RXCIE);

	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}
#endif
