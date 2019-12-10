
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "misc.h"

#include "BoardHwConfig.h"
#include "user_crc16.h"
#include "user_aes128.h"

void user_Task0(void *pvParameters);
void user_Task1(void *pvParameters);
extern	void Fun_led_init(void);
extern	void Fun_led_SetStates(uint8_t newState);
extern	void UART1_Configuration(void);

//uint8 crc_buf[16]={0};
//uint16 crc16Vuale=0;
uint32 memFree=0;

struct AES_ctx aes128_ecb;
uint8 ECB_KEY[16]={0};
//,0x02,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf};
uint8 ECB_Buf[16]={0};
	
int main()
{     

//	crc16_t crc16Struct;
//	
//	memset(crc_buf,0xab,sizeof(crc_buf));
//	crc16Vuale = calcCrc16(crc_buf,0x0,16,0xAAAb,0xcbcb,0x8005);
//	
//	memset(crc_buf,0x5a,sizeof(crc_buf));
//	crc16Struct.data=crc_buf;
//	crc16Struct.offset=0;
//	crc16Struct.len=16;
//	crc16Struct.initValue=0xAAAA;
//	crc16Struct.xoroutValue=0xcbcb;
//	crc16Struct.polyValue=0x8005;
//	crc16Vuale=xcalcCrc16(&crc16Struct);
	
	memset(ECB_KEY,0x0,16);
	memcpy(ECB_KEY,"123",3);
	AES_init_ctx(&aes128_ecb,ECB_KEY);
	memset(ECB_Buf,0x0,16);
	memcpy(ECB_Buf,"456",3);
	AES_ECB_encrypt(&aes128_ecb,ECB_Buf);
	
	Fun_led_init();
	UART1_Configuration();
	
	xTaskCreate(user_Task0,(const char *)"UART1",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+3,NULL);
	memFree = xPortGetFreeHeapSize();
	
	xTaskCreate(user_Task1,(const char *)"LED1",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+4,NULL);
	memFree = xPortGetFreeHeapSize();
	
	vTaskStartScheduler();
}

void user_Task0(void *pvParameters)
{
	while(1)
	{
		printf("Task0 Run\r\n");
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}

void user_Task1(void *pvParameters)
{
	while(1)
	{	
		Fun_led_SetStates(Bit_RESET);
		vTaskDelay(500/portTICK_RATE_MS);
		Fun_led_SetStates(Bit_SET);
		vTaskDelay(100/portTICK_RATE_MS);
	}
}
