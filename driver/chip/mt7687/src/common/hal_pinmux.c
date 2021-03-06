/* Copyright Statement:
 *
 */

/*
** $Log: hal_pinmux.c $
**
**
**
*/

/*
    Porting from legacy/driver/hal_GPIO.c
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/


/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "hal_gpio.h"
#ifdef HAL_GPIO_MODULE_ENABLED

#include <stdio.h>
#include <string.h>
#include "type_def.h"
#include "top.h"
#include "hal_pinmux.h"
#include "hal_gpio_7687.h"


#define HAL_GPIO_DIRECTION_IN 0
/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/


/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

VOID halPinmuxTopOnPadFunc(ENUM_PAD_NAME_T ePadIndex, UINT8 ucFunc) //pinmux setting by gen_pmux_top_aon
{
    uint32_t temp;
    switch (ePadIndex) {
        case ePAD_ANTSEL0:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20);
            temp &= ~PAD_ANTSEL0_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20) = temp | (ucFunc << 0) ;
            break;
        case ePAD_ANTSEL1:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20); 
            temp &= ~PAD_ANTSEL1_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20) =  temp | (ucFunc << 4);
            break;
        case ePAD_ANTSEL2:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20); 
            temp &= ~PAD_ANTSEL2_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20) =  temp | (ucFunc << 8);
            break;
        case ePAD_ANTSEL3:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20); 
            temp &= ~PAD_ANTSEL3_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20) =  temp | (ucFunc << 12);
            break;
        case ePAD_ANTSEL4:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20);  
            temp &= ~PAD_ANTSEL4_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20) =  temp | (ucFunc << 16);
            break;
        case ePAD_ANTSEL5:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20); 
            temp &= ~PAD_ANTSEL5_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20) =  temp | (ucFunc << 20);
            break;
        case ePAD_ANTSEL6:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20);  
            temp &= ~PAD_ANTSEL6_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20) =  temp | (ucFunc << 24);
            break;
        case ePAD_ANTSEL7:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20);  
            temp &= ~PAD_ANTSEL7_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x20) =  temp | (ucFunc << 28);
            break;
        case ePAD_PERST_N:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C); 
            temp &= ~PAD_PERST_N_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C) =  temp | (ucFunc << 0);
            break;
        case ePAD_WAKE_N:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C);  
            temp &= ~PAD_WAKE_N_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C) =  temp | (ucFunc << 4);
            break;
        case ePAD_CLK_REQ_N:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C); 
            temp &= ~PAD_CLK_REQ_N_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C) =  temp | (ucFunc << 8);
            break;
        case ePAD_SDIO_CLK:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C);  
            temp &= ~PAD_SDIO_CLK_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C) =  temp | (ucFunc << 12);
            if (2 == ucFunc || 4 == ucFunc || 5 == ucFunc) {
                halGPIO_ConfDirection((UINT32)ePadIndex, HAL_GPIO_DIRECTION_IN);
            }
            break;
        case ePAD_SDIO_CMD:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C);  
            temp &= ~PAD_SDIO_CMD_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C) =  temp | (ucFunc << 16);
            if (4 == ucFunc || 5 == ucFunc) {
                halGPIO_ConfDirection((UINT32)ePadIndex, HAL_GPIO_DIRECTION_IN);
            }
            break;
        case ePAD_SDIO_DAT3:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C); 
            temp &= ~PAD_SDIO_DAT3_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C) =  temp | (ucFunc << 20);
            if (6 == ucFunc) {
                halGPIO_ConfDirection((UINT32)ePadIndex, HAL_GPIO_DIRECTION_IN);
            }
            break;
        case ePAD_SDIO_DAT2:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C); 
            temp &= ~PAD_SDIO_DAT2_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C) =  temp | (ucFunc << 24);
            if (4 == ucFunc || 7 == ucFunc) {
                halGPIO_ConfDirection((UINT32)ePadIndex, HAL_GPIO_DIRECTION_IN);
            }
            break;
        case ePAD_SDIO_DAT1:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C); 
            temp &= ~PAD_SDIO_DAT1_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x2C) =  temp | (ucFunc << 28);
            if (4 == ucFunc || 6 == ucFunc) {
                halGPIO_ConfDirection((UINT32)ePadIndex, HAL_GPIO_DIRECTION_IN);
            }
            break;
        case ePAD_SDIO_DAT0:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30);  
            temp &= ~PAD_SDIO_DAT0_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30) =  temp | (ucFunc << 0);
            if (4 == ucFunc || 6 == ucFunc) {
                halGPIO_ConfDirection((UINT32)ePadIndex, HAL_GPIO_DIRECTION_IN);
            }
            break;
        case ePAD_GPIO0:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30);  
            temp &= ~PAD_GPIO0_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30) =  temp | (ucFunc << 4);
            break;
        case ePAD_GPIO1:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30);  
            temp &= ~PAD_GPIO1_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30) =  temp | (ucFunc << 8);
            break;
        case ePAD_UART_DBG:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30); 
            temp &= ~PAD_UART_DBG_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30) =  temp | (ucFunc << 12);
            break;
        case ePAD_UART_RX:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30); 
            temp &= ~PAD_UART_RX_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30) =  temp | (ucFunc << 16);
            break;
        case ePAD_UART_TX:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30);
            temp &= ~PAD_UART_TX_PINMUX_AON_MASK; 
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30) = temp | (ucFunc << 20);;
            break;
        case ePAD_UART_RTS:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30);  
            temp &= ~PAD_UART_RTS_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30) =  temp | (ucFunc << 24);
            break;
        case ePAD_UART_CTS:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30);  
            temp &= ~PAD_UART_CTS_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x30) =  temp | (ucFunc << 28);
            break;
        case ePAD_WF_RF_DIS_B:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x3C);  
            temp &= ~PAD_WF_RF_DIS_B_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x3C) =  temp | (ucFunc << 4);
            break;
        case ePAD_BT_RF_DIS_B:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x3C);  
            temp &= ~PAD_BT_RF_DIS_B_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x3C) =  temp | (ucFunc << 8);
            break;
        case ePAD_WF_LED_B:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x3C);  
            temp &= ~PAD_WF_LED_B_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x3C) =  temp | (ucFunc << 12);
            break;
        case ePAD_BT_LED_B:
            //config GPIO pinmux
            temp = DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x3C);  
            temp &= ~PAD_BT_LED_B_PINMUX_AON_MASK;
            DRV_Reg32(IOT_GPIO_PINMUX_AON_BASE + 0x3C) =  temp | (ucFunc << 16);
            break;
        default:
            break;
    }
}
#endif

