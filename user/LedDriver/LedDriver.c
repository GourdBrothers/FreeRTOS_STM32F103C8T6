

/**
*** Board: maple mini
*** LED		:	PB1, when set high, led will light
***	USB_DISC:	PB9, when set high, USB DP+ pull high
***	BUTTON	:	
*/

#include "stm32f10x.h"
#include "BoardHwConfig.h"

void Fun_led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED_RCC_CLK,ENABLE);

	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin	= LED_PIN;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_2MHz;
	
	GPIO_Init(LED_GPIO,&GPIO_InitStruct);
	GPIO_ResetBits(LED_GPIO,LED_PIN);
}

void Fun_led_SetStates(uint8_t newState)
{
	if(newState!=0){
		GPIO_SetBits(LED_GPIO,LED_PIN);
	}
	else{
		GPIO_ResetBits(LED_GPIO,LED_PIN);
	}
}
