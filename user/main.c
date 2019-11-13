
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "misc.h"

#include "stm32f10x.h"


void user_Task0(void *pvParameters);
void user_Task1(void *pvParameters);
extern	void led_init(void);
extern	void UART1_Configuration(void);

int main()
{     
	led_init();
	UART1_Configuration();
	xTaskCreate(user_Task0,(const char *)"LED0",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+3,NULL);
	xTaskCreate(user_Task1,(const char *)"LED1",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+4,NULL);
	vTaskStartScheduler();
}

void user_Task0(void *pvParameters)
{
	while(1)
	{
		printf("Tast0 Run\r\n");
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}

void user_Task1(void *pvParameters)
{
	while(1)
	{	
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		vTaskDelay(500/portTICK_RATE_MS);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		vTaskDelay(500/portTICK_RATE_MS);
	}
}
