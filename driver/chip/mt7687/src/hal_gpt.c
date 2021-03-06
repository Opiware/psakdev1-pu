/* Copyright Statement:
 *
 */

#include "hal_gpt.h"

#ifdef HAL_GPT_MODULE_ENABLED
#include <string.h>
#include "timer.h"
#include "gpt.h"
#include "hal_gpt.h"
#include "hal_log.h"



typedef struct {
    hal_gpt_callback_t callback;
    void *user_data;
} hal_gpt_callback_context;

typedef struct {
    hal_gpt_running_status_t running_status;
    hal_gpt_callback_context callback_context;
    bool has_initlized;
} hal_gpt_context_t;

#define HAL_GPT_DELAY_MS_PORT   HAL_GPT_2
#define HAL_GPT_DELAY_US_PORT   HAL_GPT_4


static hal_gpt_context_t g_gpt_context[HAL_GPT_MAX];

static bool hal_gpt_is_port_valid(hal_gpt_port_t gpt_port)
{
    if ((gpt_port < HAL_GPT_MAX) && (gpt_port != HAL_GPT_DELAY_MS_PORT)) {
        return true;
    } else {
        return false;
    }
}

static uint32_t hal_gpt_translate_timeout_time(uint32_t mili_seconds)
{
    return ((uint32_t)(mili_seconds * 32 + (7 * mili_seconds) / 10 + (6 * mili_seconds) / 100 + (8 * mili_seconds) / 1000));
}

static bool hal_gpt_translate_type(hal_gpt_timer_type_t type)
{
    return HAL_GPT_TIMER_TYPE_REPEAT == type;
}

hal_gpt_status_t hal_gpt_init(hal_gpt_port_t gpt_port)
{
    if (g_gpt_context[gpt_port].has_initlized != false) {
        return HAL_GPT_STATUS_ERROR;
    }

    if (hal_gpt_is_port_valid(gpt_port) != true) {
        log_hal_error("Invalid port: %d.", gpt_port);
        return HAL_GPT_STATUS_ERROR_PORT;
    }
    memset(&g_gpt_context[gpt_port],
           0,
           sizeof(hal_gpt_context_t));

    g_gpt_context[gpt_port].has_initlized = true;

    return HAL_GPT_STATUS_OK;
}

hal_gpt_status_t hal_gpt_deinit(hal_gpt_port_t gpt_port)
{
    if (hal_gpt_is_port_valid(gpt_port) != true) {
        log_hal_error("Invalid port: %d.", gpt_port);
        return HAL_GPT_STATUS_ERROR_PORT;
    }

    if (g_gpt_context[gpt_port].running_status != HAL_GPT_STOPPED) {
        log_hal_error("Should call  port: %d.", gpt_port);
        return HAL_GPT_STATUS_ERROR;
    }

    memset(&g_gpt_context[gpt_port],
           0,
           sizeof(hal_gpt_context_t));
    g_gpt_context[gpt_port].has_initlized = false;
    return HAL_GPT_STATUS_OK;
}

hal_gpt_status_t hal_gpt_get_free_run_count(hal_gpt_clock_source_t clock_source, uint32_t *count)
{
    if (clock_source == HAL_GPT_CLOCK_SOURCE_32K) {
        if (g_gpt_context[HAL_GPT_DELAY_MS_PORT].running_status !=  HAL_GPT_RUNNING) {
            CM4_GPT2Init();
        }
        *count = get_current_count();
        g_gpt_context[HAL_GPT_2].running_status = HAL_GPT_RUNNING;
    } else if (clock_source == HAL_GPT_CLOCK_SOURCE_1M) {
        if (g_gpt_context[HAL_GPT_DELAY_US_PORT].running_status !=  HAL_GPT_RUNNING) {
            CM4_GPT4Init();
        }
        *count = get_current_gpt4_count() / (top_mcu_freq_get() / 1000000);
        g_gpt_context[HAL_GPT_4].running_status = HAL_GPT_RUNNING;
    } else if (clock_source == HAL_GPT_CLOCK_SOURCE_BUS) {
        if (g_gpt_context[HAL_GPT_DELAY_US_PORT].running_status !=  HAL_GPT_RUNNING) {
            CM4_GPT4Init();
        }
        *count = get_current_gpt4_count();
        g_gpt_context[HAL_GPT_4].running_status = HAL_GPT_RUNNING;
    }else {
        log_hal_error("Invalid parameter: %d.", clock_source);
        return HAL_GPT_STATUS_INVALID_PARAMETER;
    }

    return HAL_GPT_STATUS_OK;
}

hal_gpt_status_t hal_gpt_get_duration_count(uint32_t start_count, uint32_t end_count, uint32_t *duration_count)
{
    if (duration_count == NULL) {
        return HAL_GPT_STATUS_INVALID_PARAMETER;
    }

    if (end_count > start_count) {
        *duration_count = end_count - start_count;
    } else {

        *duration_count = (0xffffffff - (start_count - end_count)) + 1;
    }
    return HAL_GPT_STATUS_OK;
}

