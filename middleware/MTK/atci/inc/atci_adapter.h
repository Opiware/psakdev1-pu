/* Copyright Statement:
 *
 */

#ifndef ATCI_ADPT_H
#define ATCI_ADPT_H
#include "atci.h"




/*--- Function ---*/
/* related with OS platform */
extern void*    atci_mem_alloc(uint32_t size);
extern void     atci_mem_free(void *buf);
extern uint32_t atci_mutex_create(void);
extern uint32_t atci_mutex_lock(uint32_t mutex_id);
extern uint32_t atci_mutex_unlock(uint32_t mutex_id);
extern uint32_t atci_queue_create(uint32_t queue_length,uint32_t item_size);
extern int32_t  atci_queue_receive_no_wait(uint32_t q_id, void* data);
int32_t atci_queue_receive_wait(uint32_t q_id, void* data, uint32_t delay_time);
extern uint16_t atci_queue_get_item_num(uint32_t q_id);
extern atci_status_t atci_queue_send(uint32_t q_id, void* data);
extern atci_status_t atci_queue_send_from_isr(uint32_t q_id, void* data);
extern uint32_t atci_semaphore_create( uint32_t uxMaxCount, uint32_t uxInitialCount);
extern atci_status_t atci_semaphore_give(uint32_t semaphore_id);
extern uint32_t atci_semaphore_take(uint32_t semaphore_id);



#endif
