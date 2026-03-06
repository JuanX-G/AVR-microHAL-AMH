#include <stdint.h>
#include "twi.h"

void TWI_init(void) {
	TWSR &= ~((1<<TWPS0) | (1<<TWPS1));  
	TWBR = 32;                          
	TWCR = (1<<TWEN);
}

uint8_t TWI_start(void) {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

    while (!(TWCR & (1<<TWINT)));

    return (TWSR & 0xF8);  
}

void TWI_stop(void) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

    while (TWCR & (1<<TWSTO));  
}

uint8_t TWI_write(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);

    while (!(TWCR & (1<<TWINT)));

    return (TWSR & 0xF8);
}

uint8_t TWI_read_ACK(void) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

    while (!(TWCR & (1<<TWINT)));

    return TWDR;
}

uint8_t TWI_read_NACK(void) {
    TWCR = (1<<TWINT) | (1<<TWEN);

    while (!(TWCR & (1<<TWINT)));

    return TWDR;
}
