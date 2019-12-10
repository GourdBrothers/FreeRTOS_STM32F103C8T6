/*
**
**	user_crc16.c
**
**
*/


#include "user_crc16.h"

uint16 calcCrc16(uint8 *data, uint32 offset, uint32 len, uint16 initValue,uint16 xoroutValue,uint16 polyValue)
{
 	uint16 crc= initValue;
	
	uint32 i, j;
	
	for (j=0; j < len; j++)
	{
		crc ^= ((uint16)data[offset + j])<<8;
		for ( i=0; i<8; i++)
		{
			if(crc & 0x8000)
			{
				crc <<= 1;
				crc ^= polyValue;
			}
			else
			{
				crc <<= 1;
			}
		}
	}
	
	return crc^xoroutValue;
}

uint16 xcalcCrc16(crc16_t *pCrc16Struct)
{
	uint16 crc= pCrc16Struct->initValue;
	
	uint32 i, j;
	
	for (j=0; j < pCrc16Struct->len; j++)
	{
		crc ^= ((uint16)pCrc16Struct->data[pCrc16Struct->offset + j])<<8;
		for ( i=0; i<8; i++)
		{
			if(crc & 0x8000)
			{
				crc <<= 1;
				crc ^= pCrc16Struct->polyValue;
			}
			else
			{
				crc <<= 1;
			}
		}
	}
	
	return crc^pCrc16Struct->xoroutValue;
	
}
