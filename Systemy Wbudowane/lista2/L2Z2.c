#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
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

FILE uart_file;

void io_init(){
    LED_DDR |= _BV(PD2);
    LED_PORT &= ~_BV(PD2);
    BUTTON_DDR &= ~_BV(PD4);
    BUTTON_PORT |= _BV(PD4);
}

static const int8_t len_mask = 0b00000111;
static const int8_t morse_mask = 0b00000001;

// 0 - krokpa, 1 - kreska, w odwrotnej kolejnosci (np A to ._ ale w tłumaczu to _.) 
// ostatnie 3 bity mówią o ilości znaków

static const int8_t translate[36] = {
  0b00001010, //A 0
  0b01000100, //B 1
  0b01010100, //C 2
  0b00100011, //D 3
  0b00000001, //E 4
  0b00010100, //F 5
  0b00110011, //G 6
  0b00000100, //H 7
  0b00000010, //I 8
  0b00111100, //J 9
  0b00101011, //K 10
  0b00100100, //L 11
  0b00011010, //M 12
  0b00010010, //N 13
  0b00111011, //O 14
  0b00110100, //P 15
  0b01101100, //Q 16
  0b00010011, //R 17
  0b00000011, //S 18
  0b00001001, //T 19
  0b00001011, //U 20
  0b00001100, //V 21
  0b00011011, //W 22
  0b01001100, //X 23
  0b01011100, //Y 24
  0b01100100  //Z 25
};

char buf[5] = {0};
int8_t idx = 0;

void print_morse(){
  int8_t litera = 0b00000000;
  for(uint8_t i = 0; i < idx; i++){
    if(buf[i] == 0){ //kropka
      litera = litera << 1;
    }
    else{ //kreska
      litera = litera << 1;
      litera = litera | 0b00000001;
    }
  }
  litera = litera << 3;
  litera |= idx;
  for(uint8_t i = 0; i < 25; i++){
    if(translate [i] == litera){
      printf("%c\n", i + 65);
      break;
    }
  }
  buf[0] = 0;
  buf[1] = 0;
  buf[2] = 0;
  buf[3] = 0;
  buf[4] = 0;
}


int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  io_init();
  // program testowy
  uint8_t pressed = 0;
  uint8_t notpressed = 0;
  while(1) {
    if (PIND & _BV(PD4)){
        pressed++;
        notpressed = 0;
        if(pressed > 6){ //kreska
            LED_PORT |= _BV(PD2);
        }
    }
    else{
      if (pressed > 6 && notpressed == 0){ //kreska
        buf[idx] = 1;
        idx++;
        pressed = 0;
        _delay_ms(100);
        LED_PORT &= ~_BV(PD2);
      }
      else if (pressed > 0 && notpressed == 0){ //kropka
        buf[idx] = 0;
        idx++;
        pressed = 0;
        _delay_ms(100);
      }
      if(idx == 5 || ((notpressed > 12) && (idx > 0))){ //cala litera
        print_morse();
        idx = 0;
      }
      notpressed++;
    }
    _delay_ms(100);
  }
}
