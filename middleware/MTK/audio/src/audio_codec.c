/* Copyright Statement:
 *
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "audio_codec.h"
#include <stdint.h>
#include <string.h>

#include "hal_log.h"
#include "task_def.h"

QueueHandle_t audio_codec_queue_handle = NULL;
TaskHandle_t audio_codec_task_handle = NULL;
SemaphoreHandle_t audio_codec_semaphore_handle = NULL;
audio_codec_internal_callback_t audio_codec_queue_cb_array[AUDIO_CODEC_MAX_FUNCTIONS];
audio_codec_media_handle_t *audio_codec_queue_handle_array[AUDIO_CODEC_MAX_FUNCTIONS];

static void audio_codec_task_main(void *arg)
{
    audio_codec_queue_event_t event;

    while (1) {
        if (xQueueReceive(audio_codec_queue_handle, &event, portMAX_DELAY)) {
            // log_hal_info("uxQueueSpacesAvailable %d \n", uxQueueSpacesAvailable(audio_codec_queue_handle));
            audio_codec_media_handle_t *handle = event.handle;
            uint32_t id_idx;
            for (id_idx = 0; id_idx < AUDIO_CODEC_MAX_FUNCTIONS; id_idx++) {
                if (audio_codec_queue_handle_array[id_idx] == handle) {
                    audio_codec_queue_cb_array[id_idx](handle, event.parameter);
                    break;
                }
            }
        }
    }
}


audio_codec_status_t audio_codec_event_register_callback(audio_codec_media_handle_t *handle, audio_codec_internal_callback_t callback)
{
    {   /* temp */
        if ( audio_codec_queue_handle == NULL ) {
            audio_codec_queue_handle = xQueueCreate(AUDIO_CODEC_QUEUE_LENGTH, sizeof(audio_codec_queue_event_t));
            {   /* Initialize queue registration */
                uint32_t id_idx;
                for (id_idx = 0; id_idx < AUDIO_CODEC_MAX_FUNCTIONS; id_idx++) {
                    audio_codec_queue_handle_array[id_idx] = NULL;
                }
            }

            xTaskCreate(audio_codec_task_main,
                        AUDIO_CODEC_TASK_NAME, AUDIO_CODEC_TASK_STACKSIZE / sizeof(StackType_t), NULL, AUDIO_CODEC_TASK_PRIO, &audio_codec_task_handle);
        }
    }
    uint32_t id_idx;
    audio_codec_status_t status = AUDIO_CODEC_RETURN_ERROR;
    for (id_idx = 0; id_idx < AUDIO_CODEC_MAX_FUNCTIONS; id_idx++) {
        if (audio_codec_queue_handle_array[id_idx] == NULL) {
            audio_codec_queue_handle_array[id_idx] = handle;
            audio_codec_queue_cb_array[id_idx] = callback;
            status = AUDIO_CODEC_RETURN_OK;
            break;
        }
    }
    return status;
}

audio_codec_status_t audio_codec_event_deregister_callback(audio_codec_media_handle_t *handle)
{
    uint32_t id_idx;
    audio_codec_status_t status = AUDIO_CODEC_RETURN_ERROR;
    for (id_idx = 0; id_idx < AUDIO_CODEC_MAX_FUNCTIONS; id_idx++) {
        if (audio_codec_queue_handle_array[id_idx] == handle) {
            audio_codec_queue_handle_array[id_idx] = NULL;
            status = AUDIO_CODEC_RETURN_OK;
            break;
        }
    }

    {   /* temp */
        bool needDelete = true;
        for (id_idx = 0; id_idx < AUDIO_CODEC_MAX_FUNCTIONS; id_idx++) {
            if (audio_codec_queue_handle_array[id_idx] != NULL) {
                needDelete = false;
                break;
            }
        }
        if ( needDelete && audio_codec_task_handle != NULL) {
            vTaskDelete(audio_codec_task_handle);
            audio_codec_task_handle = NULL;
        }

        if ( needDelete && audio_codec_queue_handle != NULL) {
            vQueueDelete(audio_codec_queue_handle);
            audio_codec_queue_handle = NULL;
        }
    }
    return status;
}

audio_codec_status_t audio_codec_event_send_from_isr (audio_codec_media_handle_t *handle, void *parameter)
{
    // log_hal_info("audio_codec_event_send_from_isr + \n");
    audio_codec_status_t status = AUDIO_CODEC_RETURN_OK;
    audio_codec_queue_event_t event;
    event.handle    = handle;
    event.parameter = parameter;
    if (xQueueSendFromISR(audio_codec_queue_handle, &event, 0) != pdPASS) {
        status = AUDIO_CODEC_RETURN_ERROR;
    }
    // log_hal_info("uxQueueSpacesAvailable %d \n", uxQueueSpacesAvailable(audio_codec_queue_handle));
    return status;
}

/* global semaphore to protect play/stop/close/pause/resume flow */
audio_codec_status_t audio_codec_mutex_create(void)
{
    audio_codec_status_t status = AUDIO_CODEC_RETURN_OK;

    if ( audio_codec_semaphore_handle == NULL ) {
        audio_codec_semaphore_handle = xSemaphoreCreateMutex();
    }
    else {
        status = AUDIO_CODEC_RETURN_ERROR;
    }

    return status;
}

audio_codec_status_t audio_codec_mutex_delete(void)
{
    audio_codec_status_t status = AUDIO_CODEC_RETURN_OK;

    if ( audio_codec_semaphore_handle != NULL ) {
         vSemaphoreDelete(audio_codec_semaphore_handle);
    }
    else {
        status = AUDIO_CODEC_RETURN_ERROR;
    }

    return status;
}

audio_codec_status_t audio_codec_mutex_lock(void)
{
    audio_codec_status_t status = AUDIO_CODEC_RETURN_OK;

    if ( audio_codec_semaphore_handle != NULL ) {
        log_hal_info("[Audio Codec] audio_codec_mutex_lock() +\r\n");
        xSemaphoreTake(audio_codec_semaphore_handle, portMAX_DELAY);
        log_hal_info("[Audio Codec] audio_codec_mutex_lock() -\r\n");
    }
    else {
        status = AUDIO_CODEC_RETURN_ERROR;
    }

    return status;
}

audio_codec_status_t audio_codec_mutex_unlock(void)
{
    audio_codec_status_t status = AUDIO_CODEC_RETURN_OK;

    if ( audio_codec_semaphore_handle != NULL ) {
        log_hal_info("[Audio Codec] audio_codec_mutex_unlock()\r\n");
        xSemaphoreGive(audio_codec_semaphore_handle);
    }
    else {
        status = AUDIO_CODEC_RETURN_ERROR;
    }

    return status;
}
