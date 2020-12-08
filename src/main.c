#define F_CPU 19200000UL

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

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB;

RGB leds[NUMLeds];

void LEDBit(bool Bit)
{
    if (Bit)
    {
        PORTB |= (1 << LEDPin); // set LEDPin high
        _delay_us(T1H / 4);
        PORTB &= ~(1 << LEDPin); //set LEDPin low
        //_delay_us(T1L);
    }
    else
    {
        PORTB |= (1 << LEDPin); // set LEDPin high
        _delay_us(T0H / 4);
        PORTB &= ~(1 << LEDPin); //set LEDPin low
        //_delay_us(T0L);
    }
}

void drawLEDs()
{
    for (int j = 0; j <= NUMLeds; j++)
    {
        for (int8_t i = 7; i >= 0; i--)
        {
            // LEDBit(leds[j].green & i)
            if (leds[j].green & 1 << i)
            {
                LEDBit(1);
            }
            else
            {
                LEDBit(0);
            }
        }
        for (int8_t i = 7; i >= 0; i--)
        {
            if (leds[j].red & 1 << i)
            {
                LEDBit(1);
            }
            else
            {
                LEDBit(0);
            }
        }
        for (int8_t i = 7; i >= 0; i--)
        {
            if (leds[j].blue & 1 << i)
            {
                LEDBit(1);
            }
            else
            {
                LEDBit(0);
            }
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
    _delay_ms(5);
    while (1)
    {
        setValue(rand() % 100, 0, 0, 0);
        setValue(0, rand() % 100, 0, 1);
        setValue(0, 0, rand() % 100, 2);
        setValue(rand() % 100, rand() % 100, rand() % 100, 3);
        drawLEDs();
        _delay_ms(100);
    }
    return 0;
}