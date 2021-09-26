#include <util/delay.h>
#include <avr/io.h>

#define LED_DDR DDRD
#define LED_PORT PORTD
#define BUTTON_DDR DDRB
#define BUTTON_PORT PORTB

void num_to_gray(uint8_t num){
  uint8_t gray = num ^ (num >> 1);
  LED_PORT = gray;
}

void io_init(){
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0b11111111;
  LED_PORT &= 0b00000000;
  BUTTON_DDR &= ~_BV(PB0) & ~_BV(PB1) & ~_BV(PB2);
  BUTTON_PORT |= _BV(PB0) | _BV(PB1) | _BV(PB2);
}

int main()
{
  io_init();
  uint8_t first_button = 0;
  uint8_t second_button = 0;
  uint8_t third_button = 0;
  uint8_t num = 0;
  while(1) {
    //kolejny kod Gray
    if (!(PINB & _BV(PB0)) && !first_button){
      num++;
      first_button = 1;
    }
    else if((PINB & _BV(PB0)) && first_button){
      first_button = 0;
    }
    //poprzedni kod Gray
    if (!(PINB & _BV(PB1)) && !second_button){
      num--;
      second_button = 1;
    }
    else if((PINB & _BV(PB1)) && second_button){
      second_button = 0;
    }
    //resetowanie
    if (!(PINB & _BV(PB2)) && !third_button){
      num = 0;
      third_button = 1;
    }
    else if((PINB & _BV(PB2)) && third_button){
      third_button = 0;
    }
    //konwertowanie liczby do kodu Gray
    num_to_gray(num);
    _delay_ms(10);
  }
}
