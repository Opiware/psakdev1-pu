/* Copyright Statement:
 *
 */

#ifndef USB_CUSTOM_H
#define USB_CUSTOM_H

/* custom parameter for usb device*/
typedef struct
{
	const uint16_t 	desc_vendor;
	const uint16_t 	*manufacture_string;
	const uint8_t 	manufacture_size;
	const uint16_t 	*product_string;
	const uint8_t 	product_size;
}USB_DEVICE_PARAM;


/* custom parameter for acm device*/
typedef struct
{
	const uint16_t 	desc_product;
	const uint16_t 	*comm_interface_string;
	const uint8_t 	comm_interface_size;
	const uint16_t 	*data_interface_string;
	const uint8_t 	data_interface_size;
}USB_ACM_PARAM;

/* custom parameter for mass storage device*/
typedef struct
{
	const uint16_t 	desc_product;
	const uint8_t 	*inquire_data;
	const uint8_t 	inquire_size;
	const uint16_t 	*interface_string;
	const uint8_t 	interface_size;
}USB_MS_PARAM;

typedef const USB_DEVICE_PARAM* (*usb_get_device_param_func)(void);
typedef const USB_ACM_PARAM* (*usb_get_acm_param_func)(void);
typedef const USB_MS_PARAM* (*usb_get_ms_param_func)(void);


/* get parameter functions*/
typedef struct 
{
	usb_get_device_param_func	get_device_param_func;
	usb_get_acm_param_func		get_acm_param_func;
	usb_get_ms_param_func		get_ms_param_func;
} USB_CUSTOM_FUNC;

#endif

