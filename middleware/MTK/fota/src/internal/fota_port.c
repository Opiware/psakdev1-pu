/* Copyright Statement:
 *
 */

#ifndef MOD_CFG_FOTA_DISABLE_OS
/* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#else
#include "mt7687.h"
#include "core_cmFunc.h"
#endif

#include "fota_port.h"


#ifndef MOD_CFG_FOTA_DISABLE_OS

void fota_port_isr_disable(void)
{
    taskDISABLE_INTERRUPTS();
}

void fota_port_isr_enable(void)
{
    taskENABLE_INTERRUPTS();
}

#else

void fota_port_isr_disable(void)
{
    __disable_irq();
}

void fota_port_isr_enable(void)
{
    __enable_irq();
}

#endif

