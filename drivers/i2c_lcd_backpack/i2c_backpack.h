#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "../../protocols/twi/twi.h"

#define LCD_ADDR 0x27

#define LCD_RS  (1<<0)
#define LCD_RW  (1<<1)
#define LCD_EN  (1<<2)
#define LCD_BL  (1<<3)

void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_init(void);

uint8_t lcd_goto(uint8_t row, uint8_t col);
void lcd_puts(char *s);
uint8_t lcd_nputs(char *s, uint8_t count);

#define LCD_CLEAR_LN(l)  do { \
	lcd_goto(l, 0); \
	lcd_puts("                    \0");  \
	} while (0);
