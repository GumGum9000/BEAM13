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
    uint8_t red,r;
    uint8_t green,g;
    uint8_t blue,b;
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

void setValueRGB(RGB RGBVal, int pos)
{
    leds[pos].red = RGBVal.r;
    leds[pos].green = RGBVal.g;
    leds[pos].blue = RGBVal.b;
}

RGB hsv2rgb(uint8_t hue, uint8_t sat, uint8_t val) //NOT 0-255!!!
{
    double      hh, p, q, t, ff;
    long        i;
    RGB         out;

    if(sat <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = val;
        out.g = val;
        out.b = val;
        return out;
    }
    hh = hue;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = val * (1.0 - sat);
    q = val * (1.0 - (sat * ff));
    t = val * (1.0 - (sat * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = val;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = val;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = val;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = val;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = val;
        break;
    case 5:
    default:
        out.r = val;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

void LEDsOff(){
    for (int i=0;i<NUMLeds;i++){
       setValue(0, 0, 0, i); 
    }
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

void Block(uint8_t i){
    uint8_t hue;
    if(i==1){
        LEDsOff();
        setValueRGB(hsv2rgb(hue,255,255),i);
        setValueRGB(hsv2rgb(hue,255,125),i+1);
    }else if(i==NUMLeds){
        LEDsOff();
         setValueRGB(hsv2rgb(hue,255,255),i);
        setValueRGB(hsv2rgb(hue,255,125),i-1);
    }else{
        LEDsOff();
        setValueRGB(hsv2rgb(hue,255,125),i-1);
        setValueRGB(hsv2rgb(hue,255,255),i);
        setValueRGB(hsv2rgb(hue,255,125),i+1);
    }
}