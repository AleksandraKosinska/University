#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED_DDR DDRD
#define LED_PORT PORTD
#define BUTTON_DDR DDRD
#define BUTTON_PORT PORTD

// inicjalizacja UART
void uart_init()
{
    // ustaw baudrate
    UBRR0 = UBRR_VALUE;
    // wyczyść rejestr UCSR0A
    UCSR0A = 0;
    // włącz odbiornik i nadajnik
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    // ustaw format 8n1
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
    // czekaj aż transmiter gotowy
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = data;
    return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
    // czekaj aż znak dostępny
    while (!(UCSR0A & _BV(RXC0)));
    return UDR0;
}

void timer0_init()
{
    TCCR0B |= _BV(CS01) | _BV(CS00); //clk /64 (From prescaler)
    TCCR0A |= _BV(WGM01); //CTC OCRA Immediate MAX
    TIMSK0 |= _BV(OCIE0A); //Timer/Counter0 Output Compare Match A Interrupt Enable
    OCR0A = 124;
}

uint8_t buf[1000];
volatile uint16_t idx = 0;

ISR(TIMER0_COMPA_vect)
{
    //bufor
    if(idx >= 1000)
    {
        idx = idx - 1000;
    }
    if(buf[idx])
    {
        LED_PORT &= ~_BV(PD2);
    }
    else
    {
        LED_PORT |= _BV(PD2);
    }
    //czy guzik nacisniety
    if (!(PIND & _BV(PD4)))
    {
        buf[idx] = 1;
    }
    else 
    {
        buf[idx] = 0;
    }
    idx ++;
}


void io_init()
{
    LED_DDR |= _BV(PD2);
    LED_PORT &= ~_BV(PD2);
    BUTTON_DDR &= ~_BV(PD4);
    BUTTON_PORT |= _BV(PD4);
}

FILE uart_file;

int main(){
  for(int i=0; i<1000; i++)
  {
    buf[i] = 0;
  }
  timer0_init();
  uart_init();
  io_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_IDLE);
  // odmaskuj przerwania
  sei();

  while(1) {
    sleep_mode();
  }
}
