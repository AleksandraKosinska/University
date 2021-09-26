#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "hd44780.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik
  UCSR0B = _BV(RXEN0) | _BV(RXCIE0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// obsluga przewania recieve
ISR(USART_RX_vect)
{
    static uint8_t i = 0;
    static char buffer[16];
    buffer[16] = '\0';
    buffer[i] = UDR0;
    if(buffer[i] == '\r')
    {
        buffer[i] = '\0';
        LCD_Clear();
        LCD_GoTo(0, 0);
        printf("%s", buffer);
        LCD_GoTo(0, 1);
        i = -1;
    }
    else
    {
        LCD_WriteData(buffer[i]);
    }
    i += 1;
    if(i == 16)
    {
        LCD_Clear();
        LCD_GoTo(0, 1);
        i = 0;
    }
    buffer[i] = '\0';  
}

int hd44780_transmit(char data, FILE *stream) {
    LCD_WriteData(data);
    return 0;
}

FILE hd44780_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // odmaskuj przerwania
  sei();
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;
  LCD_GoTo(0, 1);
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
  while(1) {
    sleep_cpu();
  }
}