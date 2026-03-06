#include "i2c_backpack.h"
#include <stdint.h>

/* [NOT-PUBLIC] Low level function writing to the PCF pack over I2C
 * ACCEPTS:
 * 	> 1-argument --- data to be sent
 * RETURNS:
 * 	> 0 --- on succes
 * 	> [non-zero] --- error code from twi driver calls
 */
static inline uint8_t pcf_write(uint8_t data) {
	uint8_t status = TWI_start();
	if (status != 0x08 && status != 0x10) return 0x09;

	status = TWI_write(LCD_ADDR << 1); 
	if (status != 0x18) return 0x18;

	status = TWI_write(data);
	if (status != 0x18) return 0x18;
	TWI_stop();
	return 0;
}

/* [NOT-PUBLIC] Low level function writing to the PCF pack over I2C
 * the function itroduces proper pauses and EN line pulses
 * ACCEPTS:
 * 	> 1-argument --- data to be sent
 * RETURNS:
 * 	> 0 --- on succes
 * 	> [non-zero] --- error code from twi driver calls
 */
static uint8_t lcd_pulse(uint8_t data) {
    uint8_t status = pcf_write(data | LCD_EN);
    if (status != 0) return status;
    _delay_us(1);
    status = pcf_write(data & ~LCD_EN);
    if (status != 0) return status;
    _delay_us(50);
    return 0;
}

static void lcd_write4(uint8_t nibble, uint8_t control) {
    uint8_t data = 0;

    data |= (nibble & 0x0F) << 4;  // D4-D7
    data |= control;
    data |= LCD_BL;

    lcd_pulse(data);
}

static void lcd_write(uint8_t value, uint8_t mode) {
    lcd_write4(value >> 4, mode);
    lcd_write4(value & 0x0F, mode);
}

void lcd_command(uint8_t cmd) {
    lcd_write(cmd, 0);
}

void lcd_data(uint8_t data) {
    lcd_write(data, LCD_RS);
}

void lcd_init(void) {
    _delay_ms(50);

    lcd_write4(0x03, 0);
    _delay_ms(5);

    lcd_write4(0x03, 0);
    _delay_us(150);

    lcd_write4(0x03, 0);
    lcd_write4(0x02, 0);  

    lcd_command(0x28);    
    lcd_command(0x0C);    
    lcd_command(0x06);    
    lcd_command(0x01);    
    _delay_ms(2);
}
