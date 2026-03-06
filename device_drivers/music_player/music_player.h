#include "../../protocols/uart/uart.h"
#include <util/delay.h>
#include "stdbool.h"

#define PLAY_STATUS_ROW 2

#define DEFAULT_VOLUME 16
#define DEFAULT_EQ 2

void music_player_stop();
void music_player_pause();
void music_player_next();
void music_player_play();

void music_player_reset();

static inline void player_checksum_calc(uint8_t cmd, uint16_t arg, uint16_t* checksum);

void music_player_volume_set(uint8_t vol);
void music_player_eq_set(uint8_t eq_type);
void music_player_reset_to_defaults(void);

void music_player_set_sd();
typedef struct {
	_Bool playing;
	_Bool shuffle;
	uint8_t volume;
} music_player_t;

#define MUSIC_PLAYER_INIT {false, false, 15}

