#include "free_rtos_tasks.h"

SemaphoreHandle_t shGreenTsk;
SemaphoreHandle_t shRedTsk;


void vInitFreeRtosTasks(void)
{
	shGreenTsk = xSemaphoreCreateBinary();
	shRedTsk   = xSemaphoreCreateBinary();

	if (xTaskCreate(vBlinkGreenLed, "GREEN-LED-BLINK",
						512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
	{
		while(1);
	}

	if (xTaskCreate(vBlinkRedLed, "RED-LED-BLINK",
							512, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
	{
		while(1);
	}
}

void vBlinkGreenLed(void * pvParameters)
{
	long start       = 0;
	long duration_ms = 0;

	for (;;)
	{
		start = xTaskGetTickCount();

		do
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
			vTaskDelay(500);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
			vTaskDelay(500);

			duration_ms = xTaskGetTickCount() - start;

		}while(duration_ms < 5000);

		xSemaphoreGive(shGreenTsk);

		while (xSemaphoreTake(shRedTsk, portMAX_DELAY) != pdPASS);

		start = xTaskGetTickCount();

		do
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
			vTaskDelay(50);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
			vTaskDelay(50);

			duration_ms = xTaskGetTickCount() - start;

		} while(duration_ms < 10000);

		xSemaphoreGive(shGreenTsk);

		vTaskDelay(1);

	}
}

void vBlinkRedLed(void * pvParameters)
{
	long start       = 0;
	long duration_ms = 0;

	for(;;)
	{
		vTaskDelay(1);

		start = xTaskGetTickCount();

		do
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
			vTaskDelay(50);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
			vTaskDelay(50);

			duration_ms = xTaskGetTickCount() - start;

		} while (duration_ms < 10000);

		xSemaphoreGive(shRedTsk);

		start = xTaskGetTickCount();

		do
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
			vTaskDelay(500);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
			vTaskDelay(500);

			duration_ms = xTaskGetTickCount() - start;

		} while (duration_ms < 5000);

		xSemaphoreGive(shRedTsk);

		while (xSemaphoreTake(shGreenTsk, portMAX_DELAY) != pdPASS);
	}
}


