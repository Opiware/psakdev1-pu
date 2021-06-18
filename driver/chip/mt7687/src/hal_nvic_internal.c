/* Copyright Statement:
 *
 */

#include "hal_nvic_internal.h"

#ifdef HAL_NVIC_MODULE_ENABLED
#include "hal_nvic.h"
#include "memory_attribute.h"
#include "hal_nvic_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

static void software_trigger_irq(hal_nvic_irq_t irq_number)
{
    NVIC->STIR = (irq_number << NVIC_STIR_INTID_Pos) & NVIC_STIR_INTID_Msk;
    __DSB();
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

#ifdef __cplusplus
}
#endif

#endif /* HAL_NVIC_MODULE_ENABLED */


