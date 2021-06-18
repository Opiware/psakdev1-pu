/* Copyright Statement:
 *
 */

#include "eint_key_custom.h"
#include "eint_key.h"
#include "hal_gpio.h"
#include "hal_log.h"
#include "assert.h"

extern const char BSP_EINTKEY0_PIN;
extern const char BSP_EINTKEY1_PIN;
extern const char BSP_EINTKEY2_PIN;

extern const char BSP_EINTKEY0_PIN_M_EINT;
extern const char BSP_EINTKEY1_PIN_M_EINT;
extern const char BSP_EINTKEY2_PIN_M_EINT;

extern const unsigned char BSP_EINTKEY0_EINT;
extern const unsigned char BSP_EINTKEY1_EINT;
extern const unsigned char BSP_EINTKEY2_EINT;


/*config the GPIO, eint mode, eint number, keyad data */
bsp_eint_key_mapping_t eint_key_mapping[BSP_EINT_KEY_NUMBER] = {
    {HAL_GPIO_0,  HAL_GPIO_0_EINT0, HAL_EINT_NUMBER_0, BSP_EINT_KEY_DATA0},
};



void eint_key_custom_init(void)
{

#ifdef EINT_KEY_USED_EPT_CONFIGURATION
    uint32_t i;

    if ((BSP_EINTKEY0_PIN == 0xff) && (BSP_EINTKEY1_PIN == 0xff) && (BSP_EINTKEY2_PIN == 0xff)) {
        log_hal_info("[eint_key]eint key pin has not been configured by ept tool\r\n");
        assert(0);
    }
    
    eint_key_mapping[0].gpio_port = BSP_EINTKEY0_PIN;
    eint_key_mapping[1].gpio_port = BSP_EINTKEY1_PIN;
    eint_key_mapping[2].gpio_port = BSP_EINTKEY2_PIN;

    eint_key_mapping[0].eint_mode = BSP_EINTKEY0_PIN_M_EINT;
    eint_key_mapping[1].eint_mode = BSP_EINTKEY1_PIN_M_EINT;
    eint_key_mapping[2].eint_mode = BSP_EINTKEY2_PIN_M_EINT;

    eint_key_mapping[0].eint_number = BSP_EINTKEY0_EINT;
    eint_key_mapping[1].eint_number = BSP_EINTKEY1_EINT;
    eint_key_mapping[2].eint_number = BSP_EINTKEY2_EINT;

    eint_key_mapping[0].key_data = BSP_EINT_KEY_DATA0;
    eint_key_mapping[1].key_data = BSP_EINT_KEY_DATA1;
    eint_key_mapping[2].key_data = BSP_EINT_KEY_DATA2;

    for (i=0; i<BSP_EINT_KEY_NUMBER; i++) {
        log_hal_info("[eint_key]led%d: gpio = %d; mode = %d; eint=%d; key_data = %d\r\n", \
             i, \
             eint_key_mapping[i].gpio_port, \
             eint_key_mapping[i].eint_mode, \
             eint_key_mapping[i].eint_number, \
             eint_key_mapping[i].key_data);
    }
#endif

}


