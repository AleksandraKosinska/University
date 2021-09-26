#include <util/delay.h>
#include <avr/io.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

int main()
{
  //konfigurowanie portow
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0b11111111;
  LED_PORT |= 0b11111111;
  LED_PORT ^= 0b11101111;
  while(1) {
    _delay_ms(1000);
    LED_PORT ^= 0b10010000;
    _delay_ms(1000);
    LED_PORT ^= 0b01111000;
    _delay_ms(1000);
    LED_PORT ^= 0b11111010;
    _delay_ms(1000);
    LED_PORT ^= 0b10010000;
    _delay_ms(1000);
    LED_PORT ^= 0b00001011;
    _delay_ms(1000);
    LED_PORT ^= 0b00101001;
    _delay_ms(1000);
    LED_PORT ^= 0b00010100;
    _delay_ms(1000);
    LED_PORT ^= 0b01011101;
    _delay_ms(1000);
    LED_PORT ^= 0b10111001;
    _delay_ms(1000);
    LED_PORT ^= 0b01010000;
  }
}
