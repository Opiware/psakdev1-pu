/* Copyright Statement:
 *
 */

#ifndef __SERIAL_PORT_INTERNAL_H__
#define __SERIAL_PORT_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MTK_PORT_SERVICE_ENABLE

#include <assert.h>

#define SERIAL_PORT_MAGIC_NUM 'M'
#define SERIAL_PORT_MAGIC_NUM_MASK 0xff
#define SERIAL_PORT_MAGIC_NUM_SHIFT 24
#define SERIAL_PORT_STATUS_INVALID 'I'
#define SERIAL_PORT_STATUS_VALID 'V'
#define SERIAL_PORT_STATUS_MARK 0xff
#define SERIAL_PORT_STATUS_SHIFT 16
#define SERIAL_PORT_OPEN_COUNT_MASK 0xff
#define SERIAL_PORT_OPEN_COUNT_SHIFT 8
#define SERIAL_PORT_DEV_MASK 0xff

typedef struct {
    serial_port_dev_setting_t setting[SERIAL_PORT_DEV_MAX];
} serial_port_setting_t;

typedef struct {
    serial_port_status_t (*init)(serial_port_dev_t device, serial_port_open_para_t *para, void *priv_data);
    serial_port_status_t (*control)(serial_port_dev_t device, serial_port_ctrl_cmd_t cmd, serial_port_ctrl_para_t *para);
    serial_port_status_t (*deinit)(serial_port_dev_t device);
    void (*reset_para)(serial_port_setting_t *setting);
} serial_port_operation_t;

serial_port_status_t serial_port_uart_init(serial_port_dev_t device, serial_port_open_para_t *para, void *priv_data);
serial_port_status_t serial_port_uart_control(serial_port_dev_t device, serial_port_ctrl_cmd_t cmd, serial_port_ctrl_para_t *para);
serial_port_status_t serial_port_uart_deinit(serial_port_dev_t device);
void serial_port_uart_reset_para(serial_port_setting_t *setting);
serial_port_status_t serial_port_usb_init(serial_port_dev_t device, serial_port_open_para_t *para, void *priv_data);
serial_port_status_t serial_port_usb_control(serial_port_dev_t device, serial_port_ctrl_cmd_t cmd, serial_port_ctrl_para_t *para);
serial_port_status_t serial_port_usb_deinit(serial_port_dev_t device);

#define SERIAL_PORT_ASSERT() assert(0)

#endif

#ifdef __cplusplus
}
#endif

#endif

