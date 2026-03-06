#include <stdint.h>
#include "i2c_multi_helpers.h"
#include "i2c_send_recv.h"

unsigned char soft_i2c_send_multiple(unsigned char *dt, uint8_t count) {
	for (int i = 0; i < count; i++) {
		if (soft_i2c_send(dt[i]) != 0) return 1;
	}
	return 0;
}
