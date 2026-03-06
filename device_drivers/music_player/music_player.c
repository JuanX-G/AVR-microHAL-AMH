#include "music_player.h"
#include "music_player_commands.h" /* include here to not pollute the name space */
#include <stdint.h>

void music_player_pause(void) {
	PLAYER_TX_CMD_START;
	uart_tx(PLAYER_PAUSE);
	uart_tx(PLAYER_NO_FEEDBACK);
	uart_tx(0x00);
	uart_tx(0x00);
	uart_tx(PLAYER_PAUSE_CHECKSUM_HI);
	uart_tx(PLAYER_PAUSE_CHECKSUM_LO);
	uart_tx(PLAYER_CMD_END);
}

void music_player_play(void) {
	PLAYER_TX_CMD_START;
	uart_tx(PLAYER_PLAY);
	uart_tx(PLAYER_NO_FEEDBACK);
	uart_tx(0x00);
	uart_tx(0x00);
	uart_tx(PLAYER_PLAY_CHECKSUM_HI);
	uart_tx(PLAYER_PLAY_CHECKSUM_LO);
	uart_tx(PLAYER_CMD_END);
}

void music_player_next(void) {
	PLAYER_TX_CMD_START;
	uart_tx(PLAYER_NEXT);
	uart_tx(PLAYER_NO_FEEDBACK);
	uart_tx(0x00);
	uart_tx(0x00);
	uart_tx(PLAYER_NEXT_CHECKSUM_HI);
	uart_tx(PLAYER_NEXT_CHECKSUM_LO);
	uart_tx(PLAYER_CMD_END);
}


void music_player_reset(void) {
	PLAYER_TX_CMD_START;
	uart_tx(PLAYER_RESET);
	uart_tx(PLAYER_NO_FEEDBACK);
	uart_tx(0x00);
	uart_tx(0x00);
	uart_tx(PLAYER_RESET_CHECKSUM_HI);
	uart_tx(PLAYER_RESET_CHECKSUM_LO);
	uart_tx(PLAYER_CMD_END);
}

/*	###	###	###	*/
static inline void player_checksum_calc(uint8_t cmd, uint16_t arg, uint16_t* checksum) {
	uint8_t hi = (arg >> 8) & 0xFF; 
	uint8_t lo = arg & 0xFF; 
	*checksum = 0 - (0xFF + 0x06 + cmd + 0x00 + hi + lo);
}

void music_player_volume_set(uint8_t vol) {
	uint16_t checksum = 0;
	player_checksum_calc(PLAYER_VOLUME_SET, (uint16_t) vol, &checksum);

	PLAYER_TX_CMD_START;
	uart_tx(PLAYER_VOLUME_SET);
	uart_tx(PLAYER_NO_FEEDBACK);
	uart_tx(0x00);
	uart_tx(vol);
	uart_tx((uint8_t)(checksum >> 8));
	uart_tx((uint8_t)(checksum & 0xFF));
	uart_tx(PLAYER_CMD_END);
}

void music_player_eq_set(uint8_t eq_type) {
    if (eq_type > 5) eq_type = 0; 

    uint16_t checksum = 0;
    player_checksum_calc(PLAYER_EQ_SET, (uint16_t)eq_type, &checksum);

    PLAYER_TX_CMD_START;
    uart_tx(PLAYER_EQ_SET);
    uart_tx(PLAYER_NO_FEEDBACK);
    uart_tx(0x00);     
    uart_tx(eq_type); 
    uart_tx((uint8_t)(checksum >> 8));
    uart_tx((uint8_t)(checksum & 0xFF));
    uart_tx(PLAYER_CMD_END);
}

void music_player_reset_to_defaults(void) {
	music_player_reset();
	_delay_ms(2500);
	music_player_volume_set(DEFAULT_VOLUME);
	_delay_ms(2000);
	music_player_eq_set(DEFAULT_EQ);
	_delay_ms(2000);
	music_player_next();
	_delay_ms(2000);
}

void music_player_set_sd() {
    PLAYER_TX_CMD_START;
    uart_tx(PLAYER_SELECT_SD);
    uart_tx(PLAYER_NO_FEEDBACK);
    uart_tx(0x00);     
    uart_tx(PLAYER_SELECT_SD_ARG); 
    uart_tx(PLAYER_SELECT_SD_CHECKSUM_HI);
    uart_tx(PLAYER_SELECT_SD_CHECKSUM_LO);
    uart_tx(PLAYER_CMD_END);
}
