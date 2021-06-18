/* Copyright Statement:
 *
 */

#include "hal_nvic.h"

#ifdef HAL_NVIC_MODULE_ENABLED

#include <stdint.h>
#include "nvic.h"
#include "mem_util.h"
#include "timer.h"
#include "nvic_extern.h"
#include "memory_attribute.h"


void NVIC_SetupVectorTable(uint32_t addr)
{
    SCB->VTOR = addr;

    __asm volatile("dsb");
    __asm volatile("isb");
}


void NVIC_SWInt(unsigned int source)
{
    NVIC->STIR = source;
}

ATTR_TEXT_IN_TCM uint32_t save_and_set_interrupt_mask(void)
{
    uint32_t mask;
    local_irq_save(mask);
    return mask;
}

ATTR_TEXT_IN_TCM void restore_interrupt_mask(uint32_t mask)
{
    local_irq_restore(mask);
}
#endif

