#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>
#include <inttypes.h>

#define LED_DDR DDRB
#define LED_PORT PORTB
#define BUTTON_DDR DDRB
#define BUTTON_PORT PORTB

#define mainRULER_TASK_PRIORITY (tskIDLE_PRIORITY)

#define mainBUTTON_TASK_PRIORITY 2


static void vLedRuler(void* pvParameters);

static void vLedButton(void* pvParameters);


int main(void)
{
    // Create task.
    xTaskHandle ruler_handle;
    xTaskHandle button_handle;

    xTaskCreate(vLedRuler,
                "ruler",
                configMINIMAL_STACK_SIZE,
                NULL,
         mainRULER_TASK_PRIORITY,
        &ruler_handle);

    xTaskCreate(vLedButton,
        "button",
        configMINIMAL_STACK_SIZE,
        NULL,
        mainBUTTON_TASK_PRIORITY,
        &button_handle);

    // Start scheduler.
  vTaskStartScheduler();

    return 0;
}


void vApplicationIdleHook(void)
{

}


static void vLedRuler(void* pvParameters)
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0b11111111;
  LED_PORT |= 0b01000000;
  while(1) {
    for(int i = 0; i < 6; i++){
      LED_PORT = LED_PORT >> 1;
      _delay_ms(100);
    }
    for(int i = 0; i < 6; i++){
      LED_PORT = LED_PORT << 1;
      _delay_ms(100);
    }
  }
}


static void vLedButton(void* pvParameters)
{

    uint64_t buf[1000];
    uint16_t idx = 0;
  
    LED_DDR |= _BV(PB5);
    LED_PORT &= ~_BV(PB5);
    BUTTON_DDR &= ~_BV(PB2);
    BUTTON_PORT |= _BV(PB2);
    
    while(1)
  {
     //bufor
    if(idx >= 1000)
    {
        idx = idx - 1000;
    }
    if(buf[idx])
    {
        LED_PORT &= ~_BV(PB5);
    }
    else
    {
        LED_PORT |= _BV(PB5);
    }
    //czy guzik nacisniety
    if (!(PINB & _BV(PB2)))
    {
        buf[idx] = 1;
    }
    else 
    {
        buf[idx] = 0;
    }
    idx ++;
    
    vTaskDelay(10);
  }    
}
