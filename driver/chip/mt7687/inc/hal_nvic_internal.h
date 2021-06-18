/* Copyright Statement:
 *
 */

#ifndef _HAL_NVIC_INTERNAL_H_
#define _HAL_NVIC_INTERNAL_H_
#include "hal_nvic.h"

#ifdef HAL_NVIC_MODULE_ENABLED
/* Please refer to configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY= 4 in freertos_config.h */
#define FREERTOS_ISR_API_PRIORITY  (4)          /* please keep the setting */
/* DEFAULT_IRQ_PRIORITY is from FREERTOS_ISR_API_PRIORITY =  4  to  configKERNEL_INTERRUPT_PRIORITY -1 = (0xFF - 1)
    as pend_sv should be lowest irq priority to avoid unneccessary freert_os schedule */
#define DEFAULT_IRQ_PRIORITY  (FREERTOS_ISR_API_PRIORITY + 1)     /* please keep the setting */
#define RESERVED_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 63)

uint32_t save_and_set_interrupt_mask(void);
void restore_interrupt_mask(uint32_t mask);
hal_nvic_status_t nvic_irq_software_trigger(hal_nvic_irq_t irq_number);

#endif //HAL_NVIC_MODULE_ENABLED
#endif //_HAL_NVIC_INTERNAL_H_

