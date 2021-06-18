/* Copyright Statement:
 *
 */

#ifndef HAL_EMI_INTERNAL_H
#define HAL_EMI_INTERNAL_H

#include <memory_attribute.h>

typedef enum emi_clock_enum_t
{
    EMI_CLK_LOW_TO_HIGH = 0,
    EMI_CLK_HIGH_TO_LOW  = 1,
} emi_clock;

typedef struct {
    uint32_t EMI_RDCT_VAL;
    uint32_t EMI_DSRAM_VAL;
    uint32_t EMI_MSRAM0_VAL;
	uint32_t EMI_MSRAM1_VAL;
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


typedef enum{
    FILTER_LENGTH_521T = 0,
	FILTER_LENGTH_1024T = 1,
	FILTER_LENGTH_2048T = 2,
	FILTER_LENGTH_4096T = 3,
}bandwidth_filter_length_t;



ATTR_TEXT_IN_TCM int32_t EMI_DynamicClockSwitch(emi_clock clock);
ATTR_TEXT_IN_TCM void mtk_psram_half_sleep_enter(void);
ATTR_TEXT_IN_TCM void mtk_psram_half_sleep_exit(void);
ATTR_TEXT_IN_TCM void EMI_Setting_restore(void);
ATTR_TEXT_IN_TCM void EMI_Setting_Save(void);
ATTR_TEXT_IN_TCM int8_t custom_setEMI(void);
ATTR_TEXT_IN_TCM int8_t custom_setAdvEMI(void);
ATTR_TEXT_IN_TCM void emi_mask_master(void);
ATTR_TEXT_IN_TCM void emi_unmask_master(void);


ATTR_TEXT_IN_TCM uint32_t __EMI_GetSR(uint32_t bank_no);
ATTR_TEXT_IN_TCM void __EMI_SetSR(uint32_t bank_no, uint32_t value);


#endif
