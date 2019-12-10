/*
 *
 * user_crc16.h
 *
 *
 * 1 tab == 4 spaces!
 */


#ifndef  __USER_MISC_H__
#define  __USER_MISC_H__


#ifndef uint8
#define uint8	unsigned char 
#endif

#ifndef uint16
#define uint16	unsigned short 
#endif

#ifndef int32
#define int32	int
#endif

#ifndef uint32
#define uint32	unsigned int
#endif

typedef struct
{
	uint8 *data;
	uint32 offset;
	uint32 len;
	uint16 initValue;
	uint16 polyValue;
	uint16 xoroutValue;
}crc16_t;

extern uint16 calcCrc16(uint8 *data, uint32 offset, uint32 len, uint16 initValue,uint16 xoroutValue,uint16 polyValue);
extern uint16 xcalcCrc16(crc16_t *pCrc16Struct);

#endif
