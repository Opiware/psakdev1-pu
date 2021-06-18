/* Copyright Statement:
 *
 */

#ifndef __TRNG_SW_H__
#define __TRNG_SW_H__


#include "hal_platform.h"
#include "hal_nvic_internal.h"

#ifdef HAL_TRNG_MODULE_ENABLED

/*define the trng time configuration */
#define TRNG_TIME       ((uint32_t)0x030F0801)

#define TIMEOUT_VALUE    4096

typedef enum {

    TRNG_GEN_TIMEOUT = -1,
    TRNG_GEN_FAIL    = -2,
    TRNG_GEN_SUCCESS = 0

} Trng_Result;

#define TRNG_INIT  1

#define TRNG_DEINIT  0

#define TRNG_CHECK_AND_SET_BUSY(busy_status)  \
do{ \
    uint32_t saved_mask; \
    saved_mask = save_and_set_interrupt_mask(); \
    if(trng_init_status == TRNG_INIT){ \
        busy_status = HAL_TRNG_STATUS_ERROR; \
    } else { \
        trng_init_status = TRNG_INIT;  \
        busy_status = HAL_TRNG_STATUS_OK; \
    } \
     restore_interrupt_mask(saved_mask); \
}while(0)

#define TRNG_SET_IDLE()   \
do{  \
	    uint32_t saved_mask; \
        saved_mask = save_and_set_interrupt_mask(); \
       trng_init_status= TRNG_DEINIT;  \
       restore_interrupt_mask(saved_mask); \
}while(0)



/* function delcartion */
void  trng_init(void);
Trng_Result trng_config_timeout_limit(uint32_t timeout_value);
Trng_Result trng_enable_mode(bool H_GARO, bool H_RO, bool H_FIRO);
void  trng_start(void);
void  trng_deinit(void);
void trng_test(void);
Trng_Result  trng_get(uint32_t *random_data);
uint32_t  trng_get_random_data(void);
void  trng_stop(void);


#endif /*HAL_TRNG_MODULE_ENABLED*/
#endif

