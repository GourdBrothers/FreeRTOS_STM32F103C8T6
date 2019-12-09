#include "user_fifo.h"
#include <stdio.h>

#define FIFO_LEN (fifo->usr_len - fifo->cur_len)


//SPI_CMD spi_cmd = 0;

//uint8_t count = 0;

void user_fifo_init(user_fifo_t *fifo,  uint8_t *fifo_buf, int32_t fifo_size)
{
    fifo->buf = fifo_buf;
    fifo->size = fifo_size;
    fifo->cur_len = 0;
    fifo->usr_len = 0;
    fifo->cur_p = 0;
    fifo->usr_p = 0;
}


uint32_t user_get_fifo_len(user_fifo_t *fifo)
{
    return FIFO_LEN;
}

uint32_t user_get_fifo_rest_size(user_fifo_t *fifo)
{
    return (fifo->size - FIFO_LEN);
}

uint32_t user_peek_fifo_data(user_fifo_t *fifo, uint8_t *buf, uint32_t ptr, uint32_t len)
{
    if(ptr>FIFO_LEN)
    {
        return 0;
    }

    uint32_t peek_ptr = 0;
    uint32_t ii = 0;
    if(FIFO_LEN == fifo->size)   //如果buf已满，则让cur跳转至usr来处理
    {
       peek_ptr = fifo->usr_p + ptr;
    }
    peek_ptr = fifo->cur_p + ptr;

    if(peek_ptr >= fifo->size)
    {
        peek_ptr -= fifo->size;
    }


    for(ii=0;ii<len;ii++)
    {
         if(FIFO_LEN <= ptr+ii)
         {
             break;
         }
        buf[ii] = fifo->buf[peek_ptr ++];
        //LOG("0x%02X:", buf[ii]);
        if(peek_ptr >= fifo->size)
        {
            peek_ptr = 0;
        }
       
    }

    return ii;

}


uint32_t user_get_fifo_data(user_fifo_t *fifo, uint8_t *buf, uint32_t offset, uint32_t len)
{
    //uint8_t *buf;
    uint32_t ptr;

    // FIFO_ENTER_CRITICAL_LOCK();
    
    if(offset >= FIFO_LEN)
    {
       offset = FIFO_LEN;   //偏移；量不能超过
    }

    fifo->cur_len += offset;
    fifo->cur_p += offset;
    if(fifo->cur_p >= fifo->size)
    {
        fifo->cur_p -= fifo->size;
    }

   // LOG("%d:",fifo->len);
    for(ptr=0;ptr<len;ptr++)
    {
        if(FIFO_LEN == 0)
        {
           //fifo->cur_p = fifo->usr_p;
           break;       
        }

        if(FIFO_LEN == fifo->size)   //如果buf已满，则让cur跳转至usr来处理
        {
            fifo->cur_p = fifo->usr_p;
        }

        buf[ptr] = fifo->buf[fifo->cur_p++];
        
        //LOG("%02X ",test_byte);
        fifo->cur_len ++;

        if(fifo->cur_p >= fifo->size)
        {
            fifo->cur_p = 0;
        }
       
    }

    // FIFO_EXIT_CRITICAL_LOCK();

    return ptr;
}


int user_set_fifo_data(user_fifo_t *fifo, uint8_t* buf,uint32_t len)
{
    int ptr;

    for(ptr=0;ptr<len;ptr++)
    {

        if(FIFO_LEN < fifo->size)   //大于等于fifo size 则不增加
            fifo->usr_len ++;

        //fifo->buf[fifo->usr_p++] = *(buf + ptr);
        fifo->buf[fifo->usr_p++] = buf[ptr];
        if(fifo->usr_p >= fifo->size)
        {
            fifo->usr_p = 0;
        }
        
    }
    return len;
}

void user_clear_fifo(user_fifo_t *fifo)
{
    fifo->usr_p = fifo->cur_p ; 
    // fifo->len = 0;
    fifo->cur_len = 0;
    fifo->usr_len = 0;
}
