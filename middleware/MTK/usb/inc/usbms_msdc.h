/* Copyright Statement:
 *
 */

#ifndef __USBMS_MSDC_H__
#define __USBMS_MSDC_H__

typedef enum
{
	USB_STORAGE_DEV_NOR,
	USB_STORAGE_DEV_NAND,
	USB_STORAGE_DEV_CARD,
	USB_STORAGE_DEV_CDROM,
	USB_STORAGE_DEV_NONE
} usbms_dev_type_t;


typedef struct
{
	bool (* usbms_read)(void *data, uint32_t LBA, uint16_t sec_len);
	bool (* usbms_write)(void *data, uint32_t LBA, uint16_t sec_len);
	bool (* usbms_format)(void);
	bool (* usbms_checkmedia_exist)(void);
	bool (* usbms_prevmedia_removal)(bool enable);
	bool (* usbms_read_capacity)(uint32_t *max_lba, uint32_t *sec_len);
	usbms_dev_type_t (* usbms_dev_type)(void);
} usbms_msdc_driver_t;


#endif

