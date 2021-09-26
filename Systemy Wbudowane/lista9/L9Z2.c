#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

void display_status(uint8_t status){
  LCD_GoTo(0, 0);
  LCD_Clear();
  for(uint8_t i = 0; i < status/5; i++){
    LCD_WriteData(255);
  }
  status = status % 5;
  if(status > 0){
    LCD_WriteData(status);
  }
}

int main()
{
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();

  //wlasne znaki
  LCD_WriteCommand(0x40);
  for(uint8_t i = 0; i < 5; i++){
    for(uint8_t j = 0; j < 8; j++){
      char tab = 0b10000;
      for(uint8_t k = 1; k <= i; k++){
        tab += 0b10000 >> k;
      }
      LCD_WriteData(tab);
    }
  }
  uint8_t status = 0;
  while(1) {
    display_status(status);
    _delay_ms(100);
    if(status >= 80){
      status = 0;
    }
    else{
      status += 1;
    }
  }
}

