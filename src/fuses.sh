#!/usr/bin/env fish
avrdude -c stk500v2 -p t13 -P /dev/ttyUSB0 -U lfuse:w:0x6A:m
avrdude -c stk500v2 -p t13 -P /dev/ttyUSB0 -U hfuse:w:0xFF:m
avrdude -c stk500v2 -p t13 -P /dev/ttyUSB0 -U lock:w:0xFF:m