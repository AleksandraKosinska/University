#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

int main() {
    DDRD |= _BV(PD2);
    adc_init();
    while (1) {
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
        uint8_t led = v >> 2;
        for (int8_t i = 0; i < 5; i++) {
            PORTD &= ~_BV(PD2);
            for(uint16_t j = 0; j*((j+10)/9) < led*(led/9); j++){
              _delay_us(1);
            } 
            PORTD |= _BV(PD2);
        }
    }
}
