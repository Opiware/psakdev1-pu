/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    usbacm_adap.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *  This file intends for usb adaption layer for UART API definitions
 *
 * Author:
 * -------
 *   Jensen Hu
 *   CJung Chen 
 *
 *============================================================================
 ****************************************************************************/
 
#ifndef USBACM_ADAP_H
#define USBACM_ADAP_H

typedef enum 
{
	CDC_ONLY_PUSH = 0,  	//Only push buffer  ( initial sate: prepare buffer for USB )
	CDC_ONLY_GET,   	//  Only get data   ( there might be no FLC buffer anymore )
	CDC_GET_DATA,   	//  normal state	( get data & push another buffer )
	CDC_POP_BUFF    	//  Get empty buffer  (leave RNDIS mode „³ release FLC buffer )
}USB_Requ_type;


extern void USB2UART_init(void);
extern void USB2UART_Clear_Tx_Buffer(uint8_t port);
extern void USB2UART_Clear_Rx_Buffer(uint8_t port);


extern void USB2UART_ClrRxBuffer(uint8_t port);
extern uint16_t USB2UART_GetRxAvail(uint8_t port);
extern uint16_t USB2UART_GetBufAvail(BUFFER_INFO *buf_info);
extern uint16_t USB2UART_GetBytes(uint8_t port, uint8_t *buffaddr, uint16_t length);
extern void USB2UART_ClrTxBuffer(uint8_t port);
extern uint16_t USB2UART_GetTxRoomLeft(uint8_t port);
extern uint16_t USB2UART_PutBytes(uint8_t port, uint8_t *buffaddr, uint16_t length);
extern uint8_t USB2UART_GetByte_Polling(uint8_t port);
extern void USB2UART_PutData_Polling(uint8_t port, uint8_t *Buffaddr, uint16_t Length);
extern uint16_t USB2UART_GetBuffRoomLeft(BUFFER_INFO *buf_info);
extern uint16_t USB2UART_GetTxRoomLeft(uint8_t port);

#endif /* USBACM_ADAP_H */

