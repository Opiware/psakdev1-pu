/* Copyright Statement:
 *
 */

#include <stdlib.h>
#include "hal_sys.h"
#include "hal_wdt.h"

#include "type_def.h"

static hal_sys_reboot_callback_t s_callback = NULL;

hal_sys_reboot_callback_t hal_sys_reboot_register_callback(hal_sys_reboot_callback_t callback)
{
    hal_sys_reboot_callback_t old_callback = s_callback;
    s_callback = callback;
    return old_callback;
}


hal_sys_status_t hal_sys_reboot(uint32_t magic, uint32_t command)
{
   #ifdef HAL_WDT_MODULE_ENABLED
      hal_wdt_config_t wdt_init;
   #endif
 if (magic != HAL_SYS_REBOOT_MAGIC) {
        return HAL_SYS_INVALID_MAGIC;
    }

    if (command == WHOLE_SYSTEM_REBOOT_COMMAND) {
        hal_sys_reboot_callback_t callback = s_callback;
        if (callback != NULL) {
            callback(command);
        }

	#ifdef HAL_WDT_MODULE_ENABLED	
	wdt_init.mode = HAL_WDT_MODE_RESET;
	wdt_init.seconds = 1;
        hal_wdt_init(&wdt_init);
	hal_wdt_software_reset();

       #endif
        while (1);

    } else if (command == 0x12345678) {

    }

    return HAL_SYS_OK;
}

