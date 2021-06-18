/* Copyright Statement:
 *
 */

/**
 * @author  MTK
 * @version 1.0
 * @date    2015.10.29
 * */

#ifndef __HAL_SYS_TOPSM_H__
#define __HAL_SYS_TOPSM_H__

#include "hal_platform.h"
#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_sleep_manager_platform.h"

typedef enum {
    HAL_SYS_TOPSM_MTCMOS_BTSYS,
    HAL_SYS_TOPSM_MTCMOS_MMSYS,
    HAL_SYS_TOPSM_MTCMOS_MD2G,
    HAL_SYS_TOPSM_MTCMOS_INFRA,
    HAL_SYS_TOPSM_MTCMOS_CMSYS,
    HAL_SYS_TOPSM_MTCMOS_DEBUG
} hal_sys_topsm_mtcmos_enum_t;

/*  SYS_TOPSM_BASE: 0xA20F0000 is used for Larkspur */
#define SYS_TOPSM_RM_PWR_STA                 ((volatile uint32_t*)(SYS_TOPSM_BASE+0x820))  /* Power Status Register  */
#define SYS_TOPSM_RM_TMR_PWR0                ((volatile uint32_t*)(SYS_TOPSM_BASE+0x14))  /* Resource Manager Timer Power Enable Control 0 */
#define SYS_TOPSM_RM_PWR_CON2                ((volatile uint32_t*)(SYS_TOPSM_BASE+0x808))       /* Power Control Register (SW or HW mode) */
#define SYS_TOPSM_RM_PWR_CON1                ((volatile uint32_t*)(SYS_TOPSM_BASE+0x804))       /* Power Control Register (SW or HW mode) */
#define SYS_TOPSM_RM_PWR_CON3                ((volatile uint32_t*)(SYS_TOPSM_BASE+0x80C))       /* Power Control Register (SW or HW mode) */
#define SYS_TOPSM_TOPSM_DBG                  ((volatile uint32_t*)(SYS_TOPSM_BASE+0x50))        /* Sleep Manager Debug Control */

#define SYS_TOPSM_RM_SM_MASK                 ((volatile uint32_t*)(SYS_TOPSM_BASE+0x890))       /* Sleep Manager Enable Control */
#define SYS_TOPSM_RM_SM_PWR                  ((volatile uint32_t*)(SYS_TOPSM_BASE+0x850))       /* Sleep Manager Enable Control */
#define SYS_TOPSM_SW_CLK_FORCE_ON_SET        ((volatile uint32_t*)(SYS_TOPSM_BASE+0xA04))       /* Software Clock Force On Set */
#define SYS_TOPSM_SM_SLV_REQ_STA             ((volatile uint32_t*)(SYS_TOPSM_BASE+0x8E0))       /* Sleep Manager Request Status */
#define SYS_TOPSM_RM_PWR_CON0                ((volatile uint16_t*)(SYS_TOPSM_BASE+0x800))       /* Power Control Register */
#define SYS_TOPSM_DBG_RM_SM_MASK             ((volatile uint32_t*)(SYS_TOPSM_BASE+0x880))       /* Sleep Manager Debug Control Mask */
#define SYS_TOPSM_INDIV_CLK_PROTECT_ACK_MASK ((volatile uint32_t*)(SYS_TOPSM_BASE+0xA34))
#define SYS_TOPSM_CCF_CLK_CON                ((volatile uint32_t*)(SYS_TOPSM_BASE+0x200))

void sys_topsm_mtcmos_control(hal_sys_topsm_mtcmos_enum_t mtcmos, bool config);
void bootrom_system_power_default_setup(void); /*Restore the power domain to boot time*/
void sys_topsm_init(void); /*init sys topsm*/
void sys_topsm_debug_log(hal_sys_topsm_mtcmos_enum_t mtcmos);

#endif /* HAL_SLEEP_MANAGER_ENABLED */
#endif /* __HAL_SYS_TOPSM_H__ */
