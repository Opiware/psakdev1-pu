/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    usb_custom_def.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file declares usb customization definitions
 *
 * Author:
 * -------
 *  Choco Chou
 *
 *============================================================================*/

/* USB VID */
#define MTK_USB_VID						(0x0e8d)

/*
 * When the USB is detected, the LED lights up
 * */

//#define USB_DETECT_LED

#ifdef USB_DETECT_LED
#define VIBR_VOL PMIC_LDO_1P8V
#define LED_GPIO HAL_GPIO_24
#endif

/*********************************************/
/*        Device Common                      */
/*********************************************/
#define USB_DESCRIPTOR_SIZE 		512

/*********************************************/
/*             CDC ACM Buffer Size           */
/*********************************************/

#define	USB_TX_RING_BUFFER_1_SIZE			(2048)
#define	USB_TX_RING_BUFFER_2_SIZE			(2048)
#define	USB_TX_RING_BUFFER_3_SIZE			(2048)

#define	USB_RX_RING_BUFFER_1_SIZE			(2048)
#define	USB_RX_RING_BUFFER_2_SIZE			(2048)
#define	USB_RX_RING_BUFFER_3_SIZE			(2048)

#ifdef  __USB_HIGH_SPEED_COM_PORT_ENABLE__
// high speed interface RX buffer
#define USB_ACM_RX_BUFFER_NUM  					8   
#define USB_ACM_RX_BUFFER_SIZE 					3072
#else
#define USB_ACM_RX_BUFFER_NUM  					0   
#define USB_ACM_RX_BUFFER_SIZE 					0
#endif

/*********************************************/
/*        Mass Storage Buffer Size           */
/*********************************************/
#if defined(__LOW_COST_SUPPORT_ULC__)
#define USBMS_MAX_BUFFERSIZE     		(4*1024)
#elif (defined(__LOW_COST_SUPPORT_COMMON__)&&(!defined(__USB_HS_ENABLE__)))
#define USBMS_MAX_BUFFERSIZE     		(8*1024)
#else
#define USBMS_MAX_BUFFERSIZE     		(32*1024)
#endif

