/* Copyright Statement:
 *
 */

#include "sw_types.h"
#include <stdint.h>
int8_t custom_setAdvEMI(void);
int8_t custom_setEMI(void);
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
