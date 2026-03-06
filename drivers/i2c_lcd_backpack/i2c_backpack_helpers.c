#include "i2c_backpack.h"
#include <stdint.h>

/* Set cursor on a 4x20 PCF-Backpack driven LCD
 * ACCEPTS:
 * 	> 1-argument --- the row to set the cursor to row < 4
 * 	> 2-argument --- the column to set the cursor to col < 20
 * RETURNS:
 * 	> 0 --- on succes 
 * 	> 1 --- on row number being too high
 * 	> 2 --- on column number being too high
 * NOTES: 
 * 	> The validity of the row number is checked first,
 * 	   if 1 is returned, the column number could still be wrong
 */
uint8_t lcd_goto(uint8_t row, uint8_t col) {
	uint8_t addr;

	if (row > 3) return 1;
	if (col > 19) return 2;
	switch(row) {
		case 0: addr = 0x00; break;
		case 1: addr = 0x40; break;
		case 2: addr = 0x14; break;
		case 3: addr = 0x54; break;
		default: addr = 0x00;
	}

	lcd_command(0x80 | (addr + col));
	return 0;
}

void lcd_puts(char *s) {
	while (*s)
		lcd_data(*s++);
}

/* Safer version of lcd_puts, accepts a maximum number of chars to print
 * ACCEPTS:
 * 	> 1-argument --- pointer to the first character of a null terminated string to print
 * 	> 2-argument --- the maximum namber of chars to print 
 * RETURNS:
 * 	> 0 --- on succes, that is the string being printed in full and 
 *         the loop stopping on the null terminator
 * 	> 1 --- on loop braking because of count being excedeed
 * 	> 2 --- on column number being too high
 * NOTES: 
 */
uint8_t lcd_nputs(char *s, uint8_t count) {
	uint8_t idx = 0;
	while (*s) {
		if (idx >= count) return 1;
		lcd_data(*s++); 
		idx++;
	}
	return 0;
}
