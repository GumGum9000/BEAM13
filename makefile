MCU=attiny13
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

	
all:
	${CC} -mmcu=attiny13a -g -Wall -Os -o main.o main.c
	${OBJCOPY} -j .text -j .data -O ihex main.o main.hex	
	avr-size --mcu=attiny13a -C main.o

flash:
	${AVRDUDE} -p ${MCU} -c stk500v2 -P /dev/ttyUSB0 -U flash:w:main.hex:i -F

clean:
	rm -f *.o *.hex