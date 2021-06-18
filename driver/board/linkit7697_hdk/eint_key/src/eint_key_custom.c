/* Copyright Statement:
 *
 */

#include "eint_key_custom.h"
#include "eint_key.h"
#include "hal_gpio.h"

/*config the GPIO, eint mode, eint number, keyad data */
bsp_eint_key_mapping_t const eint_key_mapping[BSP_EINT_KEY_NUMBER] = {
    {HAL_GPIO_0,  HAL_GPIO_0_EINT0, HAL_EINT_NUMBER_0, BSP_EINT_KEY_DATA0},
};


void eint_key_custom_init(void) 
{

	//:todo add EPT configuration
}


