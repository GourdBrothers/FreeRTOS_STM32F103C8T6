#ifndef _USER_FIFO_H_
#define _USER_FIFO_H_


#include "types.h"
#include "hal_mcu.h"

#define FIFO_ENTER_CRITICAL_LOCK() HAL_ENTER_CRITICAL_SECTION()
#define FIFO_EXIT_CRITICAL_LOCK() HAL_EXIT_CRITICAL_SECTION()

typedef struct{
    uint32_t size;
    uint32_t cur_len;
    uint32_t usr_len;
    uint32_t cur_p; 
    uint32_t usr_p; //move ptr
    uint8_t*  buf;
}user_fifo_t;


extern void user_fifo_init(user_fifo_t *fifo, uint8_t *fifo_buf, int32_t fifo_size);
extern uint32_t user_get_fifo_len(user_fifo_t *fifo);
extern uint32_t user_get_fifo_rest_size(user_fifo_t *fifo);
extern uint32_t user_peek_fifo_data(user_fifo_t *fifo, uint8_t *buf, uint32_t ptr, uint32_t len);
extern uint32_t user_get_fifo_data(user_fifo_t *fifo, uint8_t *buf, uint32_t offset, uint32_t len);
extern int user_set_fifo_data(user_fifo_t *fifo, uint8_t* buf,uint32_t len);
extern void user_clear_fifo(user_fifo_t *fifo);

#endif

