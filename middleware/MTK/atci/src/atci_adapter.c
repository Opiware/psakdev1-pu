/* Copyright Statement:
 *
 */

/* Common Internal Adapter API */
#include "atci_adapter.h"
/* Free RTOS */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "hal_nvic_internal.h"


uint32_t atci_queue_create(uint32_t queue_length,uint32_t item_size)
{
    QueueHandle_t q_id = NULL;

    q_id = xQueueCreate(queue_length, item_size);
    return (uint32_t)q_id;
}

atci_status_t atci_queue_send(uint32_t q_id, void* data)
{
    BaseType_t ret = 0;
	BaseType_t xHigherPriorityTaskWoken;

	if ( 0 == q_id )
		return ATCI_STATUS_ERROR;
		
//	if( 0 == hal_nvic_query_exception_number())
	if( 0 == HAL_NVIC_QUERY_EXCEPTION_NUMBER)
    	ret = xQueueSend((QueueHandle_t)q_id, data, 0);
	else 
		ret = xQueueSendFromISR((QueueHandle_t)q_id, data, &xHigherPriorityTaskWoken);
		
    if (pdFAIL != ret) {
        return ATCI_STATUS_OK;
    } else {
        return ATCI_STATUS_ERROR;
    }
}


atci_status_t atci_queue_send_from_isr(uint32_t q_id, void* data) 
{
    BaseType_t ret = 0;
    BaseType_t xHigherPriorityTaskWoken;

    ret = xQueueSendFromISR((QueueHandle_t)q_id, data, &xHigherPriorityTaskWoken);
    if (pdPASS == ret) {
        return ATCI_STATUS_OK;
    } else {
        return ATCI_STATUS_ERROR;
    }
}


int32_t atci_queue_receive_no_wait(uint32_t q_id, void* data)
{
    BaseType_t ret = -1;
	if ( 0 == q_id )
		return 0;
    ret = xQueueReceive((QueueHandle_t)q_id, data, 0);
    return (int32_t)ret;
}

int32_t atci_queue_receive_wait(uint32_t q_id, void* data, uint32_t delay_time)
{
    BaseType_t ret = -1;
    ret = xQueueReceive((QueueHandle_t)q_id, data, delay_time / portTICK_PERIOD_MS);
    return (int32_t)ret;
}

uint16_t atci_queue_get_item_num(uint32_t q_id)
{
    uint16_t queue_item_num = 0;
	if ( 0 == q_id )
		return 0;
	
    queue_item_num = (uint16_t)uxQueueMessagesWaiting((QueueHandle_t) q_id);
    return queue_item_num;
}

uint32_t atci_mutex_create(void)
{
    return (uint32_t)xSemaphoreCreateMutex();
}

uint32_t atci_mutex_lock(uint32_t mutex_id)
{
	if(mutex_id == 0)
		return 0;
    return (uint32_t)xSemaphoreTake((SemaphoreHandle_t)mutex_id, portMAX_DELAY);
}

uint32_t atci_mutex_unlock(uint32_t mutex_id)
{
	if(mutex_id == 0)
		return 0;

    return (uint32_t)xSemaphoreGive((SemaphoreHandle_t)mutex_id);
}

void* atci_mem_alloc(uint32_t size)
{
    void *pvReturn = NULL;
    uint32_t  free_size;
    free_size = xPortGetFreeHeapSize();
    if (free_size > size) {
        pvReturn = pvPortMalloc(size);
    }

    return pvReturn;
}

void atci_mem_free(void *buf)
{
    if (buf != NULL) {
        vPortFree(buf);
    }
}

uint32_t atci_semaphore_create( uint32_t uxMaxCount, uint32_t uxInitialCount)
{
    return (uint32_t)xSemaphoreCreateCounting((UBaseType_t)uxMaxCount, (UBaseType_t)uxInitialCount);
}

uint32_t atci_semaphore_take(uint32_t semaphore_id)
{
	if ( NULL == (void *)semaphore_id )
		return 0;

    return (uint32_t)xSemaphoreTake((SemaphoreHandle_t)semaphore_id, portMAX_DELAY);
}

atci_status_t atci_semaphore_give(uint32_t semaphore_id)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if ( NULL == (void *)semaphore_id )
		return ATCI_STATUS_ERROR;
    //return (uint32_t)xSemaphoreGive((SemaphoreHandle_t)mutex_id);
    xSemaphoreGiveFromISR(semaphore_id, &xHigherPriorityTaskWoken);
	
	if(xHigherPriorityTaskWoken == pdTRUE) {
		return ATCI_STATUS_OK;

	} else {
		return ATCI_STATUS_ERROR;
	}
}


