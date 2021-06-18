/* Copyright Statement:
 *
 */

#ifndef _KEYPAD_CUSTOM_H_
#define _KEYPAD_CUSTOM_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    uint32_t longpress_time;
    uint32_t repet_time;
} keypad_custom_event_time_t;


/********* varible extern *************/


/******** funtion extern **************/
bool keypad_custom_normal_init(void);
bool keypad_custom_init(void);
bool keypad_custom_deinit(void);
uint8_t keypad_custom_translate_keydata(uint8_t key_position);
bool keypad_custom_set_event_time(keypad_custom_event_time_t* event_time);

#ifdef HAL_KEYPAD_FEATURE_POWERKEY
bool keypad_custom_powerkey_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _KEYPAD_CUSTOM_H_ */
