#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "drivers/i2c_lcd_backpack/i2c_backpack.h"
#include "drivers/button/button.h"
#include "definitions/gpio_definitions.h"
#include "device_drivers/music_player/music_player.h"
#include "drivers/timer/timer.h"
#include "drivers/timer/delays.h"

uint8_t concat_str(const char* s1, const char* s2, char* outs, uint8_t outs_size) {
    uint8_t idx = 0;
    while (*s1) {
        if (idx >= outs_size - 1) return 1;
        outs[idx++] = *s1++;
    }

    while (*s2) {
        if (idx >= outs_size - 1) return 1;
        outs[idx++] = *s2++;
    }

    outs[idx] = '\0';
    return 0;
}

#define SETARR_AT(arr, i, c) arr[i] = c;
void draw_player_status(music_player_t* status) {
	char output_str[21] = {0};
	char vol_outs[3] = {0};
	itoa(status->volume, vol_outs, 10);
	SETARR_AT(output_str, 0, 's');
	SETARR_AT(output_str, 1, 'h');
	SETARR_AT(output_str, 2, ':');
	SETARR_AT(output_str, 3, ' ');
	SETARR_AT(output_str, 4, (status->shuffle) ? '@' : '-'); 
	SETARR_AT(output_str, 5, '|');
	SETARR_AT(output_str, 6, (status->playing) ? '>' : '#');
	SETARR_AT(output_str, 7, '|');
	SETARR_AT(output_str, 8, ' '); 
	SETARR_AT(output_str, 9, 'v'); 
	SETARR_AT(output_str, 10, 'o'); 
	SETARR_AT(output_str, 11, 'l'); 
	SETARR_AT(output_str, 12, ':');
	SETARR_AT(output_str, 13, ' ');
	SETARR_AT(output_str, 14, vol_outs[0]);
	SETARR_AT(output_str, 15, vol_outs[1]);
	SETARR_AT(output_str, 16, vol_outs[2]);
	SETARR_AT(output_str, 20, '\0');

	LCD_CLEAR_LN(PLAY_STATUS_ROW);

	lcd_goto(PLAY_STATUS_ROW, 0);
	lcd_puts(output_str);
}

int main(void) {
	DDRD |= (1 << PD5);
	_delay_ms(50);      
	TWI_init();
	lcd_init();
	lcd_goto(0, 0);

	BTN_FULL_INIT(&pause_play_btn_gpio, &pause_play_btn);
	BTN_FULL_INIT(&next_btn_gpio, &next_btn);

	lcd_goto(1, 0);
	lcd_puts("> minp3 booting...");
	music_player_t music_player = MUSIC_PLAYER_INIT;
	music_player_reset_to_defaults();
	LCD_CLEAR_LN(1);
	music_player_set_sd();
	_delay_ms(2000);
	music_player_play();
	music_player.playing = true;
	while (1) {
		button_update(&pause_play_btn);
		if (button_just_pressed(&pause_play_btn)) {
			if (music_player.playing == true) {
					music_player_pause();
					music_player.playing = false;
					draw_player_status(&music_player);
					_delay_ms(2000);
			} else {
					music_player_play();
					music_player.playing = true;
					draw_player_status(&music_player);
					_delay_ms(2000);
			}
		}
		button_update(&next_btn);
		if (button_just_pressed(&next_btn)) {
			music_player_next();
			draw_player_status(&music_player);
			_delay_ms(2000);
		}
	}
	while(1);
}

