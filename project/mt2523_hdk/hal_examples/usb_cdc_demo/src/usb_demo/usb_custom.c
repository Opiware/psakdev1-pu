/* Copyright Statement:
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "memory_attribute.h"

#include "usb_custom.h"

/************************************************************
	external variables
*************************************************************/


ATTR_RWDATA_IN_NONCACHED_RAM unsigned char USB_BUFFERR[1024]; // USB total buffer 


/************************************************************
	device descriptor parameters
*************************************************************/

static const uint16_t USB_MANUFACTURER_STRING[] = 
{
	0x031a,
	'M',
	'e',
	'd',
	'i',
	'a',
	'T',
	'e',
	'k',
	' ',
	'I',
	'n',
	'c'
};

static const uint16_t USB_PRODUCT_STRING[] = 
{
	0x0310,
	'P',
	'r',
	'o',
	'd',
	'u',
	'c',
	't'
};


static const USB_DEVICE_PARAM usb_device_param = 
{
	0x0e8d,				/* vendor id */	
	USB_MANUFACTURER_STRING,
	sizeof(USB_MANUFACTURER_STRING)/sizeof(uint16_t),
	USB_PRODUCT_STRING,
	sizeof(USB_PRODUCT_STRING)/sizeof(uint16_t)
};

/************************************************************
	CDC ACM parameters
*************************************************************/

static const uint16_t USB_ACM_COMM_INTERFACE_STRING[] = 
{
	0x031A,
	'C',
	'O',
	'M',
	'(',
	'c',   
	'o',
	'm',
	'm',
	'_',
	'i',
	'f',
	')'
};

static const uint16_t  USB_ACM_DATA_INTERFACE_STRING[] = 
{
	0x031A,
	'C',
	'O',
	'M',
	'(',
	'd',
	'a',
	't',
	'a',
	'_',
	'i',
	'f',
	')'
};



static const USB_ACM_PARAM usb_acm_param =
{
	0x0003,				/* CDC ACM Product ID */
	USB_ACM_COMM_INTERFACE_STRING,
	sizeof(USB_ACM_COMM_INTERFACE_STRING)/sizeof(uint16_t),
	USB_ACM_DATA_INTERFACE_STRING,
	sizeof(USB_ACM_DATA_INTERFACE_STRING)/sizeof(uint16_t),
};






/************************************************************
	customization functinos
*************************************************************/

/* get general USB device parameter function*/
const USB_DEVICE_PARAM *USB_GetDeviceParam(void)
{
	return (&usb_device_param);
}

/* get CDC ACM USB device parameter function*/
const USB_ACM_PARAM *USB_GetAcmParam(void)
{
	return (&usb_acm_param);
}



/* get USB custom parameter function*/
static const USB_CUSTOM_FUNC USB_CustomFunc = 
{
	USB_GetDeviceParam,
	USB_GetAcmParam
};

const USB_CUSTOM_FUNC* USB_GetCustomFunc(void)
{
	return(&USB_CustomFunc);
}


