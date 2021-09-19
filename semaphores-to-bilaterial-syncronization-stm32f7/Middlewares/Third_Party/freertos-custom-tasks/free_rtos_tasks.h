#ifndef THIRD_PARTY_FREERTOS_CUSTOM_TASKS_FREE_RTOS_TASKS_H_
#define THIRD_PARTY_FREERTOS_CUSTOM_TASKS_FREE_RTOS_TASKS_H_

#include "stm32f7xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void vInitFreeRtosTasks(void);

void vBlinkGreenLed(void * pvParameters);
void vBlinkRedLed(void * pvParameters);


#endif /* THIRD_PARTY_FREERTOS_CUSTOM_TASKS_FREE_RTOS_TASKS_H_ */
