/* Copyright Statement:
 *
 */

#include "hal_trng_internal.h"

#ifdef HAL_TRNG_MODULE_ENABLED
#include "hal_clock.h"

/*trng  base address register global variable*/
TRNG_REGISTER_T  *trng = TRNG;


void  trng_init(void)
{

    /* enable clock pdn*/
    hal_clock_enable(HAL_CLOCK_CG_TRNG);

}

Trng_Result trng_config_timeout_limit(uint32_t timeout_value)

{
    /*time out shuld be less than TIMEOUT_VALUE*/

    uint32_t  timeout_limit = timeout_value;

    if (timeout_limit > TIMEOUT_VALUE) {
        return TRNG_GEN_FAIL;
    }

    trng->TRNG_CONF &= ~(0xFFF << (6));
    trng->TRNG_CONF |= (timeout_value << (6));

    return  TRNG_GEN_SUCCESS;
}


Trng_Result trng_enable_mode(bool H_FIRO, bool H_RO, bool H_GARO)
{

    if (true == H_FIRO) {
        trng->TRNG_CONF |= TRNG_H_FIRO_EN_MASK;
    } else {
        trng->TRNG_CONF &= ~TRNG_H_FIRO_EN_MASK;
    }
    if (true == H_RO) {
        trng->TRNG_CONF |= TRNG_H_RO_EN_MASK;
    } else {
        trng->TRNG_CONF &= ~TRNG_H_RO_EN_MASK;
    }

    if (true == H_GARO) {
        trng->TRNG_CONF |= TRNG_H_GARO_EN_MASK;
    } else {
        trng->TRNG_CONF &= ~TRNG_H_GARO_EN_MASK;
    }

    return  TRNG_GEN_SUCCESS;

}

void  trng_start(void)
{
    volatile uint32_t temp_random = 0;
    temp_random = trng->TRNG_DATA;
    temp_random += 1;
    trng->TRNG_CTRL |= TRNG_START_MASK;

}

void  trng_stop(void)
{
    volatile uint32_t temp_random = 0;
    temp_random = trng->TRNG_DATA;
    temp_random += 1;

    trng->TRNG_CTRL &= ~TRNG_START_MASK;


}


void  trng_deinit(void)

{
    /*disable clock pdn*/
    hal_clock_disable(HAL_CLOCK_CG_TRNG);

}


uint32_t  trng_get_random_data(void)
{

    volatile uint32_t random_data = 0;
    volatile uint32_t ready_data = 0;


    ready_data = trng->TRNG_INT_SET;
    ready_data &= TRNG_RDY_MASK;
    while (ready_data != TRNG_RDY_MASK) {
        ready_data = trng->TRNG_INT_SET;
	  if (ready_data == TRNG_TIMEOUT_MASK) {
           return 0;
		}
        ready_data &= TRNG_RDY_MASK;
    }
    trng->TRNG_INT_CLR = TRNG_INT_CLR_MASK;
    trng->TRNG_CTRL = TRNG_STOP_MASK;
    random_data = trng->TRNG_DATA;
	
    return random_data;
}

#endif /*HAL_TRNG_MODULE_ENABLED*/







