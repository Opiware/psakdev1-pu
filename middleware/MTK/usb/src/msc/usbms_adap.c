/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    usbms_adap.c
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *  This file implements usb adaption layer for mass storage
 *
 * Author:
 * -------
 *  Jensen Hu
 *
 *****************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "hal_usb.h"

#include "usb_comm.h"
#include "usbms_drv.h"
#include "usbms_state.h"
#include "usb_msdisk.h"
#include "hal_log.h"

static uint8_t USBMS_MAX_DISK[LOGIC_DRIVE_COUNT] = {0};
static USB_DiskDriver_STRUCT  *USBMS_DISKDRV_API[LOGIC_DRIVE_COUNT][MAX_DISK_DRVER];
static Read_Capacity_Info  USBMS_DISKDRV_LBA_INFO[MAX_DISK_DRVER];
static uint32_t CURRENT_DRV = LOGIC_DRIVE_MS;


/***********************************************
	adaption functions
************************************************/

static void USB_Ms_Check_CURRENT_DRV(uint8_t LUN)
{
    if (USBMS_DISKDRV_API[CURRENT_DRV][LUN] == NULL) {
        LOG_E(hal, "ASSERT\n");
    }
}

uint8_t USB_Ms_Get_Max_LUN(void)
{
    //disk number 0 means no disk register for mass storage function
    if (USBMS_MAX_DISK[CURRENT_DRV] == 0) {
        LOG_E(hal, "ASSERT, (uint32_t)USBMS_MAX_DISK[CURRENT_DRV] \n");
    }
    return (USBMS_MAX_DISK[CURRENT_DRV] - 1);
}

uint8_t USB_Ms_Register_DiskDriver(USB_DiskDriver_STRUCT *disk_api)
{
    USBMS_DISKDRV_API[CURRENT_DRV][USBMS_MAX_DISK[CURRENT_DRV]] = disk_api;
    USBMS_MAX_DISK[CURRENT_DRV]++;

    if (USBMS_MAX_DISK[CURRENT_DRV] >= MAX_DISK_DRVER) {
        LOG_E(hal, "ASSERT\n");
    }

    LOG_I(hal, "USB_Ms_Register_DiskDriver, USBMS_MAX_DISK[CURRENT_DRV]-1 = %d\n", USBMS_MAX_DISK[CURRENT_DRV] - 1);
    return (USBMS_MAX_DISK[CURRENT_DRV] - 1);
}
void USB_Ms_DeRegister_DiskDriver(uint8_t disk_index)
{
    uint8_t index;

    /* disk index can not exceed max LUN, and if deregister the last LUN, zero LUN is not allowed*/
    if ((disk_index > USBMS_MAX_DISK[CURRENT_DRV]) /*|| (USBMS_MAX_DISK[CURRENT_DRV] == 1)*/) {
        LOG_E(hal, "ASSERT, disk_index:%d\n", disk_index);
    }

    if (disk_index < (USBMS_MAX_DISK[CURRENT_DRV] - 1)) {
        for (index = disk_index; index < (USBMS_MAX_DISK[CURRENT_DRV] - 1); index++) {
            USBMS_DISKDRV_API[CURRENT_DRV][index] = USBMS_DISKDRV_API[CURRENT_DRV][index + 1];
        }
    }
    USBMS_MAX_DISK[CURRENT_DRV]--;
}

void USB_Ms_Change_Register_DiskDriver(uint8_t disk_index, USB_DiskDriver_STRUCT *disk_api)
{
    /* disk index can not exceed max LUN */
    if (disk_index >= USBMS_MAX_DISK[CURRENT_DRV]) {
        LOG_E(hal, "ASSERT\n");
    }

    USBMS_DISKDRV_API[CURRENT_DRV][disk_index] = disk_api;
}


USB_STORAGE_DEV_STATUS USB_Ms_Checkmedia_Exist(uint8_t LUN)
{
    USB_Ms_Check_CURRENT_DRV(LUN);

    return USBMS_DISKDRV_API[CURRENT_DRV][LUN]->usbms_checkmedia_exist();
}


bool USB_Ms_Format(uint8_t LUN)
{
    USB_Ms_Check_CURRENT_DRV(LUN);

    return USBMS_DISKDRV_API[CURRENT_DRV][LUN]->usbms_format();
}


bool USB_Ms_Read_Capacity(uint8_t LUN, uint32_t *max_lba, uint32_t *sec_len)
{
    bool ret;

    USB_Ms_Check_CURRENT_DRV(LUN);

    ret = USBMS_DISKDRV_API[CURRENT_DRV][LUN]->usbms_read_capacity(max_lba, sec_len);
    USBMS_DISKDRV_LBA_INFO[LUN].LastBA = *max_lba;
    USBMS_DISKDRV_LBA_INFO[LUN].BlkLen = *sec_len;

    return ret;
}

bool USB_Ms_Read_Write(USB_MS_DIRECTION direct, uint8_t LUN, void *data, uint32_t LBA, uint16_t sec_len)
{
    bool ret;

    USB_Ms_Check_CURRENT_DRV(LUN);

    if ( (LBA + sec_len - 1) > USBMS_DISKDRV_LBA_INFO[LUN].LastBA) {
        return false;
    }

    if (direct == USB_MS_WRITE) {
        ret = USBMS_DISKDRV_API[CURRENT_DRV][LUN]->usbms_write(data, LBA, sec_len);
    } else {
        ret = USBMS_DISKDRV_API[CURRENT_DRV][LUN]->usbms_read(data, LBA, sec_len);
    }

    return ret;
}

bool USB_Ms_Prevmedia_Removal(uint8_t LUN, bool enable)
{
    USB_Ms_Check_CURRENT_DRV(LUN);

    return USBMS_DISKDRV_API[CURRENT_DRV][LUN]->usbms_prevmedia_removal(enable);
}


USB_STORAGE_DEV_TYPE USB_Ms_Dev_Type(uint8_t LUN)
{
    USB_Ms_Check_CURRENT_DRV(LUN);

    return USBMS_DISKDRV_API[CURRENT_DRV][LUN]->usbms_dev_type();
}

