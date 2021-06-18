/* Copyright Statement:
 *
 */

#include "hal.h"
#include "hal_msdc.h"
#include "usbms_msdc.h"
#include "msdc_custom_config.h"


#define USBMS_MSDC_PORT ((hal_sd_port_t)MASS_STORAGE_USE_MSDC_PORT_NUMBER)
#define USBMS_MSDC_BUSWIDTH ((hal_sd_bus_width_t)MASS_STORAGE_MSDC_BUS_WIDTH)
#define USBMS_MSDC_BUS_CLOCK MASS_STORAGE_MSDC_BUS_CLOCK /*KHz*/

hal_sd_config_t sd_config = {USBMS_MSDC_BUSWIDTH, USBMS_MSDC_BUS_CLOCK};


static bool usbms_read_msdc(void *data, uint32_t LBA, uint16_t sec_len)
{
    hal_sd_status_t status;
    uint32_t retry = 0;

    while (retry < 3) {
        status = hal_sd_read_blocks(USBMS_MSDC_PORT, data, LBA, sec_len);
        if (HAL_SD_STATUS_OK == status) {
            return true;
        } else {
            status = hal_sd_init(USBMS_MSDC_PORT, &sd_config);
            if (HAL_SD_STATUS_OK == status) {
                retry++;
            } else {
                return false;
            }
        }
    }

    return false;
}

static bool usbms_write_msdc(void *data, uint32_t LBA, uint16_t sec_len)
{
    hal_sd_status_t status;
    uint32_t retry = 0;

    while (retry < 3) {
        status = hal_sd_write_blocks(USBMS_MSDC_PORT, data, LBA, sec_len);
        if (HAL_SD_STATUS_OK == status) {
            return true;
        } else {
            status = hal_sd_init(USBMS_MSDC_PORT, &sd_config);
            if (HAL_SD_STATUS_OK == status) {
                retry++;
            } else {
                return false;
            }
        }
    }

    return false;
}


static bool usbms_checkmedia_exist_msdc(void)
{
    return (true); //didn't support hot plug
}


static bool usbms_format_msdc(void)
{
    hal_sd_status_t status;

    status = hal_sd_init(USBMS_MSDC_PORT, &sd_config);

    return (HAL_SD_STATUS_OK == status ? true : false);
}


static bool usbms_prevmedia_removal_msdc(bool enable)
{
    return true;
}


static bool usbms_read_capacity_msdc(uint32_t *max_lba, uint32_t *sec_len)
{
    hal_sd_status_t status;
    uint64_t card_capacity;

    status = hal_sd_get_capacity(USBMS_MSDC_PORT, &card_capacity);

    if (HAL_SD_STATUS_OK != status) {
        status = hal_sd_init(USBMS_MSDC_PORT, &sd_config);
        if (HAL_SD_STATUS_OK == status) {
            status = hal_sd_get_capacity(USBMS_MSDC_PORT, &card_capacity);
            if (HAL_SD_STATUS_OK != status) {
                return false;
            }
        } else {
            return false;
        }
    }

    *max_lba = (card_capacity / 512) - 1;
    *sec_len = 512;


    return true;
}


static usbms_dev_type_t usbms_read_dev_type_msdc(void)
{
    return (USB_STORAGE_DEV_CARD);
}


usbms_msdc_driver_t usbms_msdc_driver = {
    usbms_read_msdc,
    usbms_write_msdc,
    usbms_format_msdc,
    usbms_checkmedia_exist_msdc,
    usbms_prevmedia_removal_msdc,
    usbms_read_capacity_msdc,
    usbms_read_dev_type_msdc,
};








