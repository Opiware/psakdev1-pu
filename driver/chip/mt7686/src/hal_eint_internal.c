/* Copyright Statement:
 *
 */

/*************************************************************************
 * Included header files
 *************************************************************************/

#include "hal_eint.h"

#ifdef HAL_EINT_MODULE_ENABLED
#include "hal_eint_internal.h"
#include "hal_nvic_internal.h"
#include "hal_log.h"
#include "hal_gpt.h"
#include "memory_attribute.h"


ATTR_RWDATA_IN_TCM EINT_REGISTER_T *EINT_REGISTER = (EINT_REGISTER_T *)EINT_BASE;
eint_function_t eint_function_table[HAL_EINT_NUMBER_MAX];

uint32_t eint_get_status(void)
{
    return (EINT_REGISTER->EINT_STA);
}

void eint_ack_interrupt(uint32_t eint_number)
{
    EINT_REGISTER->EITN_INTACK = (1 << eint_number);
}

uint32_t eint_caculate_debounce_time(uint32_t ms)
{
    uint32_t prescaler;
    uint32_t count;

    if (ms == 0) {
        /* set to one 32KHz clock cycle */
        prescaler = EINT_CON_PRESCALER_32KHZ;
        count = 0;
    } else if (ms <= 62) {
        prescaler = EINT_CON_PRESCALER_32KHZ;
        count = EINT_TIME_MS_TO_COUNT(ms,32768);
    } else if (ms <= 125) {
        prescaler = EINT_CON_PRESCALER_16KHZ;
        count = EINT_TIME_MS_TO_COUNT(ms,16384);
    } else if (ms <= 250) {
        prescaler = EINT_CON_PRESCALER_8KHZ;
        count = EINT_TIME_MS_TO_COUNT(ms,8192);
    } else if (ms <= 500) {
        prescaler = EINT_CON_PRESCALER_4KHZ;
        count = EINT_TIME_MS_TO_COUNT(ms,4096);
    } else if (ms <= 1000) {
        prescaler = EINT_CON_PRESCALER_2KHZ;
        count = EINT_TIME_MS_TO_COUNT(ms,2048);
    } else if (ms <= 2000) {
        prescaler = EINT_CON_PRESCALER_1KHZ;
        count = EINT_TIME_MS_TO_COUNT(ms,1024);
    } else if (ms <= 4000) {
        prescaler = EINT_CON_PRESCALER_512HZ;
        count = EINT_TIME_MS_TO_COUNT(ms,512);
    } else if (ms <= 8000) {
        prescaler = EINT_CON_PRESCALER_256HZ;
        count = EINT_TIME_MS_TO_COUNT(ms,256);
    } else {
        /* set to maximum prescaler/count */
        prescaler = EINT_CON_PRESCALER_256HZ;
        count = EINT_CON_DBC_CNT_MASK;
    }

    if (count > EINT_CON_DBC_CNT_MASK) {
        count = EINT_CON_DBC_CNT_MASK;
    }

    count = (count | EINT_CON_DBC_EN_MASK |
             (EINT_CON_PRESCALER_MASK & (prescaler << EINT_CON_PRESCALER_OFFSET)));
    return count;
}

void hal_eint_isr(uint32_t index)
{
    uint32_t status;
    uint32_t eint_index = 0;

    status = eint_get_status();
    if (status == 0) {
        return;
    }

    for (eint_index = 0; eint_index < HAL_EINT_NUMBER_MAX; eint_index++) {
        if (status & (1 << eint_index)) {
            hal_eint_mask((hal_eint_number_t)eint_index);
            eint_ack_interrupt(eint_index);
            if (eint_function_table[eint_index].eint_callback) {
                eint_function_table[eint_index].eint_callback(eint_function_table[eint_index].user_data);
            } else {
                //log_hal_error("ERROR: no EINT interrupt handler!\n");
            }
        }
    }
}

#endif /* HAL_EINT_MODULE_ENABLED */

