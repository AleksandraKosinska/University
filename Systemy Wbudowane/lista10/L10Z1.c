#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

void adc_init(){
  ADMUX   = 0b01000000;
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

void timer1_init(){
  ICR1 = 16000 - 1;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}

int main(){
    adc_init();
    timer1_init();
    OCR1A = ICR1; // ICR1/2 wypełnienie 50%

  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while(ADCSRA & _BV(ADSC)); // czekaj na zakończenie pomiaru
    uint32_t v = ADC; // oblicz wynik
    if (v == 0) {
        OCR1A = 0;
    } else {
        OCR1A = (ICR1 / (10230/v))*10;
    }
  }
}