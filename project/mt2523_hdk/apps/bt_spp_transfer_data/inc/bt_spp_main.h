/* Copyright Statement:
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BT_SPP_MAIN_H__
#define __BT_SPP_MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "syslog.h"
#include "bt_type.h"
#include "task_def.h"

/* Exported types ------------------------------------------------------------*/
typedef struct {
    bt_msg_type_t msg;
    bt_status_t status;  
    uint8_t param[50];
} spp_message_t;


#define SPP_CLIENT_STRING "Hello, SPP Server!"
#define SPP_SERVER_STRING "Hello, SPP Client!"

/* Exported functions ------------------------------------------------------- */
extern void bt_spp_main(void);
#endif /* __BT_SPP_MAIN_H__ */

