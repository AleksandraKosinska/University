#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

void timer1_init(){
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = 001  -- prescaler 1
  // ICR1  = 1023
  ICR1 = 1023;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}

int main(){
  adc_init();
  timer1_init();
  DDRD |= _BV(PD3) | _BV(PD4);
  
  OCR1A = ICR1;
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    if(v == 0){
      OCR1A = ICR1;
    }
    else if(v >= 512){
      PORTD &= ~_BV(PD3);
      PORTD |= _BV(PD4);
      OCR1A = (v - 512) * 2;
    }
    else{
      PORTD &= ~_BV(PD4);
      PORTD |= _BV(PD3);
      OCR1A = (v - 512) * -2;
    }
  }
}
