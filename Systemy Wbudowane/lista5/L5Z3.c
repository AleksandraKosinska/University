#include <stdio.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define n 16 //ilosc pomiarow w serii

uint16_t without_noise_reduction[n];
uint16_t noise_reduction[n];
uint32_t without_noise_reduction_avg = 0;
uint32_t noise_reduction_avg = 0;
uint32_t wariancja_without = 0;
uint32_t wariancja_noise_reduction = 0;
FILE uart_file;

int uart_transmit(char data, FILE *stream)
{
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

int uart_receive(FILE *stream)
{
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

void uart_init()
{
  UBRR0 = UBRR_VALUE;
  UCSR0A = 0;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

void adc_init()
{
  ADMUX   = 0b01001110; // ref Vcc 1.1V
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  // włącz ADC
  ADCSRA |= _BV(ADEN);
}

EMPTY_INTERRUPT (ADC_vect);

void pomiar_without_noise_reduction()
{
    for(int i = 0; i < n; i++)
    {
      ADCSRA |= _BV(ADSC);
      while(ADCSRA & _BV(ADSC));
      without_noise_reduction[i] = ADC;
      without_noise_reduction_avg += ADC;
      _delay_ms(10);
    }
    without_noise_reduction_avg /= n;
}

void pomiar_with_noise_reduction()
{
  set_sleep_mode (SLEEP_MODE_ADC);
  sleep_enable();
  for(int i=0; i<n; i++)
  {
    sleep_cpu();
    noise_reduction[i] = ADC;
    noise_reduction_avg += ADC;
    _delay_ms(10);
  }
  noise_reduction_avg /= n;
  sleep_disable();
}

uint32_t pow(uint32_t num)
{
  return num*num;
}

void oblicz_wariancja_without()
{
  for(int i=0; i<n; i++)
  {
    wariancja_without += pow(noise_reduction[i]-noise_reduction_avg);
  }
  wariancja_without /= n;
}

void oblicz_wariancja_noise_reduction()
{
  for(int i=0; i<n; i++)
  {
    wariancja_noise_reduction += pow(without_noise_reduction[i]-without_noise_reduction_avg);
  }
  wariancja_noise_reduction /= n;
}

int main(){
  uart_init();
  adc_init();
  
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // odmaskuj przerwania
  ADCSRA |= _BV(ADIE);
  sei();
  
  _delay_ms(10);

  //uzupelnienie tablic pomiarow
  pomiar_without_noise_reduction();
  pomiar_with_noise_reduction();
  
  printf("noise_reduction | without_noise_reduction\r\n");
  for(int i=0; i<n; i++){
    printf("      %d       |    %d\r\n", noise_reduction[i], without_noise_reduction[i]);
  }
  printf("             average: \r\n");
  printf("      %d      ", noise_reduction_avg);
  printf(" |    %d\r\n", without_noise_reduction_avg);
  
  //liczenie wariancji
  oblicz_wariancja_without();
  oblicz_wariancja_noise_reduction();
  
  printf("            wariancje: \r\n");
  printf("      %d         |    %d\r\n", wariancja_without, wariancja_noise_reduction);
  printf("\n\n\n");


  return 0;
}
