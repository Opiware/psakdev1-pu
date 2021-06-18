/* Copyright Statement:
 *
 */

#include <stdlib.h>
#include "hal_sys.h"
#include "low_hal_wdt.h"
#include "mt7687_cm4_hw_memmap.h"
#include "type_def.h"

static hal_sys_reboot_callback_t s_callback = NULL;

//P_IOT_CM4_RGU_MEM_CTRL_TypeDef pCM4RguMemCtrlTypeDef = (P_IOT_CM4_RGU_MEM_CTRL_TypeDef)(CM4_TOPRGU_BASE + IOT_CM4_RGU_MEM_CTRL_OFFSET);

hal_sys_reboot_callback_t hal_sys_reboot_register_callback(hal_sys_reboot_callback_t callback)
{
    hal_sys_reboot_callback_t old_callback = s_callback;
    s_callback = callback;
    return old_callback;
}


hal_sys_status_t hal_sys_reboot(uint32_t magic, uint32_t command)
{
    if (magic != HAL_SYS_REBOOT_MAGIC) {
        return HAL_SYS_INVALID_MAGIC;
    }

    if (command == WHOLE_SYSTEM_REBOOT_COMMAND) {
        hal_sys_reboot_callback_t callback = s_callback;
        if (callback != NULL) {
            callback(command);
        }

        /*call hardware reboot here!!! WDT HW timer trigger whole chip reset*/
        //CR 0x8300917C[16] = 1 : CM4 WDT whole chip mode, CM4 WDT reset whole chip included N9 domain
        //DRV_Reg32(pCM4RguMemCtrlTypeDef -> CM4_FPGA_RGU_DUMMY_CR) |=  BIT(16);

        halWDTConfig(0, 0, 0, 1); //CM4_WDT_RESET_MODE

        //halWDTSetTimeout(1);
        // Kick WDT to count down
        //halWDTEnable(1);
        halWDTSoftwareReset(); //trigger WDT immediatly

        while (1)
            ;
    } else if (command == 0x12345678) {
#if 0
        // this is an example of rebooting some subsystem, but not implmented.
        return HAL_SYS_INVALID_COMMAND;
#endif
    }

    return HAL_SYS_OK;
}

