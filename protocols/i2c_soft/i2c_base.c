#include "i2c_m_helpers.h"
#include "i2c_base.h"

void soft_i2c_init(void) {
    SCLDDR |= (1<<SCL);
    SDADDR |= (1<<SDA);
    SCL_HIGH;
    SDA_HIGH;
}

void soft_i2c_start(void) {
    SDA_LOW;
    _delay_us(1.3);
    SCL_LOW;
    _delay_us(0.6);
}

void soft_i2c_stop(void) {
    SCL_HIGH;
    _delay_us(1.3);
    SDA_HIGH;
    _delay_us(1.3);
}
