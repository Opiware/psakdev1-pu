/* Copyright Statement:
 *
 */

#ifndef __HAL_MPU_INTERNAL_H__
#define __HAL_MPU_INTERNAL_H__
#include "hal_mpu.h"

#ifdef HAL_MPU_MODULE_ENABLED


#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    struct {
        uint32_t ENABLE: 1;                     /**< Enables the MPU */
        uint32_t HFNMIENA: 1;                   /**< Enables the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
        uint32_t PRIVDEFENA: 1;                 /**< Enables privileged software access to the default memory map */
        uint32_t _reserved0: 29;                /**< Reserved */
    } b;
    uint32_t w;
} MPU_CTRL_Type;

typedef uint32_t MPU_REGION_EN_Type;

typedef union {
    struct {
        uint32_t REGION: 4;                     /**< MPU region field */
        uint32_t VALID: 1;                      /**< MPU Region Number valid bit */
        uint32_t ADDR: 27;                      /**< Region base address field */
    } b;
    uint32_t w;
} MPU_RBAR_Type;

typedef union {
    struct {
        uint32_t ENABLE: 1;                     /**< Region enable bit */
        uint32_t SIZE: 5;                       /**< Specifies the size of the MPU protection region */
        uint32_t _reserved0: 2;                 /**< Reserved */
        uint32_t SRD: 8;                        /**< Subregion disable bits */
        uint32_t B: 1;                          /**< Memory access attributes */
        uint32_t C: 1;                          /**< Memory access attributes */
        uint32_t S: 1;                          /**< Shareable bit */
        uint32_t TEX: 3;                        /**< Memory access attributes */
        uint32_t _reserved1: 2;                 /**< Reserved */
        uint32_t AP: 3;                         /**< Access permission field */
        uint32_t _reserved2: 1;                 /**< Reserved */
        uint32_t XN: 1;                         /**< Instruction access disable bit */
        uint32_t _reserved3: 3;                 /**< Reserved */
    } b;
    uint32_t w;
} MPU_RASR_Type;

typedef struct {
    MPU_RBAR_Type mpu_rbar;
    MPU_RASR_Type mpu_rasr;
} MPU_ENTRY_Type;


extern MPU_CTRL_Type g_mpu_ctrl;
extern MPU_REGION_EN_Type g_mpu_region_en;
extern MPU_ENTRY_Type g_mpu_entry[HAL_MPU_REGION_MAX];

/* Save MPU status before entering deepsleep */
void mpu_status_save(void);

/* Restore MPU status after leaving deepsleep */
void mpu_status_restore(void);


#ifdef __cplusplus
}
#endif

#endif /* HAL_MPU_MODULE_ENABLED */
#endif /* __HAL_MPU_INTERNAL_H__ */

