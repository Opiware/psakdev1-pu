/* Copyright Statement:
 *
 */

#ifndef __HAL_GDMA_INTERNAL_H__
#define __HAL_GDMA_INTERNAL_H__


#include "hal_platform.h"

#ifdef HAL_GDMA_MODULE_ENABLED
#include "hal_nvic.h"
#include "hal_nvic_internal.h"


/** @brief general dma transfer size format */
typedef enum {
    GDMA_BYTE = 0,            /**< general dma transfer size -byte format */
    GDMA_HALF_WORD = 1,       /**<general  dma transfer size -half word format */
    GDMA_WORD = 2             /**<general  dma transfer size -word  format */
} gdma_transfer_size_format_t;

#define MIN_LENGHT_VALUE 0x0001
#define MAX_LENGTH_VALUE 0x3FFFC
#define MAX_COUNT_VALUE  0xFFFF


#define INVALID_INDEX  0xff


#define GDMA_INIT  1
#define GDMA_DEINIT  0
#define GDMA_CHECK_AND_SET_BUSY(gdma_port,busy_status)  \
do{ \
    uint32_t saved_mask; \
    saved_mask = save_and_set_interrupt_mask(); \
    if(gdma_init_status[gdma_port] == GDMA_INIT){ \
        busy_status = HAL_GDMA_STATUS_ERROR; \
    } else { \
        gdma_init_status[gdma_port] = GDMA_INIT;  \
        busy_status = HAL_GDMA_STATUS_OK; \
    } \
        restore_interrupt_mask(saved_mask); \
}while(0)

#define GDMA_SET_IDLE(gdma_port)   \
do{  \
       gdma_init_status[gdma_port] = GDMA_DEINIT;  \
}while(0)

gdma_transfer_size_format_t gdma_calculate_size(
    uint32_t length,
    uint32_t *count);

#endif /*HAL_GDMA_MODULE_ENABLED*/

#endif //__HAL_GDMA_INTERNAL_H__
