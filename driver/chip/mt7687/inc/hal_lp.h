/* Copyright Statement:
 *
 */

/*
** $Log: low_hal_lp.h $
**
**
**
**
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

#ifndef __LOW_HAL_LP_H__
#define __LOW_HAL_LP_H__


#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include <stdint.h>
#include "mt7687.h"
#include "memory_attribute.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

typedef enum {
    LHAL_LP_CM4_HCLK_XTAL = 0,
    LHAL_LP_CM4_HCLK_F32K,
    LHAL_LP_CM4_HCLK_PLL1_64M,
    LHAL_LP_CM4_HCLK_PLL_CK,
    LHAL_LP_CM4_HCLK_NUM
} lhal_lp_cm4_hclk_t;

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/


/*
========================================================================
Routine Description:

Note:
========================================================================
*/
#define __SYSRAM_CHECKSUM_BEFORE_SLEEP() { \
    before_checksum = 0;                                                                                            \
    after_checksum = 0;                                                                                             \
    for(checksum_addr = CHECKSUM_START;checksum_addr < CHECKSUM_END;checksum_addr += 4 ){                           \
        before_checksum += *((volatile uint32_t*)checksum_addr);                                                    \
    }                                                                                                               \
}

#define __SYSRAM_CHECKSUM_AFTER_SLEEP() { \
    for(checksum_addr = CHECKSUM_START;checksum_addr < CHECKSUM_END;checksum_addr += 4 ){                           \
        after_checksum += *((volatile uint32_t*)checksum_addr);                                                     \
    }                                                                                                               \
}

#define __SYSRAM_CHECKSUM_RESULT() { \
    if(before_checksum == after_checksum){                                                                          \
        printf("SYSRAM checksum PASS\r\n");                                                                         \
    }else{                                                                                                          \
        printf("before_checksum = 0x%08X\r\n", before_checksum);                                                    \
        printf("after_checksum = 0x%08X\r\n", after_checksum);                                                      \
    }                                                                                                               \
}

extern int8_t hal_lp_connsys_give_n9_own(void);
extern int8_t hal_lp_connsys_get_own_enable_int(void);
extern int8_t hal_lp_connsys_get_ownership(void);
extern void hal_lp_deep_sleep_set_rgu(void);
extern void hal_lp_legacy_sleep_set_rgu(void);
extern void hal_lp_deep_sleep(void);
extern void hal_lp_legacy_sleep(void);
extern void hal_lp_handle_intr(void);
extern uint8_t hal_lp_get_wic_wakeup(void);
extern uint32_t hal_lp_get_wic_status(void);

#ifdef __cplusplus
}
#endif

#endif /* __LOW_HAL_LP_H__ */

