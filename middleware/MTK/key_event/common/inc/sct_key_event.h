/* Copyright Statement:
 *
 */
#ifndef __SCT_KEY_EVENT_H__
#define __SCT_KEY_EVENT_H__

#include "stdint.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum {
    SCT_KEY_RELEASE        = 0,        /**< A key is released. */    
    SCT_KEY_SHORT_PRESS    = 1,        /**< A key is released. */
    SCT_KEY_LONG_PRESS_1   = 2,        /**< A key is long pressed. */
    SCT_KEY_LONG_PRESS_2   = 3,        /**< A key is long pressed. */
    SCT_KEY_LONG_PRESS_3   = 4,        /**< A key is long pressed. */
    SCT_KEY_REPEAT         = 5,        /**< A key is repeat pressed. */
    SCT_KEY_DOUBLE_PRESS   = 6,        /**< A key is double click */
    SCT_KEY_TRIPLE_PRESS   = 7,        /**< A key is triple click. */
    SCT_KEY_PMU_LONG_PRESS = 8         /**< PMU hardware powerkey is long pressed. */
} sct_key_event_t;

typedef struct {
    uint32_t short_time;
    uint32_t longpress_time_1;
    uint32_t longpress_time_2;
    uint32_t longpress_time_3;
    uint32_t repeat_time;
    uint32_t double_interval_time;
    uint32_t triple_interval_time;
} sct_key_event_time_t;

typedef void (*sct_key_callback_t)(sct_key_event_t event, uint8_t key_data, void *user_data);


/********* varible extern *************/
extern sct_key_event_time_t    keypad_event_time;
extern uint32_t sct_key_driven_signal_time;

/******** funtion extern **************/
bool sct_key_event_init(void);
bool sct_key_register_callback(sct_key_callback_t callback, void *user_data);
bool sct_key_set_event_time(sct_key_event_time_t* event_time);
bool sct_key_set_driven_signal_time(uint32_t signal_time);
bool sct_key_set_debounce_time(uint32_t debounce);

#ifdef __cplusplus
}
#endif

#endif /* __SCT_KEY_EVENT_H__ */

