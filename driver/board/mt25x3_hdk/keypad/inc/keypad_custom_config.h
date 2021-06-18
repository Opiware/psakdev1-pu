/* Copyright Statement:
 *
 */

#ifndef __KEYPAD_CUSTOM_CONFIG_H__
#define __KEYPAD_CUSTOM_CONFIG_H__


#ifdef __cplusplus
extern "C" {
#endif

/*Set the keypad detection debounce time, the maximum value is 4095, the unit is millisecond.*/
#define HAL_KEYPAD_DEBOUNCE_TIME    16

/*Set normal keypad longpress time, the unit is millisecond.*/
#define HAL_KEYPAD_LONGPRESS_TIME   2000

/*Set normal keypad  repeat time, the unit is millisecond.*/
#define HAL_KEYPAD_REPEAT_TIME   1000

/*Set powerkey longpress time, the unit is millisecond.*/
#define HAL_POWERKEY_LONGPRESS_TIME 2000

/*Set powerkey  repeat time, the unit is millisecond.*/
#define HAL_POWERKEY_REPEAT_TIME 1000


#ifdef __cplusplus
}
#endif

#endif /* __KEYPAD_CUSTOM_CONFIG_H__ */

