#pragma once
#define SCLDDR DDRB
#define SDADDR DDRB

#define SCLPORT PORTB
#define SDAPORT PORTB

#define SCLPIN PINB
#define SDAPIN PINB

#define SCL PB0
#define SDA PB1

#define SCL_HIGH SCLPORT |= (1<<SCL)
#define SCL_LOW SCLPORT &= ~(1<<SCL)

#define SDA_HIGH SDAPORT |= (1<<SDA)
#define SDA_LOW SDAPORT &= ~(1<<SDA)
