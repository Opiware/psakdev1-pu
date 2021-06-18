/* Copyright Statement:
 *
 */

#ifdef MTK_CTP_ENABLE
#include "touch_panel_custom_ite.h"
#include "ctp.h"
#include "assert.h"
#include "hal_log.h"

extern const unsigned char BSP_CTP_EINT;
extern const char BSP_CTP_RST_PIN;
extern const char BSP_CTP_EINT_PIN;
extern const char BSP_CTP_EINT_PIN_M_GPIO;
extern const char BSP_CTP_EINT_PIN_M_EINT;
//extern const char BSP_CTP_SW_I2C_SCL_PIN;
//extern const char BSP_CTP_SW_I2C_SCL_SDA;



void touch_panel_ite_custom_data_init(void)
{
    ctp_context.x_coord_start            = CTP_ITE_COORD_X_START;
    ctp_context.x_coord_end              = CTP_ITE_COORD_X_END;
    ctp_context.y_coord_start            = CTP_ITE_COORD_Y_START;
    ctp_context.y_coord_end              = CTP_ITE_COORD_Y_END;

    ctp_context.verndor_x_coord_start    = CTP_ITE_COORD_VENDOR_X_START;
    ctp_context.verndor_x_coord_end      = CTP_ITE_COORD_VENDOR_X_END;
    ctp_context.verndor_y_coord_start    = CTP_ITE_COORD_VENDOR_Y_START;
    ctp_context.verndor_y_coord_end      = CTP_ITE_COORD_VENDOR_Y_END;

    ctp_context.pen_move_offset          = ITE_PEN_MOVE_OFFSET;
    ctp_context.pen_longtap_offset       = ITE_PEN_LONGTAP_OFFSET;

    if ((BSP_CTP_RST_PIN == 0xff)  || \
            (BSP_CTP_EINT_PIN == 0xff) || \
            (BSP_CTP_EINT == 0xff)) {
        log_hal_info("[CTP] ept tool pin setting error\r\n");
        log_hal_info("[CTP]BSP_CTP_RST_PIN= %x, BSP_CTP_EINT_PIN=%x, BSP_CTP_EINT=%x\r\n", \
                     BSP_CTP_RST_PIN, BSP_CTP_EINT_PIN, BSP_CTP_EINT);
        assert(0);
    }

    if (ctp_config_info.is_external_initialized == false) {
        if (ctp_config_info.ctp_i2c.has_initialized != true) {
            /* i2c conifg information */
            ctp_config_info.ctp_i2c.i2c_type                   = CTP_USE_HARDWARE_I2C;
            //ctp_config_info.ctp_i2c.scl_pin                    = (hal_gpio_pin_t)BSP_CTP_SW_I2C_SCL_PIN;
            //ctp_config_info.ctp_i2c.sda_pin                    = (hal_gpio_pin_t)BSP_CTP_SW_I2C_SCL_SDA;
            ctp_config_info.ctp_i2c.speed                      = HAL_I2C_FREQUENCY_400K;
            ctp_config_info.ctp_i2c.i2c_port                   = HAL_I2C_MASTER_0;
            ctp_config_info.reg_address_byte                   = 1;
        }

        if (ctp_config_info.ctp_eint.has_initialized != true) {
            /* eint conifg information */
            ctp_config_info.ctp_eint.eint_pin                  = (hal_gpio_pin_t)BSP_CTP_EINT_PIN;
            ctp_config_info.ctp_eint.eint_num                  = (hal_eint_number_t)BSP_CTP_EINT;
            ctp_config_info.ctp_eint.eint_mode                 = (uint8_t)BSP_CTP_EINT_PIN_M_EINT;
            ctp_config_info.ctp_eint.gpio_mode                 = (uint8_t)BSP_CTP_EINT_PIN_M_GPIO;
            ctp_config_info.ctp_eint.init_config.trigger_mode  = CTP_ITE_EINT_TRIGGER_TYPE;
            ctp_config_info.ctp_eint.init_config.debounce_time = 0;
            ctp_config_info.ctp_eint.has_initialized           = true;
        }

        /* reset conifg information */
        ctp_config_info.reset_pin = (hal_gpio_pin_t)BSP_CTP_RST_PIN;
    }

    log_hal_info("[CTP]get ept tool pin setting parameter, width=%d, height=%d", ITE_LCD_WIDTH, ITE_LCD_HEIGHT);
    log_hal_info("[CTP]BSP_CTP_RST_PIN         = %d", BSP_CTP_RST_PIN);
    log_hal_info("[CTP]BSP_CTP_EINT_PIN        = %d", BSP_CTP_EINT_PIN);
    log_hal_info("[CTP]BSP_CTP_EINT            = %d", BSP_CTP_EINT);
    log_hal_info("[CTP]BSP_CTP_EINT_PIN_M_EINT = %d", BSP_CTP_EINT_PIN_M_EINT);
    log_hal_info("[CTP]BSP_CTP_EINT_PIN_M_GPIO = %d", BSP_CTP_EINT_PIN_M_GPIO);


}

#endif /*MTK_CTP_ENABLE*/

