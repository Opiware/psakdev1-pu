/* Copyright Statement:
 *
 */

#ifndef USB_RESOURCE_H
#define USB_RESOURCE_H

#include "usb.h"
#include "kal_data_types.h"

/***********************************************
	implement enum and structure 
************************************************/

/* interface create infomration structrue, use this information to create interface */
typedef struct 
{
	char		*if_name_ptr;
	usb_create_if_func_ptr	if_create_func;
	usb_void_func		if_init_func;
	usb_void_func		if_enable_func;
	usb_speed_if_func_ptr	if_speed_func;
	usb_void_func		if_resume_func;
} Usb_IfCreate_Info;


typedef struct
{
	uint8_t 	device_code; 	/*device class*/
	uint8_t 	subclass_code;	
	uint8_t 	protocol_code;
	uint16_t 	product_code;
	bool	b_registerd;
} Usb_Device_Code;


/***********************************************
	function and global variable
************************************************/

extern void USB_Software_Create(void);
#ifdef __MBIM_SUPPORT__
extern void USB_Software_Speed_Init(bool b_other_speed, uint8_t cfg_num);
extern void USB_Configuration_Setup(uint8_t cfg_num);
#else
extern void USB_Software_Speed_Init(bool b_other_speed);
#endif
extern void USB_Software_Init(void);
extern void USB_Software_Resume(void);
extern void USB_Software_Enable(void);
extern void USB_DeRegister_CreateFunc(void);
extern void USB_Register_CreateFunc(char* if_name, usb_create_if_func_ptr if_create_func, usb_void_func if_init_func,
				usb_void_func if_enable_func, usb_speed_if_func_ptr if_speed_func, usb_void_func if_resume_func);
extern void USB_Register_Device_Code(uint8_t device_code, uint8_t subclass_code, 
									uint8_t protocol_code, uint16_t product_code);
extern Usb_Interface_Info* USB_Get_Interface_Number(uint8_t *p_num);
extern Usb_Ep_Info* USB_Get_Intr_Ep(uint8_t *p_num);
extern Usb_Ep_Info* USB_Get_Bulk_Tx_Ep(uint8_t *p_num);
extern Usb_Ep_Info* USB_Get_Bulk_Rx_Ep(uint8_t *p_num);

extern uint8_t USB_Get_String_Number(void *usb_string);
extern Usb_IAD_Dscr* USB_Get_IAD_Number(void);

#endif /* USB_RESOURCE_H */

