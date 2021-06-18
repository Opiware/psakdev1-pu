/* Copyright Statement:
 *
 */

#ifndef __EMI_SW_INTERNAL_H__
#define __EMI_SW_INTERNAL_H__

#include <stdint.h>

typedef enum {
    EMI_CS0 = 0,
    EMI_CS1 = 1,
    EMI_CS2 = 2,
    EMI_CS3 = 3,
    EMI_MAX_CS = 3,
    EMI_UNKNOWN_CS = 0xff
} EMI_CHIP_SELECT;


typedef enum {
    EMI_FLASH = 0,
    EMI_RAM = 1,
    EMI_MAX_MEMTYPE = 1
} EMI_MEMTYPE;


typedef struct {
    uint32_t reg_num;

    uint32_t EMI_CONM_value;
    uint32_t EMI_GENA_value;
    uint32_t EMI_RDCT_value;
    uint32_t EMI_DLLV_value;

    uint32_t EMI_IDLC_value;
    uint32_t EMI_IDLD_value;
    uint32_t EMI_IDLE_value;

    uint32_t EMI_ODLC_value;
    uint32_t EMI_ODLD_value;
    uint32_t EMI_ODLE_value;
    uint32_t EMI_ODLF_value;

    uint32_t EMI_IOA_value;
    uint32_t EMI_IOB_value;

    uint32_t EMI_DSRAM_value;
    uint32_t EMI_MSRAM_value;

    uint32_t EMI_ARBA_value;
    uint32_t EMI_ARBB_value;
    uint32_t EMI_ARBC_value;

    uint32_t EMI_SLCT_value;
    uint32_t EMI_ABCT_value;

} EMI_RUNTIME_Info;


#define __EMI_BlockAllTransactions()  \
        do {    \
            *EMI_CONM = 0x0070; \
        } while (0)

#define __EMI_UnblockAllTransactions()  \
        do {    \
            *EMI_CONM = 0x0000; \
        } while (0)


#endif  /* !__EMI_SW_INTERNAL_H__ */

