/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    usb_msdisk.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file is intends for usb mass storage disk related information.
 *
 * Author:
 * -------
 *  Jensen Hu
 *
 ****************************************************************************/
#ifndef USB_MSDISK_H
#define USB_MSDISK_H

#include "kal_data_types.h"

#define LOGIC_DRIVE_COUNT             1
#define LOGIC_DRIVE_MS                0
#define LOGIC_DRIVE_CDROM             1

typedef enum 
{
	USB_STORAGE_DEV_STATUS_OK = 0,
	USB_STORAGE_DEV_STATUS_MEDIA_CHANGE,
	USB_STORAGE_DEV_STATUS_NOMEDIA,
	USB_STORAGE_DEV_STATUS_WP,
	USB_STORAGE_DEV_STATUS_MAX
} USB_STORAGE_DEV_STATUS;


typedef enum
{
	USB_STORAGE_DEV_NOR,
	USB_STORAGE_DEV_NAND,
	USB_STORAGE_DEV_CARD,
	USB_STORAGE_DEV_CDROM,
	USB_STORAGE_DEV_NONE
}USB_STORAGE_DEV_TYPE;

//FS_GetDevType Return Value
//FS_GetDevStatus Paramter, Cannot overlap with 'A'~'Z' 0x41~0x5f
typedef enum
{
    FS_DEVICE_TYPE_UNKNOWN  = 0,
    FS_DEVICE_TYPE_NOR      = 1,
    FS_DEVICE_TYPE_NAND,
    FS_DEVICE_TYPE_CARD,
    FS_DEVICE_TYPE_EXTERNAL,
    FS_DEVICE_TYPE_SIMPLUS,
    FS_DEVICE_TYPE_EMMC,
    FS_DEVICE_TYPE_MAX_VALUE
} FS_DEVICE_TYPE_ENUM;


typedef struct
{
	bool (* usbms_read)(void *data, uint32_t LBA, uint16_t sec_len);
	bool (* usbms_write)(void *data, uint32_t LBA, uint16_t sec_len);
	bool (* usbms_format)(void);
	USB_STORAGE_DEV_STATUS (* usbms_checkmedia_exist)(void);
	bool (* usbms_prevmedia_removal)(bool enable);
	bool (* usbms_read_capacity)(uint32_t *max_lba, uint32_t *sec_len);
//	bool (* usbms_read_formatcapacity)(uint32_t *no_of_blks, uint32_t *blk_len);
	USB_STORAGE_DEV_TYPE	(* usbms_dev_type)(void);
}USB_DiskDriver_STRUCT;


#if ( (defined(__MSDC_MS__)) || (defined(__MSDC_SD_MMC__)) || (defined(__MSDC_MSPRO__)) || (defined(__MSDC2_SD_MMC__))  )
extern USB_DiskDriver_STRUCT USB_MSDC_drv;
#endif

//uint8_t usbms_register_diskdriver(USB_DiskDriver_STRUCT *disk_api);
extern uint8_t USB_Ms_Register_DiskDriver(USB_DiskDriver_STRUCT *disk_api);
extern uint8_t USB_Ms_Set_Current_Driver(uint32_t drv);
extern uint32_t USB_Ms_Get_Current_Driver(void);

#endif /* USB_MSDISK_H */                    

