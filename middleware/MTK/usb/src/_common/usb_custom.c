/* Copyright Statement:
 *
 */

#ifdef MTK_USB_DEMO_ENABLED

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "memory_attribute.h"


#include "usb_custom.h"


/************************************************************
	external variables
*************************************************************/

/************************************************************
	device descriptor parameters
*************************************************************/

static const uint16_t USB_MANUFACTURER_STRING[] = {
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

static const uint16_t USB_PRODUCT_STRING[] = {
    0x0310,
    'P',
    'r',
    'o',
    'd',
    'u',
    'c',
    't'
};


static const USB_DEVICE_PARAM usb_device_param = {
    0x0e8d,				/* vendor id */
    USB_MANUFACTURER_STRING,
    sizeof(USB_MANUFACTURER_STRING) / sizeof(uint16_t),
    USB_PRODUCT_STRING,
    sizeof(USB_PRODUCT_STRING) / sizeof(uint16_t)
};

/************************************************************
	CDC ACM parameters
*************************************************************/

static const uint16_t USB_ACM_COMM_INTERFACE_STRING[] = {
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

static const uint16_t  USB_ACM_DATA_INTERFACE_STRING[] = {
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
static const USB_ACM_PARAM usb_acm_param = {
    0x0003,				/* CDC ACM Product ID */
    USB_ACM_COMM_INTERFACE_STRING,
    sizeof(USB_ACM_COMM_INTERFACE_STRING) / sizeof(uint16_t),
    USB_ACM_DATA_INTERFACE_STRING,
    sizeof(USB_ACM_DATA_INTERFACE_STRING) / sizeof(uint16_t),
};

/*USB mass storage customize*/

/* Inquire data explanation
   The length byte(Byte 4) should be always not changed, the mass storage spec define it
   Byte 8 to 15 is Vendor Information
   Byte 16 to 31 is Product Identification
   Byte 32 to 35 is Product Revision Level */

ATTR_RWDATA_IN_NONCACHED_RAM uint8_t INQUIRE_DATA[] = {
    0x00,
    0x80,
    0x00,
    0x01,
    0x1f, /*length*/
    0x00,
    0x00,
    0x00,
    'M',  /*Vendor Identification*/
    'E',
    'D',
    'I',
    'A',
    'T',
    'E',
    'K',
    ' ', /*Product Identification*/
    'F',
    'L',
    'A',
    'S',
    'H',
    ' ',
    'D',
    'I',
    'S',
    'K',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ', /*Product Revision Level*/
    ' ',
    ' ',
    ' '
};

static const uint16_t  USB_MS_INTERFACE_STRING[] = {
    0x031c,
    'M',
    'a',
    's',
    's',
    ' ',
    'S',
    't',
    'o',
    'r',
    'a',
    'g',
    'e',
    ' '
};


static const USB_MS_PARAM usb_ms_param = {
    0x0002,			/* Mass storage Product ID */
    INQUIRE_DATA,
    sizeof(INQUIRE_DATA) / sizeof(uint8_t),
    USB_MS_INTERFACE_STRING,
    sizeof(USB_MS_INTERFACE_STRING) / sizeof(uint16_t)
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

/* get mass storage USB device parameter function*/
const USB_MS_PARAM *USB_GetMsParam(void)
{
    return (&usb_ms_param);
}


/* get USB custom parameter function*/
static const USB_CUSTOM_FUNC USB_CustomFunc = {
    USB_GetDeviceParam,
    USB_GetAcmParam,
    USB_GetMsParam
};

const USB_CUSTOM_FUNC *USB_GetCustomFunc(void)
{
    return (&USB_CustomFunc);
}



#endif //MTK_USB_DEMO_ENABLED

