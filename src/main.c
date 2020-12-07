#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>

#define T1H 0.8
#define T1L 0.45

#define T0H 0.4
#define T0L 0.85

#define reset 50

#define LEDPin PB0
#define NUMLeds 4

struct RGB
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct RGB leds[NUMLeds];


void LEDBit(bool Bit)
{
    if (Bit)
    {
        PORTB |= (1 << LEDPin); // set LEDPin high
        _delay_us(T1H);
        PORTB &= ~(1 << LEDPin); //set LEDPin low
        _delay_us(T1L);
    }
    else
    {
        PORTB |= (1 << LEDPin); // set LEDPin high
        _delay_us(T0H);
        PORTB &= ~(1 << LEDPin); //set LEDPin low
        _delay_us(T0L);
    }
}

void drawLEDs()
{
    for (int j = 0; j <= NUMLeds; j++)
    {
        for (int8_t i = 7; i >= 0; i--)
        {
            LEDBit(bit_is_set(leds[j].green, i));
        }
        for (int8_t i = 7; i >= 0; i--)
        {
            LEDBit(bit_is_set(leds[j].red, i));
        }
        for (int8_t i = 7; i >= 0; i--)
        {
            LEDBit(bit_is_set(leds[j].blue, i));
        }
    }
}
void setValue(uint8_t r, uint8_t g, uint8_t b, int pos)
{
    leds[pos].red = r;
    leds[pos].green = g;
    leds[pos].blue = b;
}

int main()
{
    DDRB |= (1 << LEDPin); // Set LEDPin as output
    /*
    setValue(255, 0, 0, 1);
    setValue(0, 255, 0, 2);
    setValue(0, 0, 255, 3);
    setValue(255, 255, 255, 4);

    drawLEDs();
    */
    while (1)
    {
        PORTB |= (1 << LEDPin); //PB0 im PORTB setzen
        _delay_(1000);
    }
    return 0;
}