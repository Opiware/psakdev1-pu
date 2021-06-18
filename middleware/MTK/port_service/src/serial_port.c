/* Copyright Statement:
 *
 */

#ifdef MTK_PORT_SERVICE_ENABLE

#include "hal_nvic_internal.h"
#include "serial_port.h"
#include "serial_port_internal.h"

static uint8_t g_serial_port_open_count = 0;
/* record status of every serial port */
static bool g_serial_port_device_is_busy[SERIAL_PORT_DEV_MAX] = {false};

serial_port_operation_t g_serial_port_handlers[SERIAL_PORT_TYPE_MAX] = {
    {
        serial_port_uart_init,
        serial_port_uart_control,
        serial_port_uart_deinit,
        serial_port_uart_reset_para,
    },
    {
        serial_port_usb_init,
        serial_port_usb_control,
        serial_port_usb_deinit,
        NULL,
    },
};

serial_port_type_t serial_port_get_device_type(serial_port_dev_t device)
{
    serial_port_type_t device_type;

    if (device <= SERIAL_PORT_DEV_UART_TYPE_END) {
        device_type = SERIAL_PORT_TYPE_UART;
    } else if ((device >= SERIAL_PORT_DEV_USB_TYPE_BEGIN) && (device <= SERIAL_PORT_DEV_USB_TYPE_END)) {
        device_type = SERIAL_PORT_TYPE_USB;
    } else {
        device_type = SERIAL_PORT_TYPE_UART;
    }

    return device_type;
}

/*
 * bit0~bit7 - serial_port_dev_t
 * bit8~bit15 - distinguish different open event
 * bit16~bit23 - tag to distinguish whether it's valid
 * bit24~bit31 - DCL_UART_MAGIC_NUM */
static serial_port_handle_t port_return_handle(bool is_valid, serial_port_dev_t device)
{
    serial_port_handle_t handle;

    if (is_valid == true) {
        g_serial_port_open_count++;
        handle = (SERIAL_PORT_MAGIC_NUM << SERIAL_PORT_MAGIC_NUM_SHIFT) |
                 (SERIAL_PORT_STATUS_VALID << SERIAL_PORT_STATUS_SHIFT) |
                 (((uint32_t)g_serial_port_open_count) << SERIAL_PORT_OPEN_COUNT_SHIFT) |
                 device;
    } else {
        handle = (SERIAL_PORT_MAGIC_NUM << SERIAL_PORT_MAGIC_NUM_SHIFT) |
                 (SERIAL_PORT_STATUS_INVALID << SERIAL_PORT_STATUS_SHIFT) |
                 (((uint32_t)g_serial_port_open_count) << SERIAL_PORT_OPEN_COUNT_SHIFT) |
                 device;
    }

    return handle;
}

static bool handle_is_valid(serial_port_handle_t handle)
{
    if ((((handle >> SERIAL_PORT_MAGIC_NUM_SHIFT) & SERIAL_PORT_MAGIC_NUM_MASK) != SERIAL_PORT_MAGIC_NUM) ||
            (((handle >> SERIAL_PORT_STATUS_SHIFT) & SERIAL_PORT_STATUS_MARK) != SERIAL_PORT_STATUS_VALID)) {
        return false;
    }

    if ((handle & SERIAL_PORT_DEV_MASK) >= SERIAL_PORT_DEV_MAX) {
        return false;
    }

    return true;
}

