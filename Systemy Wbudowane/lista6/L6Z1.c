#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)

void uart_init(){
  UBRR0 = UBRR_VALUE;
  UCSR0A = 0;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

int uart_transmit(char data, FILE *stream){
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

int uart_receive(FILE *stream){
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

void timer1_init(){
  TCCR1B = _BV(CS10);
}

FILE uart_file;

int main(){

  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  timer1_init();

  uint16_t t1, t2;
  
  // int8_t
  volatile int8_t n8=4;
  volatile int8_t m8=16;
  volatile int8_t w8;
  
  printf("int8_t\r\n");
  
  TCNT1 = 0;
  w8 = n8+m8;
  t2 = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu8"\r\n\n", w8);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w8 = n8*m8;
  t2 = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu8"\r\n\n", w8);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w8 = m8/n8;
  t2 = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu8"\r\n\n", w8);
  
  // int16_t
  volatile int16_t n16=8;
  volatile int16_t m16=32;
  volatile int16_t w16;
  
  printf("\nint16_t\r\n");
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w16 = n16+m16;
  t2 = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu16"\r\n\n", w16);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w16 = n16*m16;
  t2 = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu16"\r\n\n", w16);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w16 = m16/n16;
  t2 = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu16"\r\n\n\n\n", w16);

  // int32_t
  volatile int32_t n32=16;
  volatile int32_t m32=64;
  volatile int32_t w32;
  
  printf("\nint32_t\r\n");
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w32 = n32+m32;
  t2 = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n", w32);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w32 = n32*m32;
  t2 = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n", w32);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w32 = m32/n32;
  t2 = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n\n\n", w32);
  
  // int64_t
  volatile int64_t n64=32;
  volatile int64_t m64=128;
  volatile int64_t w64;
  
  printf("\nint64_t\r\n");
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w64 = n64+m64;
  t2 = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n", w64);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w64 = n64*m64;
  t2 = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n", w64);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  w64 = m64/n64;
  t2 = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n\n\n", w64);
  
  // float
  volatile float nf=1.0;
  volatile float mf=2.0;
  volatile float wf;
  
  printf("\nfloat\r\n");
  
  TCNT1 = 0;
  //t1 = TCNT1;
  wf = nf+mf;
  t2 = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n", wf);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  wf = nf*mf;
  t2 = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n", wf);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  wf = mf/nf;
  t2 = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n\n\n", wf);

  // double
  volatile double nd=1.0;
  volatile double md=2.0;
  volatile double wd;
  
  printf("\ndouble\r\n");
  
  TCNT1 = 0;
  //t1 = TCNT1;
  wd = nd+md;
  t2 = TCNT1;
  printf("Dodawanie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n", wd);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  wd = nd*md;
  t2 = TCNT1;
  printf("Mnożenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n", wd);
  
  TCNT1 = 0;
  //t1 = TCNT1;
  wd = md/nd;
  t2 = TCNT1;
  printf("Dzielenie: %"PRIu16" cykli\r\n", t2);
  //printf("Wynik: %"PRIu32"\r\n\n\n\n", wd);
}
