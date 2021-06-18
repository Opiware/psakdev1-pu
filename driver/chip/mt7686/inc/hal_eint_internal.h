/* Copyright Statement:
 *
 */

#ifndef __HAL_EINT_INTERNAL_H__
#define __HAL_EINT_INTERNAL_H__

#ifdef HAL_EINT_MODULE_ENABLED
#include "hal_nvic.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    void (*eint_callback)(void *user_data);
    void *user_data;
} eint_function_t;

typedef enum {
    EINT_MASK = 1,
    EINT_UNMASK = 2,
    EINT_INACTIVE = 3,
    EINT_ACTIVE = 4,
} eint_status_t;

typedef enum {
    EINT_NOT_INIT = 0,
    EINT_INIT = 1,
    EINT_DEINIT = 2,
} eint_driver_status_t;

typedef enum {
    EINT_DOMAIN_DISABLE = 0,
    EINT_DOMAIN_ENABLE  = 1
} eint_domain_status_t;

#define EINT_CON_PRESCALER_32KHZ    (0x00000000)
#define EINT_CON_PRESCALER_16KHZ    (0x00000001)
#define EINT_CON_PRESCALER_8KHZ     (0x00000002)
#define EINT_CON_PRESCALER_4KHZ     (0x00000003)
#define EINT_CON_PRESCALER_2KHZ     (0x00000004)
#define EINT_CON_PRESCALER_1KHZ     (0x00000005)
#define EINT_CON_PRESCALER_512HZ    (0x00000006)
#define EINT_CON_PRESCALER_256HZ    (0x00000007)
#define EINT_CON_DBC_ENABLE         (0x01)
#define EINT_CON_DBC_DISABLE        (0x00)
#define EINT_CON_RSTD_BC_MASK       (0x01)

#define EINT_WAKE_EVENT_EN          (0xFFFFFFFF)
#define EINT_WAKE_EVENT_DIS         (0xFFFFFFFF)

#define EINT_TIME_MS_TO_COUNT(time_ms, unit)   (((time_ms*unit)+500)/1000)  //round off calculation

/********* varible extern *************/
extern EINT_REGISTER_T *EINT_REGISTER;
extern eint_function_t eint_function_table[HAL_EINT_NUMBER_MAX];

/******** funtion extern **************/
hal_eint_status_t eint_mask_wakeup_source(hal_eint_number_t eint_number);
hal_eint_status_t eint_unmask_wakeup_source(hal_eint_number_t eint_number);
void eint_ack_interrupt(uint32_t eint_number);
uint32_t eint_get_status(void);
uint32_t eint_caculate_debounce_time(uint32_t ms);
void hal_eint_isr(uint32_t index);

#ifdef __cplusplus
}
#endif

#endif /* HAL_EINT_MODULE_ENABLED */

#endif /* __HAL_EINT_INTERNAL_H__ */