serial_port_status_t serial_port_open(serial_port_dev_t device,
                                      serial_port_open_para_t *para,
                                      serial_port_handle_t *handle)
{
    uint32_t irq_status;
    serial_port_type_t dev_type;
    serial_port_dev_setting_t serial_port_dev_setting;
    serial_port_status_t status;

    /* parameters check */
    if (device >= SERIAL_PORT_DEV_MAX) {
        return SERIAL_PORT_STATUS_INVALID_DEVICE;
    }
    if ((para->callback == NULL) || (handle == NULL)) {
        return SERIAL_PORT_STATUS_INVALID_PARAMETER;
    }

    /* check and set busy status */
    irq_status = save_and_set_interrupt_mask();
    if (g_serial_port_device_is_busy[device] == true) {
        restore_interrupt_mask(irq_status);
        return SERIAL_PORT_STATUS_BUSY;
    }
    g_serial_port_device_is_busy[device] = true;
    restore_interrupt_mask(irq_status);

    /* check and fetch parameters needed by porting layer */
    dev_type = serial_port_get_device_type(device);
    serial_port_config_read_dev_setting(device, &serial_port_dev_setting);
    if (g_serial_port_handlers[dev_type].init == NULL) {
        status = SERIAL_PORT_STATUS_UNSUPPORTED;
        goto error;
    }
    status = g_serial_port_handlers[dev_type].init(device, para, &serial_port_dev_setting);
    if ((status != SERIAL_PORT_STATUS_OK) && (status != SERIAL_PORT_STATUS_DEV_NOT_READY)) {
        goto error;
    }

    *handle = port_return_handle(true, device);
    return status;

error:
    irq_status = save_and_set_interrupt_mask();
    *handle = port_return_handle(false, SERIAL_PORT_DEV_UNDEFINED);
    g_serial_port_device_is_busy[device] = false;
    restore_interrupt_mask(irq_status);
    return status;
}

serial_port_status_t serial_port_control(serial_port_handle_t handle,
        serial_port_ctrl_cmd_t command,
        serial_port_ctrl_para_t *para)
{
    uint32_t irq_status;
    serial_port_dev_t device;
    serial_port_type_t dev_type;
    serial_port_status_t status;

    /* parameters check */
    if (handle_is_valid(handle) == false) {
        return SERIAL_PORT_STATUS_INVALID_PARAMETER;
    }
    if (command >= SERIAL_PORT_CMD_MAX) {
        return SERIAL_PORT_STATUS_INVALID_PARAMETER;
    }

    /* get device and check whether it's busy */
    device = (serial_port_dev_t)(handle & SERIAL_PORT_DEV_MASK);
    irq_status = save_and_set_interrupt_mask();
    if (g_serial_port_device_is_busy[device] == false) {
        restore_interrupt_mask(irq_status);
        return SERIAL_PORT_STATUS_UNINITIALIZED;
    }
    restore_interrupt_mask(irq_status);

    /* check and call porting layer control method */
    dev_type = serial_port_get_device_type(device);
    if (g_serial_port_handlers[dev_type].control == NULL) {
        return SERIAL_PORT_STATUS_UNSUPPORTED;
    }
    status = g_serial_port_handlers[dev_type].control(device, command, para);

    return status;
}

serial_port_status_t serial_port_close(serial_port_handle_t handle)
{
    uint32_t irq_status;
    serial_port_dev_t device;
    serial_port_type_t dev_type;
    serial_port_status_t status;

    /* parameters check */
    if (handle_is_valid(handle) == false) {
        return SERIAL_PORT_STATUS_INVALID_PARAMETER;
    }

    /* get device and check whether it's busy */
    device = (serial_port_dev_t)(handle & SERIAL_PORT_DEV_MASK);
    irq_status = save_and_set_interrupt_mask();
    if (g_serial_port_device_is_busy[device] == false) {
        restore_interrupt_mask(irq_status);
        return SERIAL_PORT_STATUS_FAIL;
    }
    restore_interrupt_mask(irq_status);

    /* check and call porting layer control method */
    dev_type = serial_port_get_device_type(device);
    if (g_serial_port_handlers[dev_type].deinit == NULL) {
        return SERIAL_PORT_STATUS_UNSUPPORTED;
    }
    status = g_serial_port_handlers[dev_type].deinit(device);
    if (status != SERIAL_PORT_STATUS_OK) {
        return status;
    }

    /* update status of the device */
    irq_status = save_and_set_interrupt_mask();
    g_serial_port_device_is_busy[device] = false;
    restore_interrupt_mask(irq_status);

    return status;
}
#endif

