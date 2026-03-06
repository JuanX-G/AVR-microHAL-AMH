SOURCE_FILES = ./protocols/*/*.c ./drivers/*/*.c ./device_drivers/*/*.c main.c

build-pack:
	avr-gcc -mmcu=atmega16 -O2 -flto -DF_CPU=8000000UL -o main.elf $(SOURCE_FILES)
	avr-objcopy -O ihex -j .text -j .data main.elf main.hex

