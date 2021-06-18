/* Copyright Statement:
 *
 */

#ifndef __HAL_CRYPT_INTERNAL_H__
#define __HAL_CRYPT_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mt7686.h"
#include "nvic.h"
#include "memory_attribute.h"

//#define CRYPTO_ENGINE_CTRL_BASE (volatile uint32_t *)(0xA0060004)
//#define ENGINE_CTRL_START_OFFSET (4)

//#define CRYPTO_ENGINE_STA_BASE (volatile uint32_t *)(0xA0060008)
//#define CRYPTO_ENGINE_STA_INT_CLR (16)

#define CRYPT_LOCK      1
#define CRYPT_UNLOCK    0

//#define CM4_MTK_CRYPTO_IRQ 6

#define DEFAULT_PRI             5
#define HIGHEST_PRI             9
#define CM4_MTK_CRYPTO_PRI      DEFAULT_PRI

/* global crypt lock variable */
extern bool g_crypt_lock;

extern void restore_interrupt_mask(uint32_t mask);
extern uint32_t save_and_set_interrupt_mask(void);

/* internal function for getting lock, -100 means the crypto engine is not available */
int32_t hal_crypt_lock_take(void);

/* internal function for releasing lock */
void hal_crypt_lock_give(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_CRYPT_INTERNAL_H__ */

