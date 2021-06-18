/* Copyright Statement:
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"

/* Exported types ------------------------------------------------------------*/
enum PowerMode {
    PowerMode_Normal,
    PowerMode_Standby,
    PowerMode_Off
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void set_power_mode(PowerMode mode, uint32_t data);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT MTK *****END OF FILE****/
