#!/usr/bin/env fish
avr-gcc -mmcu=attiny13a -Os -c main.c -o main.o
avr-gcc main.o -o main.elf
avr-objcopy -O ihex -j .text -j .data main.elf main.hex
avr-size --mcu=attiny13a -C main.elf