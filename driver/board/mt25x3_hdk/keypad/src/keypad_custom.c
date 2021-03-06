/* Copyright Statement:
 *
 */

#include "hal_keypad.h"

#ifdef HAL_KEYPAD_MODULE_ENABLED
#include "hal_gpio.h"
#include "hal_log.h"
#include "hal_keypad_internal.h"
#include "hal_keypad_powerkey_internal.h"
#include "hal_keypad_table.h"
#include "keypad_custom.h"
#include "keypad_custom_config.h"
#include "ept_keypad_drv.h"

const uint8_t   custom_key_data[32]    = {KEYPAD_MAPPING};      //normal keypad data
const uint32_t  custom_col_and_row_sel = DRV_KBD_COL_ROW_SEL;   //col and row selection
const uint32_t  custom_powerkey_data   = POWERKEY_POSITION;     //powerkey data


extern const char HAL_KEYPAD_COL2_PIN ;
extern const char HAL_KEYPAD_COL1_PIN ;
extern const char HAL_KEYPAD_COL0_PIN ;
extern const char HAL_KEYPAD_ROW2_PIN ;
extern const char HAL_KEYPAD_ROW1_PIN ;
extern const char HAL_KEYPAD_ROW0_PIN ;

#ifdef __DOUBLE_KEYPAD__
const hal_keypad_mode_t keypad_mode   = HAL_KEYPAD_MODE_DOUBLE_KEY;
#else
const hal_keypad_mode_t keypad_mode   = HAL_KEYPAD_MODE_SINGLE_KEY;
#endif /*__DOUBLE_KEYPAD__*/

bool keypad_custom_normal_init(void)
{

    hal_keypad_status_t ret;
    hal_keypad_config_t keypad_config;

    keypad_config.debounce              = HAL_KEYPAD_DEBOUNCE_TIME;             /*set to 16ms debounce*/
    keypad_config.key_map.row_bitmap    = (custom_col_and_row_sel & 0x1f);      /*set row*/
    keypad_config.key_map.column_bitmap = ((custom_col_and_row_sel >> 6) & 0x1f); /*set col*/
    keypad_config.mode                  = keypad_mode;
    keypad_config.repeat_time           = HAL_KEYPAD_REPEAT_TIME;
    keypad_config.longpress_time        = HAL_KEYPAD_LONGPRESS_TIME;

    ret = hal_keypad_init(&keypad_config);
    if (ret != HAL_KEYPAD_STATUS_OK) {
        log_hal_warning("[keypad]normal keypad custom initial fail\r\n");
        return false;
    } else {
        return true;
    }
}

#ifdef HAL_KEYPAD_FEATURE_POWERKEY
bool keypad_custom_powerkey_init(void)
{
    hal_keypad_status_t ret;
    uint32_t powerkey_data;


    powerkey_data = custom_powerkey_data;

    powerkey_context.repeat_time     = HAL_POWERKEY_REPEAT_TIME;
    powerkey_context.longpress_time  = HAL_POWERKEY_LONGPRESS_TIME;


    //fill powerkey data
    ret =  hal_keypad_powerkey_init(powerkey_data);

    if (ret != HAL_KEYPAD_STATUS_OK) {
        log_hal_warning("[keypad]powerkey custom initial fail\r\n");
        return false;
    } else {

        return true;
    }

}
#endif

bool keypad_custom_init(void)
{
    if (keypad_custom_normal_init() != true) {          /*init keypad*/
        return false;
    }

#ifdef HAL_KEYPAD_FEATURE_POWERKEY
    if (keypad_custom_powerkey_init() != true) {        /*init powerkey*/
        return false;
    }
#endif

    return true;
}


bool keypad_custom_deinit(void)
{
    if (hal_keypad_deinit() != HAL_KEYPAD_STATUS_OK) {              /*deinit keypad*/
        return false;
    }

#ifdef HAL_KEYPAD_FEATURE_POWERKEY
    if (hal_keypad_powerkey_deinit() != HAL_KEYPAD_STATUS_OK) {     /*deinit powerkey*/
        return false;
    }
#endif

    return true;
}

bool keypad_custom_set_event_time(keypad_custom_event_time_t* event_time)
{
    if (event_time == NULL) {
        return false;
    }
#ifdef HAL_KEYPAD_FEATURE_POWERKEY	
    powerkey_context.repeat_time    = event_time->repet_time;
    powerkey_context.longpress_time = event_time->longpress_time;
#endif

    keypad_context.repeat_time      = event_time->repet_time;
    keypad_context.longpress_time   = event_time->longpress_time;   

    return true;
}


uint8_t keypad_custom_translate_keydata(uint8_t key_position)
{
    return  custom_key_data[key_position];
}

#endif /*HAL_KEYPAD_MODULE_ENABLED*/

