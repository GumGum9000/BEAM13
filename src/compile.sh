#!/usr/bin/env fish
rm main.o main.elf main.hex
avr-gcc -mmcu=attiny13a -g -Wall -Os -o main.o main.c
#avr-gcc main.o -o main.elf
avr-objcopy -O ihex -j .text -j .data main.o main.hex
avr-size --mcu=attiny13a -C main.o