hal_gpt_status_t hal_gpt_get_running_status(hal_gpt_port_t gpt_port,
        hal_gpt_running_status_t *running_status)
{
    if (gpt_port >= HAL_GPT_MAX) {
        log_hal_error("Invalid hal_gpt_stop_timer to stop port: %d.", gpt_port);
        return HAL_GPT_STATUS_ERROR_PORT;
    }
    *running_status = g_gpt_context[gpt_port].running_status;
    return HAL_GPT_STATUS_OK;
}

hal_gpt_status_t hal_gpt_register_callback(hal_gpt_port_t gpt_port,
        hal_gpt_callback_t callback,
        void *user_data)
{
    if (hal_gpt_is_port_valid(gpt_port) != true) {
        log_hal_error("Invalid port: %d. Only port 0 or 1 works as timer.", gpt_port);
        return HAL_GPT_STATUS_ERROR_PORT;
    }
    if (g_gpt_context[gpt_port].has_initlized != true) {
        return HAL_GPT_STATUS_ERROR;
    }
    if (callback == NULL) {
        return HAL_GPT_STATUS_INVALID_PARAMETER;
    }
    g_gpt_context[gpt_port].callback_context.callback  = callback;
    g_gpt_context[gpt_port].callback_context.user_data = user_data;
    return HAL_GPT_STATUS_OK;
}

static void hal_gpt_callback0(void)
{
    hal_gpt_callback_context *context = &g_gpt_context[HAL_GPT_0].callback_context;
    if (NULL != context->callback) {
        context->callback(context->user_data);
    }
    g_gpt_context[HAL_GPT_0].running_status = HAL_GPT_STOPPED;
}

static void hal_gpt_callback1(void)
{
    hal_gpt_callback_context *context = &g_gpt_context[HAL_GPT_1].callback_context;
    if (NULL != context->callback) {
        context->callback(context->user_data);
    }
    g_gpt_context[HAL_GPT_1].running_status = HAL_GPT_STOPPED;
}

typedef void (*hal_gpt_internal_callback_t)(void);

static hal_gpt_internal_callback_t hal_gpt_map_callback(hal_gpt_port_t gpt_port)
{
    return (HAL_GPT_0 == gpt_port) ? hal_gpt_callback0 : hal_gpt_callback1;
}

hal_gpt_status_t hal_gpt_start_timer_ms(hal_gpt_port_t gpt_port, uint32_t timeout_time_ms, hal_gpt_timer_type_t timer_type)
{
    if (hal_gpt_is_port_valid(gpt_port) != true) {
        log_hal_error("Invalid port: %d. Only port 0 or 1 works as timer.", gpt_port);
        return HAL_GPT_STATUS_ERROR_PORT;
    }

    if (g_gpt_context[gpt_port].has_initlized != true) {
        return HAL_GPT_STATUS_ERROR;
    }

    if (timeout_time_ms > HAL_GPT_MAXIMUM_MS_TIMER_TIME) {
        return HAL_GPT_STATUS_INVALID_PARAMETER;
    }

    drvTMR_init((uint32_t)gpt_port,
                hal_gpt_translate_timeout_time(timeout_time_ms),
                hal_gpt_translate_type(timer_type),
                hal_gpt_map_callback(gpt_port));
    TMR_Start((uint32_t)gpt_port);
    g_gpt_context[gpt_port].running_status = HAL_GPT_RUNNING;
    return HAL_GPT_STATUS_OK;
}

hal_gpt_status_t hal_gpt_stop_timer(hal_gpt_port_t gpt_port)
{
    if (hal_gpt_is_port_valid(gpt_port) != true) {
        log_hal_error("Invalid port: %d. Only port 0 or 1 works as timer.", gpt_port);
        return HAL_GPT_STATUS_ERROR_PORT;
    }
    TMR_Stop((uint32_t)(gpt_port));
    g_gpt_context[gpt_port].running_status = HAL_GPT_STOPPED;
    return HAL_GPT_STATUS_OK;
}

hal_gpt_status_t hal_gpt_delay_ms(uint32_t ms)
{
    if (g_gpt_context[HAL_GPT_DELAY_MS_PORT].running_status !=  HAL_GPT_RUNNING) {
        CM4_GPT2Init();
    }
    delay_ms(ms);
    g_gpt_context[HAL_GPT_DELAY_MS_PORT].running_status = HAL_GPT_RUNNING;
    return HAL_GPT_STATUS_OK;
}

/*The max delay us time = 1/systemclock*0xffffffff */
hal_gpt_status_t hal_gpt_delay_us(uint32_t us)
{
    if (g_gpt_context[HAL_GPT_DELAY_US_PORT].running_status !=  HAL_GPT_RUNNING) {
        CM4_GPT4Init();
    }
    delay_us(us);
    g_gpt_context[HAL_GPT_DELAY_US_PORT].running_status = HAL_GPT_RUNNING;
    return HAL_GPT_STATUS_OK;
}

#endif


