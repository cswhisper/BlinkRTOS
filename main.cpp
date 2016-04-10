#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static void TaskBlinkGreenLED(void* pvParameters);

//-----------------------------------------------------------

int main()
{
  xTaskCreate(TaskBlinkGreenLED, (const portCHAR*) "GreenLED", 256, NULL, 3, NULL);
  vTaskStartScheduler();

  for (;;)
    ;;

  return 0;
}

//-----------------------------------------------------------

// Main Green LED Flash
static void TaskBlinkGreenLED(void* pvParameters)
{
  // set pin 5 of PORTB for output
  DDRB |= _BV(DDB5);

  TickType_t xLastWakeTime = xTaskGetTickCount();
  while (true)
  {
    // LED on
    PORTB |= _BV(PORTB5);
    vTaskDelayUntil(&xLastWakeTime, (1000 / portTICK_PERIOD_MS));

    // LED off
    PORTB &= ~_BV(PORTB5);
    vTaskDelayUntil(&xLastWakeTime, (1000 / portTICK_PERIOD_MS));
  }

  vTaskDelete(NULL);
}

//-----------------------------------------------------------

void vApplicationStackOverflowHook(TaskHandle_t xTask, portCHAR* pcTaskName)
{
  // main LED on
  DDRB |= _BV(DDB5);
  PORTB |= _BV(PORTB5);

  // die
  while (true)
  {
    PORTB |= _BV(PORTB5);
    _delay_ms(250);
    PORTB &= ~_BV(PORTB5);
    _delay_ms(250);
  }
}
