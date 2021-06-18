/* Copyright Statement:
 *
 */

#ifndef __HAL_GPIO_INTERNAL_H__
#define __HAL_GPIO_INTERNAL_H__

#include "hal_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAL_GPIO_MODULE_ENABLED

#define GPIO_REG_ONE_BIT_SET_CLR            0x1
#define GPIO_REG_TWO_BIT_SET_CLR            0x3
#define GPIO_REG_FOUR_BIT_SET_CLR           0xF
#define GPIO_MODE_MIN_NUMBER                0       /*  minimum function index of GPIO  */
#define GPIO_MODE_MAX_NUMBER                16      /*  maximum function index of GPIO  */
#define GPIO_REG_CTRL_PIN_NUM_OF_32         32      /*  pin munber controlled by one register is 32  */
#define GPIO_MODE_FUNCTION_CTRL_BITS        4       /*  mode function is controlled by 4 bits  */
#define GPIO_TDSEL_FUNCTION_CTRL_BITS       2       /*  TDSEL function is controlled by 2 bits  */
#define GPIO_DRV_FUNCTION_CTRL_BITS         2       /*  DRV function is controlled by 2 bits  */
#define GPIO_DIR_REG_CTRL_PIN_NUM           32      /*  pin munber controlled by direction register is 32  */
#define GPIO_MODE_REG_CTRL_PIN_NUM          8       /*  pin munber controlled by mode register is 8  */
#define GPIO_DIN_REG_CTRL_PIN_NUM           32      /*  pin munber controlled by inputd data register is 32  */
#define GPIO_DOUT_REG_CTRL_PIN_NUM          32      /*  pin munber controlled by output data register is 32  */
#ifdef HAL_GPIO_FEATURE_INVERSE
#define GPIO_DINV_REG_CTRL_PIN_NUM          32      /*  pin munber controlled by inputd data inverse register is 32  */
#endif
#define GPIO_PULL_CTRL_REG_CTRL_PIN_NUM     32      /*  pin munber controlled by pull control register is 32  */
#ifdef HAL_GPIO_FEATURE_PUPD
#define GPIO_PUPD_CTRL_REG_CTRL_PIN_NUM     32      /*  pin munber controlled by PUPD control register is 32  */
#endif
#define GPIO_TDSEL_REG_CTRL_PIN_NUM         16      /*  pin munber controlled by TDSEL register is 16  */
#define GPIO_IES_REG_CTRL_PIN_NUM           32      /*  pin munber controlled by IES register is 32  */
#define GPIO_SR_REG_CTRL_PIN_NUM            32      /*  pin munber controlled by SR register is 32  */
#define GPIO_DRV_REG_CTRL_PIN_NUM           16      /*  pin munber controlled by DRV register is 16  */

#ifdef __cplusplus
}
#endif

#endif /*HAL_GPIO_MODULE_ENABLED*/
#endif /*__HAL_GPIO_INTERNAL_H__*/
