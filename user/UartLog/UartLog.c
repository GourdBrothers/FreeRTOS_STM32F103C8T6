//
//

#include <stdio.h>

#include "stm32f10x.h"

void UART1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|	\
							RCC_APB2Periph_AFIO|	\
							RCC_APB2Periph_USART1, ENABLE  );

	/* Configure USART1 Tx (PA9) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART1 Rx (PA10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	/* Configure the USART1 synchronous paramters */
	USART_ClockInit(USART1, &USART_ClockInitStructure);
																																																																				 
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure USART1 basic and asynchronous paramters */
	USART_Init(USART1, &USART_InitStructure);
		
	/* Enable USART1 */
	USART_ClearFlag(USART1, USART_IT_RXNE);
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
		
}

#pragma import(__use_no_semihosting) 

struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;
FILE __stdin;

//int _sys_exit(int x) 
//{ 
//	x = x; 
//	return 0;
//} 

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (u8) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){};
	return (ch);
}

