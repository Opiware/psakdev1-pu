/* Copyright Statement:
 *
 */

#include "bsp_gpio_ept_config.h"
#include "mt2523.h"
#include "ept_gpio_drv.h"



GPIO_REGISTER_T *gpio_base_add = (GPIO_REGISTER_T *)GPIO_BASE;

#define GPIO_MODE_MASK_BIT     0xF

/* joint together the MACROs generated by EPT to 32-bits data as a result of the GPIO register is 32-bit,
   the data will be written to corresponding register after jointed.
*/
#define GPIO_HWORD_REG_VAL(name, port0, port1, port2, port3, port4, port5, port6, port7, port8, port9, port10, \
	                            port11, port12, port13, port14, port15, port16, port17, port18, port19, port20, port21, \
                               port22, port23, port24, port25, port26, port27, port28, port29, port30, port31)      \
((GPIO_PORT##port0##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*0) & 0x1f)) | \
(GPIO_PORT##port1##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*1) & 0x1f)) |	\
(GPIO_PORT##port2##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*2) & 0x1f)) |   \
(GPIO_PORT##port3##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*3) & 0x1f)) |	\
(GPIO_PORT##port4##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*4) & 0x1f)) | \
(GPIO_PORT##port5##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*5) & 0x1f)) | 	\
(GPIO_PORT##port6##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*6) & 0x1f)) | \
((uint32_t)(GPIO_PORT##port7##_##name)<<((GPIO_##name##_##ONE_CONTROL_BITS*7) & 0x1f)) | 	\
(GPIO_PORT##port8##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*8) & 0x1f)) | \
(GPIO_PORT##port9##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*9) & 0x1f)) |	\
(GPIO_PORT##port10##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*10) & 0x1f)) |\
(GPIO_PORT##port11##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*11) & 0x1f)) |	\
(GPIO_PORT##port12##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*12) & 0x1f)) | \
(GPIO_PORT##port13##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*13) & 0x1f)) | 	\
(GPIO_PORT##port14##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*14) & 0x1f)) | \
(GPIO_PORT##port15##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*15) & 0x1f)) | 	\
(GPIO_PORT##port16##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*16) & 0x1f)) | \
(GPIO_PORT##port17##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*17) & 0x1f)) |	\
(GPIO_PORT##port18##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*18) & 0x1f)) |	\
(GPIO_PORT##port19##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*19) & 0x1f)) |	\
(GPIO_PORT##port20##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*20) & 0x1f)) | \
(GPIO_PORT##port21##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*21) & 0x1f)) | 	\
(GPIO_PORT##port22##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*22) & 0x1f)) | \
(GPIO_PORT##port23##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*23) & 0x1f)) | 	\
(GPIO_PORT##port24##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*24) & 0x1f)) | \
(GPIO_PORT##port25##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*25) & 0x1f)) |	\
(GPIO_PORT##port26##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*26) & 0x1f)) |	\
(GPIO_PORT##port27##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*27) & 0x1f)) |	\
(GPIO_PORT##port28##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*28) & 0x1f)) | \
(GPIO_PORT##port29##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*29) & 0x1f)) | 	\
(GPIO_PORT##port30##_##name<<((GPIO_##name##_##ONE_CONTROL_BITS*30) & 0x1f)) | \
((uint32_t)(GPIO_PORT##port31##_##name)<<((GPIO_##name##_##ONE_CONTROL_BITS*31) & 0x1f) ))




/**
  * @brief  write the joint data about GPIO mode to GPIO mode register one by one
  * @param  None
  * @retval None
  */
void gpio_mode_init(void)
{
    uint32_t i, j, remainder_bit;

#ifdef GPIO_MODE_REG_MAX_NUM
    uint32_t mode_temp[GPIO_MODE_REG_MAX_NUM + 1] = { GPIO_MODE_ALL_VALUE };


    for (i = 0; i < GPIO_MODE_REG_MAX_NUM; i++) {
        gpio_base_add->GPIO_MODE_REGISTER[i].GPIO_MODE = mode_temp[i];
    }

    /* only configure the pins needed */
    if (!(GPIO_PIN_NUMBER % GPIO_MODE_ONE_REG_CONTROL_NUM)) {
        gpio_base_add->GPIO_MODE_REGISTER[i].GPIO_MODE = mode_temp[i];
    }

    else {
        remainder_bit = 0;
        for (j = 0; j < (GPIO_PIN_NUMBER % GPIO_MODE_ONE_REG_CONTROL_NUM); j ++) {
            remainder_bit |= (GPIO_MODE_MASK_BIT << (GPIO_MODE_ONE_CONTROL_BITS * j));
        }

        gpio_base_add->GPIO_MODE_REGISTER[i].GPIO_MODE_CLR |= remainder_bit;
        gpio_base_add->GPIO_MODE_REGISTER[i].GPIO_MODE_SET |= (mode_temp[i] & remainder_bit);
    }

#endif
}



/**
  * @brief  write the joint data about GPIO direction configuration to GPIO direction register one by one
  * @param  None
  * @retval None
  */
void gpio_dir_init(void)
{
    uint32_t i;

#ifdef GPIO_DIR_REG_MAX_NUM
    uint32_t dir_temp[GPIO_DIR_REG_MAX_NUM + 1] = { GPIO_DIR_ALL_VALUE };

    for (i = 0; i <= GPIO_DIR_REG_MAX_NUM; i++) {
        gpio_base_add->GPIO_DIR_REGISTER[i].GPIO_DIR = dir_temp[i];
    }
#endif
}



/**
  * @brief  write the joint data about GPIO pull configuration about pullsel to GPIO pullsel register one by one
  * @param  None
  * @retval None
  */
void gpio_pull_sel_init(void)
{
    uint32_t i;

#ifdef GPIO_PULL_SEL_REG_MAX_NUM
    uint32_t pullsel_temp[GPIO_PULL_SEL_REG_MAX_NUM + 1] = { GPIO_PULL_SEL_ALL_VALUE };

    for (i = 0; i <= GPIO_PULL_SEL_REG_MAX_NUM; i++) {
        gpio_base_add->GPIO_PULLSEL_REGISTER[i].GPIO_PULLSEL = pullsel_temp[i];
    }
#endif
}



/**
  * @brief  write the joint data about GPIO pull configuration about pullen to GPIO pullen register one by one
  * @param  None
  * @retval None
  */
void gpio_pullen_init(void)
{
    uint32_t i;

#ifdef GPIO_PULL_REG_MAX_NUM
    uint32_t pullen_temp[GPIO_PULL_REG_MAX_NUM + 1] = { GPIO_PULL_ALL_VALUE };


    for (i = 0; i <= GPIO_PULL_REG_MAX_NUM; i++) {
        gpio_base_add->GPIO_PULLEN_REGISTER[i].GPIO_PULLEN = pullen_temp[i];
    }
#endif
}



/**
  * @brief  write the joint data about GPIO output data to GPIO output data register one by one
  * @param  None
  * @retval None
  */
void gpio_output_init(void)
{
    uint32_t i;

#ifdef GPIO_OUTPUT_LEVEL_REG_MAX_NUM
    uint32_t dout_temp[GPIO_OUTPUT_LEVEL_REG_MAX_NUM + 1] = { GPIO_OUTPUT_LEVEL_ALL_VALUE };

    for (i = 0; i <= GPIO_OUTPUT_LEVEL_REG_MAX_NUM; i++) {
        gpio_base_add->GPIO_DOUT_REGISTER[i].GPIO_DOUT = dout_temp[i];
    }
#endif
}


/**
  * @brief  write the joint data about GPIO pull configuration about PUPD to GPIO pupd register one by one
  * @param  None
  * @retval None
  */
void gpio_pupd_init(void)
{
    uint32_t i;

#ifdef GPIO_PUPD_REG_MAX_NUM
    uint32_t pupd_temp[GPIO_PUPD_REG_MAX_NUM + 1] = { GPIO_PUPD_ALL_VALUE };

    for (i = 0; i <= GPIO_PUPD_REG_MAX_NUM; i++) {
        gpio_base_add->GPIO_PUPD_REGISTER[i].GPIO_PUPD = pupd_temp[i];
    }
#endif
}


/**
  * @brief  write the joint data about GPIO pull configuration about R0 to GPIO R0 register one by one
  * @param  None
  * @retval None
  */
void gpio_r0_init(void)
{
    uint32_t i;

#ifdef GPIO_R0_REG_MAX_NUM
    uint32_t r0_temp[GPIO_R0_REG_MAX_NUM + 1] = { GPIO_R0_ALL_VALUE };

    for (i = 0; i <= GPIO_R0_REG_MAX_NUM; i++) {
        gpio_base_add->GPIO_RESEN0_REGISTER[i].GPIO_RESEN0 = r0_temp[i];
    }
#endif
}


/**
  * @brief  write the joint data about GPIO pull configuration about R1 to GPIO R1 register one by one
  * @param  None
  * @retval None
  */
void gpio_r1_init(void)
{
    uint32_t i;

#ifdef GPIO_R1_REG_MAX_NUM
    uint32_t r1_temp[GPIO_R1_REG_MAX_NUM + 1] = { GPIO_R1_ALL_VALUE };

    for (i = 0; i <= GPIO_R1_REG_MAX_NUM; i++) {
        gpio_base_add->GPIO_RESEN1_REGISTER[i].GPIO_RESEN1 = r1_temp[i];
    }
#endif
}



/**
  * @brief  Main program to make the configuration of EPT to take effect
  * @param  None
  * @retval None
  */
void bsp_ept_gpio_setting_init(void)
{
    gpio_mode_init();
    gpio_dir_init();
    gpio_pull_sel_init();
    gpio_pullen_init();
    gpio_output_init();
    gpio_pupd_init();
    gpio_r0_init();
    gpio_r1_init();
}

