/* Copyright Statement:
 *
 */



#ifdef MTK_EINT_KEY_ENABLE
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <string.h>
#include <stdio.h>
#include "syslog.h"
#include <stdlib.h>
#include <assert.h>

#include "hal_log.h"
#include "task_def.h"
#include "hal_gpt.h"

#include "eint_key_custom.h"
#include "sct_key_event_internal.h"
#include "eint_key.h"

sct_eint_key_event_t sct_eint_key_event;

static void sct_eint_key_callback(bsp_eint_key_event_t event, uint8_t key_data, void *user_data)
{
	uint32_t time;

	hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &time);

	sct_eint_key_event.key_data   = key_data;
	sct_eint_key_event.state      = event;
	sct_eint_key_event.time_stamp = time;
	sct_eint_key_event.is_update  = true;
	
    sct_key_send_message(SCT_GET_KEY_DATA_EINT, NULL);
}

bool sct_eint_key_init(void)
{
	bsp_eint_key_config_t key_config;
	uint32_t debounce_time;
	

    key_config.longpress_time = sct_key_driven_signal_time;
    key_config.repeat_time    = sct_key_driven_signal_time;
    
    if (bsp_eint_key_init(&key_config) != true) {
        return false;
    }

    /*set debouce as 5ms, more sensitive*/

    #ifdef __CFW_CONFIG_SUPPORT__
	debounce_time = CFW_CFG_ITEM_VALUE(cfw_sct_key_debounce_time);
    #else
    debounce_time = SCT_KEY_DEFAULT_DEBOUNCE_TIME;
    #endif
    
    bsp_eint_key_set_debounce_time(debounce_time);

    /*register normoal keypad callback*/
    bsp_eint_key_register_callback(sct_eint_key_callback, NULL);

    bsp_eint_key_enable();
    
    return true;
}



#endif /*MTK_EINT_KEY_ENABLE*/

