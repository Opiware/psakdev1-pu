/* Copyright Statement:
 *
 */

#include "hal_gpc.h"

#ifdef HAL_GPC_MODULE_ENABLED
#include <stdbool.h>
#include <stdio.h>
#include "type_def.h"
#include "mt7687_cm4_hw_memmap.h"
#include "hal_pcnt.h"

#define IOT_PCNT_CTRL   0x1A0
#define PCNT_EN 31
#define PCNT_CLR 30
#define PCNT_EDGE 29

hal_pcnt_status_t hal_pcnt_config(bool enable, hal_pcnt_edge_t edge)
{

    if (edge != HAL_PCNT_EDGE_FALLING && edge != HAL_PCNT_EDGE_RAISING) {
        return HAL_PCNT_STATUS_INVALID_PARAMETER;
    }

    // handle hardware setting here.
    if (enable == TRUE) {
        DRV_Reg32(CM4_TOPCFGAON_BASE + IOT_PCNT_CTRL) |= ((uint32_t)1 << PCNT_EN); // Enable PCNT

        if (edge == HAL_PCNT_EDGE_RAISING) {
            DRV_Reg32(CM4_TOPCFGAON_BASE + IOT_PCNT_CTRL) |= (1 << PCNT_EDGE);    // RAISING edge
        } else {
            DRV_Reg32(CM4_TOPCFGAON_BASE + IOT_PCNT_CTRL) &= ~(1 << PCNT_EDGE);    // FALLING edge
        }

    } else {
        DRV_Reg32(CM4_TOPCFGAON_BASE + IOT_PCNT_CTRL) &= ~((uint32_t)1 << PCNT_EN); // Enable PCNT

    }

    return HAL_PCNT_STATUS_OK;
}


uint32_t hal_pcnt_read_and_clear(void)
{
    uint32_t    reg = 0;

    // read cr and clear cr here
    reg = DRV_Reg32(CM4_TOPCFGAON_BASE + IOT_PCNT_CTRL) & 0x1FFFFFFF;
    DRV_Reg32(CM4_TOPCFGAON_BASE + IOT_PCNT_CTRL) |= (1 << PCNT_CLR);

    return reg;
}

#endif

