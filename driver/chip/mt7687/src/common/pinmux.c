/* Copyright Statement:
 *
 */

/****************************************************************************
    Module Name:
    Pinmux

    Abstract:
    Configure pinmux settings.

    Revision History:
    Who         When            What
    --------    ----------      ------------------------------------------
***************************************************************************/

#include "hal_gpio.h"
#ifdef HAL_GPIO_MODULE_ENABLED

#include "type_def.h"
#include "hal_pinmux.h"
#include "pinmux.h"

int32_t pinmux_config(ENUM_IOT_GPIO_NAME_T gpio_index, uint32_t function)
{
    ENUM_PAD_NAME_T ePadIndex;

    // TODO: check if selected function belonging to gpio_index

    switch (gpio_index) {
        case eIOT_GPIO_IDX_0:

            ePadIndex = ePAD_ANTSEL0;

            break;
        case eIOT_GPIO_IDX_1:

            ePadIndex = ePAD_ANTSEL1;

            break;
        case eIOT_GPIO_IDX_2:

            ePadIndex = ePAD_ANTSEL2;

            break;
        case eIOT_GPIO_IDX_3:

            ePadIndex = ePAD_ANTSEL3;

            break;
        case eIOT_GPIO_IDX_4:

            ePadIndex = ePAD_ANTSEL4;

            break;
        case eIOT_GPIO_IDX_5:

            ePadIndex = ePAD_ANTSEL5;

            break;
        case eIOT_GPIO_IDX_6:

            ePadIndex = ePAD_ANTSEL6;

            break;
        case eIOT_GPIO_IDX_7:

            ePadIndex = ePAD_ANTSEL7;

            break;
        case eIOT_GPIO_IDX_24:

            ePadIndex = ePAD_PERST_N;

            break;
        case eIOT_GPIO_IDX_25:

            ePadIndex = ePAD_WAKE_N;

            break;
        case eIOT_GPIO_IDX_26:

            ePadIndex = ePAD_CLK_REQ_N;

            break;
        case eIOT_GPIO_IDX_27:

            ePadIndex = ePAD_SDIO_CLK;

            break;
        case eIOT_GPIO_IDX_28:

            ePadIndex = ePAD_SDIO_CMD;

            break;
        case eIOT_GPIO_IDX_29:

            ePadIndex = ePAD_SDIO_DAT3;

            break;
        case eIOT_GPIO_IDX_30:

            ePadIndex = ePAD_SDIO_DAT2;

            break;
        case eIOT_GPIO_IDX_31:

            ePadIndex = ePAD_SDIO_DAT1;

            break;
        case eIOT_GPIO_IDX_32:

            ePadIndex = ePAD_SDIO_DAT0;

            break;
        case eIOT_GPIO_IDX_33:

            ePadIndex = ePAD_GPIO0;

            break;
        case eIOT_GPIO_IDX_34:

            ePadIndex = ePAD_GPIO1;

            break;
        case eIOT_GPIO_IDX_35:

            ePadIndex = ePAD_UART_DBG;

            break;
        case eIOT_GPIO_IDX_36:

            ePadIndex = ePAD_UART_RX;

            break;
        case eIOT_GPIO_IDX_37:

            ePadIndex = ePAD_UART_TX;

            break;
        case eIOT_GPIO_IDX_38:

            ePadIndex = ePAD_UART_RTS;

            break;
        case eIOT_GPIO_IDX_39:

            ePadIndex = ePAD_UART_CTS;

            break;
        case eIOT_GPIO_IDX_57:

            ePadIndex = ePAD_WF_RF_DIS_B;

            break;
        case eIOT_GPIO_IDX_58:

            ePadIndex = ePAD_BT_RF_DIS_B;

            break;
        case eIOT_GPIO_IDX_59:

            ePadIndex = ePAD_WF_LED_B;

            break;
        case eIOT_GPIO_IDX_60:

            ePadIndex = ePAD_BT_LED_B;

            break;
        default:
            return -1;
    }

    halPinmuxTopOnPadFunc(ePadIndex, function);

    return 0;
}
#endif

