/* Copyright Statement:
 *
 */

#ifndef HAL_EMI_INTERNAL_H
#define HAL_EMI_INTERNAL_H

#include <memory_attribute.h>

typedef enum emi_clock_enum_t {
    EMI_CLK_LOW_TO_HIGH = 0,
    EMI_CLK_HIGH_TO_LOW  = 1,
} emi_clock;

typedef struct {
    uint32_t EMI_GENA_VAL;
    uint32_t EMI_RDCT_VAL;
    uint32_t EMI_DSRAM_VAL;
    uint32_t EMI_MSRAM_VAL;
    uint32_t EMI_IDL_C_VAL;
    uint32_t EMI_IDL_D_VAL;
    uint32_t EMI_IDL_E_VAL;
    uint32_t EMI_ODL_C_VAL;
    uint32_t EMI_ODL_D_VAL;
    uint32_t EMI_ODL_E_VAL;
    uint32_t EMI_ODL_F_VAL;
    uint32_t EMI_IO_A_VAL;
    uint32_t EMI_IO_B_VAL;

} EMI_SETTINGS;

ATTR_TEXT_IN_TCM int32_t EMI_DynamicClockSwitch(emi_clock clock);
ATTR_TEXT_IN_TCM void mtk_psram_half_sleep_enter(void);
ATTR_TEXT_IN_TCM void mtk_psram_half_sleep_exit(void);
ATTR_TEXT_IN_TCM void EMI_Setting_restore(void);
ATTR_TEXT_IN_TCM void EMI_Setting_Save(void);
ATTR_TEXT_IN_TCM int8_t custom_setEMI(void);
ATTR_TEXT_IN_TCM int8_t custom_setAdvEMI(void);
ATTR_TEXT_IN_TCM void emi_mask_master(void);
ATTR_TEXT_IN_TCM void emi_unmask_master(void);
#endif
