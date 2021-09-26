#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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

void timer1_init()
{
  // ustaw tryb licznika
  // WGM1  = 0000 -- normal
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
}
FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skof_1iguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj licznik
  timer1_init();
  // program
  //---------------------------------
  uint16_t time;
  //---------------------------------
  volatile int8_t i8_1 = 3;
  volatile int8_t i8_2 = 69;
  volatile int8_t i8_3;

  printf("\nint8_t\r\n");


  TCNT1 = 0;
  i8_3 = i8_1 + i8_2;
  time = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", time);

  TCNT1 = 0;
  i8_3 = i8_1 * i8_2;
  time = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  i8_3 = i8_2 / i8_1;
  time = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", time);
  
  //---------------------------------
  volatile int16_t i16_1 = 3;
  volatile int16_t i16_2 = 69;
  volatile int16_t i16_3;
  
  printf("\nint16_t\r\n");
  
  TCNT1 = 0;
  i16_3 = i16_1 + i16_2;
  time = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  i16_3 = i16_1 * i16_2;
  time = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  i16_3 = i16_2 / i16_1;
  time = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", time);

  //---------------------------------
  volatile int32_t i32_1 = 3;
  volatile int32_t i32_2 = 69;
  volatile int32_t i32_3;
  
  printf("\nint32_t\r\n");
  
  TCNT1 = 0;
  i32_3 = i32_1 + i32_2;
  time = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  i32_3 = i32_1 * i32_2;
  time = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  i32_3 = i32_2 / i32_1;
  time = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", time);
  
  //---------------------------------
  volatile int64_t i64_1 = 3;
  volatile int64_t i64_2 = 69;
  volatile int64_t i64_3;
  
  printf("\nint64_t\r\n");
  
  TCNT1 = 0;
  i64_3 = i64_1 + i64_2;
  time = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  i64_3 = i64_1 * i64_2;
  time = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  i64_3 = i64_2 / i64_1;
  time = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", time);
  
  //---------------------------------
  volatile float f_1 = 3.0;
  volatile float f_2 = 69.0;
  volatile float f_3;
  
  printf("\nfloat\r\n");
  
  TCNT1 = 0;
  f_3 = f_1 + f_2;
  time = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  f_3 = f_1 * f_2;
  time = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  f_3 = f_2 / f_1;
  time = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", time);

  //---------------------------------
  volatile double d_1 = 3.0;
  volatile double d_2 = 69.0;
  volatile double d_3;
  
  printf("\ndouble\r\n");
  
  TCNT1 = 0;
  d_3 = d_1 + d_2;
  time = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  d_3 = d_1 * d_2;
  time = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", time);
  
  TCNT1 = 0;
  d_3 = d_2 / d_1;
  time = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", time);
}
