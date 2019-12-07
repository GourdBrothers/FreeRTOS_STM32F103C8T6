/******************************************************
**
**	BoradHwConfig.h
**	Board: maple mini
*** 	LED		:	PB1, when set high, led will light
***		USB_DISC:	PB9, when set high, USB DP+ pull high
***		BUTTON	:   PB8, when press it, high level will on the pin
**	
*******************************************************
*/

#ifndef	__BOARD_HW_CONFIG_H__
#define __BOARD_HW_CONFIG_H__


#define	LED_RCC_CLK		RCC_APB2Periph_GPIOB
#define	LED_GPIO		GPIOB
#define	LED_PIN			GPIO_Pin_1




#endif /* __BOARD_HW_CONFIG_H__ */

