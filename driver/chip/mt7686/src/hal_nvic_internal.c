/* Copyright Statement:
 *
 */

#include "hal_nvic_internal.h"

#ifdef HAL_NVIC_MODULE_ENABLED
#include "hal_nvic.h"
#include "memory_attribute.h"

#ifdef __cplusplus
extern "C" {
#endif

static void software_trigger_irq(hal_nvic_irq_t irq_number)
{
    NVIC->STIR = ( irq_number << NVIC_STIR_INTID_Pos ) & NVIC_STIR_INTID_Msk;
    __DSB();
}

ATTR_TEXT_IN_TCM uint32_t save_and_set_interrupt_mask(void)
{
    uint32_t mask = __get_BASEPRI();
    //set base priority 1, fault can be handled first as priority is default zero.
    uint32_t priority = 1;
    __set_BASEPRI(((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF));
    __DMB();
    __ISB();
    return mask;
}

ATTR_TEXT_IN_TCM void restore_interrupt_mask(uint32_t mask)
{
    __set_BASEPRI(mask);
    __DMB();
    __ISB();
}

void nvic_mask_all_interrupt(void)
{
    hal_nvic_irq_t irq_number;
    uint32_t mask = save_and_set_interrupt_mask();
    for (irq_number = (hal_nvic_irq_t)0; irq_number < IRQ_NUMBER_MAX; irq_number++) {
        NVIC_DisableIRQ(irq_number);
    }
    restore_interrupt_mask(mask);
}

void nvic_unmask_all_interrupt(void)
{
    hal_nvic_irq_t irq_number;
    uint32_t mask = save_and_set_interrupt_mask();

    for (irq_number = (hal_nvic_irq_t)0; irq_number < IRQ_NUMBER_MAX; irq_number++) {
        NVIC_EnableIRQ(irq_number);
    }
    restore_interrupt_mask(mask);
}

void nvic_clear_all_pending_interrupt(void)
{
    hal_nvic_irq_t irq_number;
    for (irq_number = (hal_nvic_irq_t)0; irq_number < IRQ_NUMBER_MAX; irq_number++) {
        NVIC_ClearPendingIRQ(irq_number);
    }
}

hal_nvic_status_t nvic_irq_software_trigger(hal_nvic_irq_t irq_number)
{
    if (irq_number < 0 || irq_number >= IRQ_NUMBER_MAX) {
        return HAL_NVIC_STATUS_INVALID_PARAMETER;
    }

    software_trigger_irq(irq_number);
    return HAL_NVIC_STATUS_OK;
}

/**
 * @brief This function is used to return the CM4 status.
 * @return    To indicate whether this function call is successful.
 *            If the return value is not zero, the CM4 is executing excetpion handler;
 *            If the return value is zero, the CM4 is executing normal code. */
uint32_t hal_nvic_query_exception_number(void)
{
    return ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) >> SCB_ICSR_VECTACTIVE_Pos);
}

#ifdef __cplusplus
}
#endif

#endif /* HAL_NVIC_MODULE_ENABLED */


