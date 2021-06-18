/* Copyright Statement:
 *
 */

#include "memory_attribute.h"
#include "bl_gpt.h"

ATTR_RWDATA_IN_TCM BL_GPT_REGISTER_T* gpt_ms  = BL_GPT5;
ATTR_RWDATA_IN_TCM BL_GPT_REGISTER_T* gpt_us = BL_GPT4;

ATTR_RWDATA_IN_TCM bool us_init_falg = false;
ATTR_RWDATA_IN_TCM bool ms_init_falg = false;

#define bl_gpt_current_count(gpt) (gpt->GPT_COUNT)

ATTR_TEXT_IN_TCM static void bl_gpt_delay_time(BL_GPT_REGISTER_T *gpt, const uint32_t count)
{
    volatile uint32_t end_count = 0, current = 0;
    current   = bl_gpt_current_count(gpt);
    end_count = current + count + 1;
        
    /* loop to wait time pass */
    if ( end_count > current ) {
        while ( bl_gpt_current_count(gpt) < end_count );    /* current time < end_time */
    } else {                                                /* current time > end time */
        while ( bl_gpt_current_count(gpt) >= current );     /* wait time roll back */
        while ( bl_gpt_current_count(gpt) < end_count );    /* wait time reach end_time */
    }
}

ATTR_TEXT_IN_TCM static void  bl_gpt_start_free_run_timer(BL_GPT_REGISTER_T *gpt, const uint32_t clock_source, const uint32_t divide)
{
    //if pdn not power on, power it on
    if ( (BL_GPT_REG(BL_GPT_PDN_COND2) & BL_GPT_PDN_MASK) != 0) {
        BL_GPT_REG(BL_GPT_PDN_CLRD2) = BL_GPT_PDN_MASK;
    }
    
    gpt->GPT_CLK = clock_source | divide;
    
    /* set to free run mode, open clock source and start counter */
    gpt->GPT_CON = BL_GPT_CLOCK_UNGATE | BL_GPT_MODE_FREE_RUN | BL_GPT_COUNT_START;     
}


ATTR_TEXT_IN_TCM bool  bl_gpt_delay_us(const uint32_t us)
 {
    if ( us_init_falg != true ) {
        bl_gpt_start_free_run_timer(gpt_us,BL_GPT_CLOCK_13MHZ,BL_GPT_DIVIDE_13);
        us_init_falg = true;
    }

    bl_gpt_delay_time(gpt_us,us);

    return true;
}


ATTR_TEXT_IN_TCM bool  bl_gpt_delay_ms(const uint32_t ms)
{
    if ( ms_init_falg != true) {
        bl_gpt_start_free_run_timer(gpt_ms,BL_GPT_CLOCK_32KHZ,BL_GPT_DIVIDE_1);
        ms_init_falg = true;
    }

    bl_gpt_delay_time(gpt_ms,(uint32_t)( (ms * 32768) / 1000));

    return true;
}


ATTR_TEXT_IN_TCM bool bl_gpt_get_free_run_count(bl_gpt_clock_source_t clock_source, uint32_t *count)
{
    /* millisecond free run timer */
    if ( clock_source == BL_GPT_CLOCK_SOURCE_32K) {
        if ( ms_init_falg != true ) {

            /* set clock source to 32khz, and start timer */
            bl_gpt_start_free_run_timer( gpt_ms, BL_GPT_CLOCK_32KHZ, BL_GPT_DIVIDE_1 );
            ms_init_falg= true;
        }

        *count = bl_gpt_current_count( gpt_ms );

    } /* microsecond free rum timer */
    else if ( clock_source == BL_GPT_CLOCK_SOURCE_1M ) {
        if ( us_init_falg != true ) {

            /* set clcok source to 1mhz, and start timer */
            bl_gpt_start_free_run_timer( gpt_us, BL_GPT_CLOCK_13MHZ, BL_GPT_DIVIDE_13 );

            us_init_falg = true;

        }

        *count = bl_gpt_current_count( gpt_us );
    } else {
        return false;
    }

    return true;
}

