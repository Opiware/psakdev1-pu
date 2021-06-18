/* Copyright Statement:
 *
 */

#include "hal_flash.h"
#ifdef HAL_FLASH_MODULE_ENABLED

#include "stdio.h"
#include "hal_uid.h"
#include "sfc.h"


hal_uid_status_t hal_uid_read(uint8_t *buf, uint8_t len)
{
    unsigned char code;
    unsigned char uid_info[12];
    int i = 0;

    if (buf == NULL || len != MT7687_UID_LENGTH) {
        return HAL_UID_INVALID_PARAMETER;
    }

    // CALL read reader function here.
    code = 0x4b;
    sfc_read(&code, 1, uid_info, 12);

#if 0
    for (i = 0; i < 12; i++) {
        printf("uid_info[%d]=%x\n", i, uid_info[i]);
    }
#endif

    /* BYTE 1~4 DUMMY 5~12 UID */
    for (i = 0; i < MT7687_UID_LENGTH; i++) {
        buf[i] = uid_info[i + 4];
    }

    return HAL_UID_OK;
}
#endif

