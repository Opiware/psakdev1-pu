/* Copyright Statement:
 *
 */

#ifndef __HAL_KEYPAD_POWERKEY_INTERNAL_H__
#define __HAL_KEYPAD_POWERKEY_INTERNAL_H__

#include "hal_keypad.h"
#ifdef HAL_KEYPAD_FEATURE_POWERKEY
#include "hal_keypad_internal.h"
#include "hal_eint.h"
#include "mt2523.h"


#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************/
#define POWERKEY_BUFFER_SIZE            (32)

#define POWERKEY_PMU_RG_SET_1           (1)
#define POWERKEY_PMU_RG_SET_0           (0)

#define POWERKEY_PMU_RG_MASK            (1)

#define POWERKEY_PMU_STS_MASK           (0x03)

#define POWERKEY_PMU_RG_PKEY_LPEN       (5)
#define POWERKEY_PMU_RG_PKEY_CFG        (1)

/***************************************************************/
#define POWERKEY_STATUS_LONG_PRESS      (0x02)
#define POWERKEY_STATUS_LONG_RELEASE    (0x01)

#define POWERKEY_STATUS_PRESS           (0x02)
#define POWERKEY_STATUS_RELEASE         (0x01)

#define POWERKEY_DEFAUL_REPEAT_TIME     (1000)
#define POWERKEY_DEFAUL_LONGPRESS_TIME  (2000)


/***************************************************************/
typedef struct {
    hal_powerkey_callback_t callback;
    void *user_data;
} powerkey_callback_context_t;

typedef struct {
    uint32_t            registerd_data;
    uint32_t            release_count;
    uint32_t            timer_handle;
    bool                has_initilized;
    bool                is_pmu_init;
    powerkey_callback_context_t powerkey_callback;
    uint32_t            longpress_time;
    uint32_t            repeat_time;
} powerkey_context_t;

typedef struct {
    hal_keypad_powerkey_event_t data[POWERKEY_BUFFER_SIZE];
    uint8_t write_index;
    uint8_t read_index;
    uint8_t press_count;
} powerkey_buffer_t;


typedef enum {
    POWERKEY_PMU_POWRKEY = 0,
    POWERKEY_PMU_LONG_POWERKEY
} powerkey_pmu_status_t;

typedef struct {
    uint32_t timer_handle;
    hal_keypad_key_state_t current_state;

} powerkey_state_t;

/********* varible extern *************/
extern powerkey_context_t powerkey_context;

/******** funtion extern **************/
bool powerkey_pmu_reisgter_callback(void);
uint32_t powerkey_get_buffer_data_size(void);
bool powerkey_pmu_init(void);
void powerkey_pop_one_key_from_buffer(hal_keypad_powerkey_event_t *key_event);
bool powerkey_get_pressed_state(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_KEYPAD_FEATURE_POWERKEY */
#endif /* _HAL_KEYPAD_POWERKEY_INTERNAL_H_ */

