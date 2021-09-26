#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

void adc_init(){
  ADMUX   = 0b01000000; // pomiar na pinie A0
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

void timer1_init(){
  // fast PWM non-inverting mode with prescaler 8
  // częstotliwość 16e6/[N*(1+ICR1)] = 50 Hz
  ICR1 = 39999;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS11);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}

int main(){
    adc_init();
    timer1_init();

    while(1) {
    ADCSRA |= _BV(ADSC);                   // wykonaj konwersję
    while(ADCSRA & _BV(ADSC));             // czekaj na zakończenie pomiaru
    uint32_t v = ADC;                      // wczytaj wynik
        OCR1A = ICR1 * (0.09/1023 * v + 0.03); // ustaw wypełnienie (zakres od 0.03 do 0.12)
  }
}