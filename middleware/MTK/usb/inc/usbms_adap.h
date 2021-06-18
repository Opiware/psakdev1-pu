/* Copyright Statement:
 *
 */


/*****************************************************************************
 *
 * Filename:
 * ---------
 *    usbms_adap.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file intends for usb adaption layer for mass storage definitions
 *
 * Author:
 * -------
 *   Jensen Hu
 *   CJung Chen  
 *
 *****************************************************************************/
 
#ifndef USBMS_ADAP_H
#define USBMS_ADAP_H

#include "kal_data_types.h"
#include "usb_msdisk.h"
#include "usbms_state.h"

/***********************************************
	function and global variable
************************************************/

extern USB_DiskDriver_STRUCT usbms_msdc_driver;

#ifdef MTK_FATFS_ON_SERIAL_NAND
extern USB_DiskDriver_STRUCT usbms_spinand_driver;
#endif

/* translate fd type to usb dev type*/
extern uint8_t USB_Ms_Get_Max_LUN(void);

extern void USB_Ms_DeRegister_DiskDriver(uint8_t disk_index);
extern void USB_Ms_Change_Register_DiskDriver(uint8_t disk_index, USB_DiskDriver_STRUCT *disk_api);

extern USB_STORAGE_DEV_STATUS USB_Ms_Checkmedia_Exist(uint8_t LUN);
extern bool USB_Ms_Format(uint8_t LUN);
extern bool USB_Ms_Read_Capacity(uint8_t LUN, uint32_t *max_lba, uint32_t *sec_len);
extern bool USB_Ms_Read_FormatCapacity(uint8_t LUN, uint32_t *max_lba, uint32_t *sec_len);
extern bool USB_Ms_Read_Write(USB_MS_DIRECTION direct, uint8_t LUN, void *data, uint32_t LBA, uint16_t sec_len);
extern bool USB_Ms_Prevmedia_Removal(uint8_t LUN, bool enable);
extern USB_STORAGE_DEV_TYPE USB_Ms_Dev_Type(uint8_t LUN);

#endif //USBMS_ADAP_H

