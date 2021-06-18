/* Copyright Statement:
 *
 */


/*****************************************************************************
 *
 * Filename:
 * ---------
 *    usbms_state.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *    This file intends for usb mass storage state machine definitions
 *
 * Author:
 * -------
 *   Jensen Hu
 *   CJung Chen  
 *
 *****************************************************************************/
 
#ifndef USBMS_STATE_H
#define USBMS_STATE_H

#include "kal_data_types.h"

#define USBMS_DIR_OUT		0x00
#define USBMS_DIR_IN		0x80

typedef enum 
{
	USB_MS_ERROR_OK = 0,
	USB_MS_ERROR_RX_GETNEXTCMD,
	USB_MS_ERROR_RX_ACK,
	USB_MS_ERROR_RX_TX,
	USB_MS_ERROR_TX_IDLE,
	USB_MS_ERROR_TX_RX
} USB_MS_ERROR;

typedef enum 
{
	USB_MS_READ = 0,
	USB_MS_WRITE
} USB_MS_DIRECTION;

typedef enum
{
	MSG_ID_USB_MSDRV_RESET_IND = 0, 			/* mass storage messages */
	MSG_ID_USB_MSDRV_REC_DONE_CONF,
	MSG_ID_USB_MSDRV_TRX_DONE_CONF,
	MSG_ID_USB_MSDRV_CLEAR_STALL_REQ,
	MSG_ID_USB_MSDRV_REMOUNT_REQ
} USB_Ms_State;

extern void USB_Ms_State_Main(USB_Ms_State event, usb_ms_rec_done_conf_struct *local_para_ptr);

#if 0//def __P_PROPRIETARY_COPYRIGHT__
extern void USB_Ms_Sort_Protect_Items(uint32_t* data_item, uint32_t* second_data_item);
#endif

#endif // USBMS_STATE_H

