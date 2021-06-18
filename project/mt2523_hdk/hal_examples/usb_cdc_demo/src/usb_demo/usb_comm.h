/* Copyright Statement:
 *
 */

#ifndef USB_COMM_H
#define USB_COMM_H


#include "kal_general_types.h"

/* Define usb device type */
typedef enum 
{
	USB_UNKOWN=0,
	USB_CDC_ACM,
	USB_MASS_STORAGE,
	USB_VIDEO,
	USB_COMPOSITE_VIDEO_COM,	
	USB_STOP_MS,
	USB_CDC_ACM_LOGGING,
	USB_IMAGE,
	USB_IMAGE_MTP,
	USB_STOP_MTP,
	USB_COMPOSITE_MULTI_COM,
	USB_RNDIS,		
	USB_COMPOSITE_RNDIS_COM,
	USB_MASS_STORAGE_CDROM_ONLY,
	USB_CANNOT_CONFIG,
	USB_DATA_CONNECTION,
	USB_DATA_CONNECTION_COM,
	USB_MAX_DEVICE_TYPE
} USB_DEVICE_TYPE;


extern bool USB_GetCableStatus(void);


#if defined(__USB_MULTIPLE_COMPORT_SUPPORT__)
	#ifdef __USB_MODEM_CARD_SUPPORT__
	#define MAX_USB_PORT_NUM						3
	#else
	#define MAX_USB_PORT_NUM						2
	#endif
#else
#define MAX_USB_PORT_NUM						1
#endif


#endif  /* USB_COMM_H */                   

