/* Copyright Statement:
 *
 */

#ifndef __SERIAL_PORT_CONFIG_H__
#define __SERIAL_PORT_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MTK_PORT_SERVICE_ENABLE

/* define size of internal buffers */
#define SERIAL_PORT_RECEIVE_BUFFER_SIZE 2048
#define SERIAL_PORT_SEND_BUFFER_SIZE 2048

/* define name of port setting in NVDM */
#define PORT_SETTING_GROUP_NAME "port_service"
#define PORT_SETTING_NAME_PORT_ASSIGN "port_assign"
#define PORT_SETTING_NAME_PORT_CONFIG "port_config"

/* define max size of user name */
#define SERIAL_PORT_USER_NAME_SIZE 20

/* define default values for porting devices */
#define UART_DEFAULT_BAUDRATE HAL_UART_BAUDRATE_115200
// #define USB_DEFAULT_XXX

#endif

#ifdef __cplusplus
}
#endif

#endif

