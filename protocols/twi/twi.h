#include <avr/io.h>
#include <stdint.h>

void TWI_init(void);
uint8_t TWI_start(void);
void TWI_stop(void);

uint8_t TWI_write(uint8_t data);
uint8_t TWI_read_ACK(void);
uint8_t TWI_read_NACK(void);
