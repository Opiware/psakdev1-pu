/* Copyright Statement:
 *
 */

#include "hal_platform.h"
#include "bsp_gpio_ept_config.h"
#include "ept_gpio_drv.h"


#define GPIO_WriteReg(addr,data)    ((*(volatile uint32_t *)(addr)) = (uint32_t)(data))
#define GPIO_ReadReg(addr)          (*(volatile uint32_t *)(addr))




/* joint together the MACROs generated by EPT to 32-bits data as a result of the GPIO register is 32-bit,
   the data will be written to corresponding register after jointed.
*/
#define GPIO_HWORD_REG_VAL(name, port0, port1, port2, port3, port4, port5, port6, port7, port8, port9, port10, \
                                port11, port12, port13, port14, port15, port16, port17, port18, port19, port20, port21, \
                               port22, port23, port24, port25, port26, port27, port28, port29, port30, port31)      \
((GPIO_PORT##port0##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*0) & 0x1f)) | \
(GPIO_PORT##port1##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*1) & 0x1f)) |    \
(GPIO_PORT##port2##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*2) & 0x1f)) |   \
(GPIO_PORT##port3##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*3) & 0x1f)) |    \
(GPIO_PORT##port4##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*4) & 0x1f)) | \
(GPIO_PORT##port5##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*5) & 0x1f)) |    \
(GPIO_PORT##port6##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*6) & 0x1f)) | \
((uint32_t)(GPIO_PORT##port7##_##name)<<((GPIO_##name##_##ONE_CONTROL_BITS*7) & 0x1f)) |    \
(GPIO_PORT##port8##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*8) & 0x1f)) | \
(GPIO_PORT##port9##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*9) & 0x1f)) |    \
(GPIO_PORT##port10##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*10) & 0x1f)) |\
(GPIO_PORT##port11##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*11) & 0x1f)) |  \
(GPIO_PORT##port12##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*12) & 0x1f)) | \
(GPIO_PORT##port13##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*13) & 0x1f)) |  \
(GPIO_PORT##port14##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*14) & 0x1f)) | \
(GPIO_PORT##port15##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*15) & 0x1f)) |  \
(GPIO_PORT##port16##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*16) & 0x1f)) | \
(GPIO_PORT##port17##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*17) & 0x1f)) |  \
(GPIO_PORT##port18##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*18) & 0x1f)) |  \
(GPIO_PORT##port19##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*19) & 0x1f)) |  \
(GPIO_PORT##port20##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*20) & 0x1f)) | \
(GPIO_PORT##port21##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*21) & 0x1f)) |  \
(GPIO_PORT##port22##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*22) & 0x1f)) | \
(GPIO_PORT##port23##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*23) & 0x1f)) |  \
(GPIO_PORT##port24##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*24) & 0x1f)) | \
(GPIO_PORT##port25##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*25) & 0x1f)) |  \
(GPIO_PORT##port26##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*26) & 0x1f)) |  \
(GPIO_PORT##port27##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*27) & 0x1f)) |  \
(GPIO_PORT##port28##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*28) & 0x1f)) | \
(GPIO_PORT##port29##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*29) & 0x1f)) |  \
(GPIO_PORT##port30##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*30) & 0x1f)) | \
((uint32_t)(GPIO_PORT##port31##_##name)<<((GPIO_##name##_##ONE_CONTROL_BITS*31) & 0x1f) ))




/**
   * @brief write the joint data about GPIO mode to GPIO mode register one by one.
  * @param  None
  * @retval None
  */
void gpio_mode_init(void)
{
    uint32_t i;

#ifdef GPIO_MODE_REG_MAX_NUM
    uint32_t mode_temp[GPIO_MODE_REG_MAX_NUM + 1] = { GPIO_MODE_ALL_VALUE };

    for (i = 0; i <= GPIO_MODE_REG_MAX_NUM; i++) {
        GPIO_WriteReg(IOT_GPIO_PINMUX(i), mode_temp[i]);

    }
#endif

}


/**
   * @brief write the joint data about GPIO output enable configuration to GPIO output enable register one by one.
  * @param  None
  * @retval None
  */
void gpio_oe_init(void)
{
    uint32_t i;

#ifdef GPIO_OE_REG_MAX_NUM
    uint32_t oe_temp[GPIO_OE_REG_MAX_NUM + 1] = { GPIO_OE_ALL_VALUE };

    for (i = 0; i <= GPIO_OE_REG_MAX_NUM; i++) {
        GPIO_WriteReg(IOT_GPIO_OE(i), oe_temp[i]);
    }
#endif
}


/**
   * @brief write the joint data about GPIO input enable configuration to GPIO input enable register one by one.
  * @param  None
  * @retval None
  */
void gpio_ies_init(void)
{
    uint32_t i;

#ifdef GPIO_IES_REG_MAX_NUM
    uint32_t ies_temp[GPIO_IES_REG_MAX_NUM + 1] = { GPIO_IES_ALL_VALUE };

    for (i = 0; i <= GPIO_IES_REG_MAX_NUM; i++) {
        GPIO_WriteReg(IOT_GPIO_IES(i), ies_temp[i]);
    }

    /* Configure GPIO27 */
    GPIO_ReadReg(GPIO_SDIO_CLK) &= ~(0x2);
    GPIO_ReadReg(GPIO_SDIO_CLK) |= (GPIO_PORT27_IES << 1);
    GPIO_ReadReg(GPIO_SDIO_CLK) |= (1 << 11);

    /* Configure GPIO28 */
    GPIO_ReadReg(GPIO_SDIO_CMD) &= ~(0x2);
    GPIO_ReadReg(GPIO_SDIO_CMD) |= (GPIO_PORT28_IES << 1);
    GPIO_ReadReg(GPIO_SDIO_CMD) |= (1 << 11);

    /* Configure GPIO29 */
    GPIO_ReadReg(GPIO_SDIO_DATA3) &= ~(0x2);
    GPIO_ReadReg(GPIO_SDIO_DATA3) |= (GPIO_PORT29_IES << 1);
    GPIO_ReadReg(GPIO_SDIO_DATA3) |= (1 << 11);

    /* Configure GPIO30 */
    GPIO_ReadReg(GPIO_SDIO_DATA2) &= ~(0x2);
    GPIO_ReadReg(GPIO_SDIO_DATA2) |= (GPIO_PORT30_IES << 1);
    GPIO_ReadReg(GPIO_SDIO_DATA2) |= (1 << 11);

    /* Configure GPIO31 */
    GPIO_ReadReg(GPIO_SDIO_DATA1) &= ~(0x2);
    GPIO_ReadReg(GPIO_SDIO_DATA1) |= (GPIO_PORT31_IES << 1);
    GPIO_ReadReg(GPIO_SDIO_DATA1) |= (1 << 11);

    /* Configure GPIO32 */
    GPIO_ReadReg(GPIO_SDIO_DATA0) &= ~(0x2);
    GPIO_ReadReg(GPIO_SDIO_DATA0) |= (GPIO_PORT32_IES << 1);
    GPIO_ReadReg(GPIO_SDIO_DATA0) |= (1 << 11);
#endif
}


/**
   * @brief write the joint data about GPIO pull-up configuration to GPIO pull-up register one by one.
  * @param  None
  * @retval None
  */
void gpio_pull_up_init(void)
{
    uint32_t i;

#ifdef GPIO_PULL_UP_REG_MAX_NUM
    uint32_t pull_up_temp[GPIO_PULL_UP_REG_MAX_NUM + 1] = { GPIO_PULL_UP_ALL_VALUE };

    for (i = 0; i <= GPIO_PULL_UP_REG_MAX_NUM; i++) {
        GPIO_WriteReg(IOT_GPIO_PULL_UP(i), pull_up_temp[i]);
    }

    /* Configure GPIO27 */
    GPIO_ReadReg(GPIO_SDIO_CLK) &= ~(0x7 << 2);
    if(GPIO_PORT27_PULL_UP) {
        GPIO_ReadReg(GPIO_SDIO_CLK) |= 0x804;
    } else if (GPIO_PORT27_PULL_DOWN) {
        GPIO_ReadReg(GPIO_SDIO_CLK) |= 0x814;
    }

    /* Configure GPIO28 */
    GPIO_ReadReg(GPIO_SDIO_CMD) &= ~(0x7 << 2);
    if(GPIO_PORT28_PULL_UP) {
        GPIO_ReadReg(GPIO_SDIO_CMD) |= 0x804;
    } else if (GPIO_PORT28_PULL_DOWN) {
        GPIO_ReadReg(GPIO_SDIO_CMD) |= 0x814;
    }

    /* Configure GPIO29 */
    GPIO_ReadReg(GPIO_SDIO_DATA3) &= ~(0x7 << 2);
    if(GPIO_PORT29_PULL_UP) {
        GPIO_ReadReg(GPIO_SDIO_DATA3) |= 0x804;
    } else if (GPIO_PORT29_PULL_DOWN) {
        GPIO_ReadReg(GPIO_SDIO_DATA3) |= 0x814;
    }

    /* Configure GPIO30 */
    GPIO_ReadReg(GPIO_SDIO_DATA2) &= ~(0x7 << 2);
    if(GPIO_PORT30_PULL_UP) {
        GPIO_ReadReg(GPIO_SDIO_DATA2) |= 0x804;
    } else if (GPIO_PORT30_PULL_DOWN) {
        GPIO_ReadReg(GPIO_SDIO_DATA2) |= 0x814;
    }

    /* Configure GPIO31 */
    GPIO_ReadReg(GPIO_SDIO_DATA1) &= ~(0x7 << 2);
    if(GPIO_PORT31_PULL_UP) {
        GPIO_ReadReg(GPIO_SDIO_DATA1) |= 0x804;
    } else if (GPIO_PORT31_PULL_DOWN) {
        GPIO_ReadReg(GPIO_SDIO_DATA1) |= 0x814;
    }

    /* Configure GPIO32 */
    GPIO_ReadReg(GPIO_SDIO_DATA0) &= ~(0x7 << 2);
    if(GPIO_PORT32_PULL_UP) {
        GPIO_ReadReg(GPIO_SDIO_DATA0) |= 0x804;
    } else if (GPIO_PORT32_PULL_DOWN) {
        GPIO_ReadReg(GPIO_SDIO_DATA0) |= 0x814;
    }
#endif
}



/**
   * @brief write the joint data about GPIO pull-down configuration to GPIO pull-down register one by one.
  * @param  None
  * @retval None
  */
void gpio_pull_down_init(void)
{
    uint32_t i;

#ifdef GPIO_PULL_DOWN_REG_MAX_NUM
    uint32_t pull_down_temp[GPIO_PULL_DOWN_REG_MAX_NUM + 1] = { GPIO_PULL_DOWN_ALL_VALUE };

    for (i = 0; i <= GPIO_PULL_DOWN_REG_MAX_NUM; i++) {
        GPIO_WriteReg(IOT_GPIO_PULL_DOWN(i), pull_down_temp[i]);
    }
#endif
}


/**
   * @brief write the joint data about GPIO output data to GPIO output data register one by one.
  * @param  None
  * @retval None
  */
void gpio_output_init(void)
{
    uint32_t i;

#ifdef GPIO_OUTPUT_REG_MAX_NUM
    uint32_t output_temp[GPIO_OUTPUT_REG_MAX_NUM + 1] = { GPIO_OUTPUT_ALL_VALUE };

    for (i = 0; i <= GPIO_OUTPUT_REG_MAX_NUM; i++) {
        GPIO_WriteReg(IOT_GPIO_OUTPUT(i), output_temp[i]);
    }

#endif
}

/**
  * @brief  
Set the GPIO default control by cm4 side
  * @param  None
  * @retval None
  */
void bsp_ept_gpio_set_control_by_cm4(void)
{
    /* TOP_PAD_CTL0 ~ 2, all GPIOs are controlled by CM4 */
    *((volatile uint32_t*)0x81021080) = 0xFFFFFFFF;
    *((volatile uint32_t*)0x81021084) = 0xFFFFFFFF;
    *((volatile uint32_t*)0x81021088) = 0x0300FFFF;
}

/**
  * @brief  Main program to make the configuration of EPT to take effect
  * @param  None
  * @retval None
  */
void bsp_ept_gpio_setting_init(void)
{
    gpio_mode_init();
    gpio_oe_init();
    gpio_ies_init();
    gpio_pull_up_init();
    gpio_pull_down_init();
    gpio_output_init();
}




