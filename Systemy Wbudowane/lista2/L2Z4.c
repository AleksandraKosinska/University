#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>


uint8_t liczby[10] = {
    0b11000000,
    0b11111001,
    0b10100100,
    0b10110000,
    0b10011001,
    0b10010010,
    0b10000010,
    0b11111000,
    0b10000000,
    0b10010000
};


void show(int i, int j)
{
    for(int t=0; t<50; t++)
    {
        PORTC &= ~_BV(PC0);
        PORTC |= _BV(PC1);
        PORTD = liczby[i];
        _delay_ms(10);
        PORTC &= ~_BV(PC1);
        PORTC |= _BV(PC0);
        PORTD = liczby[j];
        _delay_ms(10);
    }
}

int main()
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    DDRD = 0b11111111;
    DDRC |= _BV(PC0) | _BV(PC1);
    while(1)
    {
        for(int i = 0; i < 6; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                show(i, j);
            }
        }
    }
    return 0;
}