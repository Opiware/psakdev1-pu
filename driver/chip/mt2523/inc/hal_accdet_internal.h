/* Copyright Statement:
 *
 */

#ifndef __HAL_ACCDET_INTERNAL_H__
#define __HAL_ACCDET_INTERNAL_H__
#include "hal_accdet.h"

#ifdef HAL_ACCDET_MODULE_ENABLED

#include "hal_eint.h"
#include "hal_nvic.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ACCDET_BUSY 1
#define ACCDET_IDLE 0

/* ACCDET+EINT solution, ACCDET only solution is supported if this define is unmasked */
#define ACCDET_EINT_SUPPORT

/* ACCDET EINT debounce */
#define HAL_ACCDET_EINT_DEBOUNCE    20

/* ACCDET PWM setting */
#define HAL_ACCDET_PWM_WIDTH        0x1900
#define HAL_ACCDET_PWM_THRESHOLD    0x0400
#define HAL_ACCDET_PWM_DELAY        0x8180


typedef struct {
    hal_accdet_callback_t func;
    void *arg;
} accdet_callback_t;

#ifdef ACCDET_EINT_SUPPORT

/* Callback function of EINT */
void accdet_eint_callback(void *user_data);

/* Register callback function of EINT */
void accdet_eint_callback_register(void);

/* Unregister callback function of EINT */
void accdet_eint_callback_unregister(void);

#endif

/* Callback function of IRQ */
void accdet_irq_callback(hal_nvic_irq_t irq_number);

/* Register callback function of IRQ */
void accdet_irq_callback_register(void);

/* Unregister callback function of IRQ */
void accdet_irq_callback_unregister(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_ACCDET_MODULE_ENABLED*/
#endif /* __HAL_ACCDET_INTERNAL_H__ */

