# AVR-microHAL-AMH
A simple HAL library for AVR microcontrollers 

## Features
The HAL aims to provide quite a low-level interface with the MCU
I aim to provide many macro helpers so code-speed can be optimized
### UART
- Blocking API fot Tx and Rx
- Non-blocking API for Rx --- interrupt and Ring buffer

### TWI
- TWI (I2C) driver

### ADC
- ADC driver
- Non-blocking ADC

### Devices
- Driver for PCF-like LCD-drivers

### Onboard peripherals
- GPIO driver
- Button driver
