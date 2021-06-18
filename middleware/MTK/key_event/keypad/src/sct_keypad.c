/* Copyright Statement:
 *
 */



#ifdef MTK_KEYPAD_ENABLE
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

#include "keypad_custom.h"
#include "sct_key_event_internal.h"
#include "sct_keypad.h"

static void sct_keypad_normal_key_callback(void *parameter)
{
    sct_key_send_message(SCT_GET_KEY_DATA_KEYPAD, NULL);
}

#ifdef HAL_KEYPAD_FEATURE_POWERKEY
static void sct_keypad_powerkey_callback(void *parameter)
{
    sct_key_send_message(SCT_GET_KEY_DATA_POWERKEY,NULL);
}
#endif



bool sct_keypad_init(void)
{
    keypad_custom_event_time_t hal_event_time;
    uint32_t hal_debouce_time;

    /*init keypad and powerkey, if no powerkey ignore*/
    if(keypad_custom_init() != true){
        return false;
    }

    /*set hal driver event as driven signal, 100ms per event*/
    hal_event_time.longpress_time = sct_key_driven_signal_time;
    hal_event_time.repet_time     = sct_key_driven_signal_time;
    keypad_custom_set_event_time(&hal_event_time);

    /*set debouce as 5ms, more sensitive*/
    #ifdef __CFW_CONFIG_SUPPORT__
    hal_debouce_time = CFW_CFG_ITEM_VALUE(cfw_sct_key_debounce_time);
    #else
    hal_debouce_time = SCT_KEY_DEFAULT_DEBOUNCE_TIME;
    #endif
    hal_keypad_set_debounce(&hal_debouce_time);

    /*register normoal keypad callback*/
    hal_keypad_register_callback(sct_keypad_normal_key_callback, NULL);

    /*enable normal keypad driver*/
    hal_keypad_enable();

#ifdef HAL_KEYPAD_FEATURE_POWERKEY
    /*register powerkey callback and enable powerkey*/
    hal_keypad_powerkey_register_callback(sct_keypad_powerkey_callback, NULL);
#endif
    
    return true;
}



#endif /*MTK_KEYPAD_ENABLE*/

