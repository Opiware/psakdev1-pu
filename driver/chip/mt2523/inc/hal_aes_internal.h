/* Copyright Statement:
 *
 */

#ifndef __HAL_AES_INTERNAL_H__
#define __HAL_AES_INTERNAL_H__

#include "hal_aes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AES_CBC = 0,
    AES_ECB = 1
} aes_mode_t;

typedef struct {
    hal_aes_buffer_t *in;  /* input */
    hal_aes_buffer_t *out; /* output */
    hal_aes_buffer_t *key; /* key */
    uint8_t *iv;           /* iv */
} aes_parcel_t;

/* Those functions are implemented in the crypto library */
extern int32_t AES_HW_Init(aes_parcel_t *parcel, bool mode, bool sw_hw_key);
extern int32_t AES_HW_DeInit(void);
extern int32_t AES_HW_Encrypt(void);
extern int32_t AES_HW_Decrypt(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_AES_INTERNAL_H__ */

