/* Copyright Statement:
 *
 */

#include "stm32f4xx.h"
#include "ostimer_reg.h"
#include "ostimer.h"

int ostimer_init( void )
{
    /************************************************************/
    /*********************** OST_INT_MASK ***********************/
    /************************************************************/
    /* Setting OSTD timeout interrupt */
    HW_WRITE( OST_INT_MASK, (~(0x0004))&0x1F ); /* Unmask UFN timeout */
    HW_WRITE(OST_ISR, 0x001F);

    NVIC_SetPriority(OSTIMER_IRQ, 0xF0);  /* set Priority for Systick Interrupt */
    //NVIC_EnableIRQ(OSTIMER_IRQ);
    return 0;
}


int ostimer_set_frame_duration( uint16_t frm_dur )
{
    uint16_t tmp_frm_f32k = (frm_dur*8)/(245/*30.5176*8*/);
    uint16_t ost_frm_num = 0;
    uint16_t target_ost_frm_f32k = 0; /* bit8~0 in OST_FRM_F32K */
    uint16_t register_ost_frm_f32k = 0;

    if ((frm_dur < 1000) || (frm_dur >8000)) {
        return -1;
    }

    target_ost_frm_f32k = tmp_frm_f32k;
    register_ost_frm_f32k = (ost_frm_num << 12) + (target_ost_frm_f32k);
    HW_WRITE( OST_FRM_F32K, register_ost_frm_f32k );
    HW_WRITE( OST_FRM, frm_dur );
    return 0;
}


int ostimer_enable( uint32_t ufn )
{
    volatile uint16_t reg_val = 0;
    volatile uint16_t wait_time = 0;
    uint16_t tmp = 0;

    /* Upper Layer must set OST_FRM before Enable OST. */
    if ( HW_READ( OST_FRM ) < 1000 ) {
        return -1;
    }

    /* Set max. value as initial value before Enable OST. */
    HW_WRITE( OST_AFN, 0xFFFFFFFF );
    HW_WRITE( OST_UFN, ufn );

    tmp = HW_READ(OST_CON);

    /* Set 1: Always enable UFN down-count feature in ARM OS Timer Driver */
    tmp |= 0x2;
    /* Set 0: Disable OST DBG mode */
    tmp &= ~(0x4);
    /* Enable OS Timer */
    tmp |= 0x1;

    //Enter critical section?
    HW_WRITE( OST_CON, tmp );
    /* Trigger HW Write command */
    HW_WRITE( OST_CMD, (CMD_MAGIC_VALUE+0x0000E004) );
    do{
        wait_time++;
        if(wait_time > OST_MAX_WAIT_TIME) {
            return -2;
        }
        reg_val = HW_READ(OST_STA);
    }while(!(reg_val & 0x0002));
    //Exit critical section?
    return 0;
}



int ostimer_disable( void )
{
    volatile uint16_t reg_val = 0;
    volatile uint16_t wait_time = 0;
    uint16_t tmp = 0;

    tmp = HW_READ(OST_CON);
    /* Disable OS Timer */
    tmp &= ~(0x1);

    //Enter critical section?
    HW_WRITE( OST_CON, tmp );
    /* Trigger HW Write command */
    HW_WRITE( OST_CMD, (CMD_MAGIC_VALUE+0x00008004) );
    do{
        wait_time++;
        if(wait_time > OST_MAX_WAIT_TIME) {
            return -2;
        }
        reg_val = HW_READ(OST_STA);
    }while(!(reg_val & 0x0002));
    //Exit critical section?
    return 0;
}


int ostimer_get_frame_num( uint32_t *frm_dur )
{
    volatile uint16_t reg_val = 0;
    volatile uint16_t wait_time = 0;

    /*OST should be in Normal State*/
    /* Trigger HW Read command */
    HW_WRITE( OST_CMD, (CMD_MAGIC_VALUE+0x00000002) );
    do{
        wait_time++;
        if(wait_time > OST_MAX_WAIT_TIME) {
            return -2;
        }
        reg_val = HW_READ(OST_STA);
    }while(!(reg_val & 0x0002));

    *frm_dur = HW_READ(OST_UFN_R);
    return 0;
}



int test_ostimer( void )
{
    ostimer_init();
    ostimer_set_frame_duration(1000);
    ostimer_enable( 3 );
    return 0;
}
