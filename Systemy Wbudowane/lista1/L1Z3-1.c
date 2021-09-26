#include <util/delay.h>
#include <avr/io.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

int main()
{
  //konfigurowanie portow
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0b11111111;
  LED_PORT |= 0b01000000;
  while(1) {
    for(int i = 0; i < 6; i++){
      LED_PORT = LED_PORT >> 1;
      _delay_ms(100);
    }
    for(int i = 0; i < 6; i++){
      LED_PORT = LED_PORT << 1;
      _delay_ms(100);
    }
  }
}
