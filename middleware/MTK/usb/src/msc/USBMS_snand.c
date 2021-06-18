/* Copyright Statement:
 *
 */

#include "hal.h"
#include "usbms_msdc.h"
#include "spi_nand_fdm.h"

#ifdef MTK_FATFS_ON_SERIAL_NAND
static bool usbms_read_nand(void *data, uint32_t LBA, uint16_t sec_len)
{
    int32_t status;
    ms_mutex_lock();
    status = spi_nand_fdm_ReadSectors(LBA, sec_len, data);
    ms_mutex_unlock();
    return (0 == status ? true : false);
}

static bool usbms_write_nand(void *data, uint32_t LBA, uint16_t sec_len)
{
    int32_t status;
    ms_mutex_lock();
    status = spi_nand_fdm_WriteSectors(LBA, sec_len, data);
    ms_mutex_unlock();
    return (0 == status ? true : false);
}


static bool usbms_checkmedia_exist_nand(void)
{
    return (true); 
}


static bool usbms_format_nand(void)
{
    int32_t status;
    ms_mutex_lock();
    status = spi_nand_fdm_LowLevelFormat();
    ms_mutex_unlock();
    return (0 == status ? true : false);
}


static bool usbms_prevmedia_removal_nand(bool enable)
{
    return true;
}


static bool usbms_read_capacity_nand(uint32_t *max_lba, uint32_t *sec_len)
{
    uint32_t status;
    DEVICE_INFO_T device_info;

    ms_mutex_lock();
    status = spi_nand_GetDiskGeometry(&device_info);
    *max_lba = device_info.sectors - 1;
    *sec_len = device_info.sector_size;
    ms_mutex_unlock();

    return true;
}


static usbms_dev_type_t usbms_read_dev_type_nand(void)
{
    return (USB_STORAGE_DEV_NAND);
}


usbms_msdc_driver_t usbms_spinand_driver = {
    usbms_read_nand,
    usbms_write_nand,
    usbms_format_nand,
    usbms_checkmedia_exist_nand,
    usbms_prevmedia_removal_nand,
    usbms_read_capacity_nand,
    usbms_read_dev_type_nand,
};
#endif


