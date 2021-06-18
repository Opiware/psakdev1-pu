/* Copyright Statement:
 *
 */

#ifndef __HAL_KEYPAD_INTERNAL_H__
#define __HAL_KEYPAD_INTERNAL_H__

#include "hal_keypad.h"

#ifdef HAL_KEYPAD_MODULE_ENABLED
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "mt2523.h"



#ifdef __cplusplus
extern "C"
{
#endif

//#define KEYPAD_DEBUG_LOG
#define KEY_INDEX_END               (0xfe)    /* key position end flag */
#define KEYPAD_BUFFER_SIZE          (128)      /* key position buffer size */

#define KEYPAD_FLAG_STA             KEYPAD_KP_STA_MASK
#define KEYPAD_FLGA_EN              KEYPAD_KP_EN_MASK
#define KEYPAD_FLAG_MODE            KEYPAD_KP_SEL_EN_MASK

/***************************************************************/

#define KEYPAD_DEFAULT_SCAN_TIMING  (0x66bb)
#define KEYPAD_DEFAULT_DEBOUNCE     (16*32)
#define KEYPAD_DEFAULT_BIT_MAPPING  (0xffffffff)

#define KEYPAD_DEBOUNCE_MAX         (0x1ffff)
#define KEYPAD_DEBOUNCE_MS_UNIT     (32)

#define PROCESS_FROM_KEYPAD_IRQ     (0xff)

#define KEYPAD_TYPE_OLD_PRESS       (0x00)
#define KEYPAD_TYPE_NEW_RELEASE     (0x01)
#define KEYPAD_TYPE_NEW_PRESS       (0x10)
#define KEYPAD_TYPE_OLD_RELEASE     (0x11)

#define KEYPAD_DEFAUL_REPEAT_TIME       (1000)
#define KEYPAD_DEFAUL_LONGPRESS_TIME    (2000)

typedef struct {
    hal_keypad_callback_t callback;
    void *user_data;
} keypad_callback_context_t;

typedef struct {

    bool                        has_initilized;
    bool                        is_running;
    keypad_callback_context_t   keypad_callback;
    uint32_t                    longpress_time;
    uint32_t                    repeat_time;
} keypad_context_t;

typedef struct {
    uint32_t register_value[2];
} keypad_key_bitmap_t;

typedef struct {
    hal_keypad_event_t data[KEYPAD_BUFFER_SIZE];
    uint32_t write_index;
    uint32_t read_index;
    uint32_t press_count;
} keypad_buffer_t;

typedef struct {
    uint32_t                *p_key_index;
    hal_keypad_key_state_t  current_state[32];
    uint32_t                timer_handle[32];
    uint32_t                position[32];
} keypad_status_t;

/********* varible extern *************/
extern KEYPAD_REGISTER_T *keypad;
extern keypad_context_t keypad_context;
extern keypad_key_bitmap_t keypad_reg_bitmap;
extern keypad_key_bitmap_t keypad_saved_bitmap;
extern keypad_status_t keypad_state;
extern keypad_buffer_t keypad_buffer;



/***********************/


/******** funtion extern **************/
void keypad_pop_one_key_from_buffer(hal_keypad_event_t *key_event) ;
void keypad_nvic_register(void);
uint32_t keypad_get_buffer_data_size(void);
hal_keypad_key_state_t keypad_get_state(void);
void keypad_eint_wakeup_init(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_KEYPAD_MODULE_ENABLED */
#endif /*_HAL_KEYPAD_INTERNAL_H_ */

