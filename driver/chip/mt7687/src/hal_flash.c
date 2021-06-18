/* Copyright Statement:
 *
 */

#include "hal_flash.h"
#ifdef HAL_FLASH_MODULE_ENABLED
#include <string.h>
#include "flash_sfc.h"
#include "hal_log.h"
#include "mt7687_cm4_hw_memmap.h"

hal_flash_status_t hal_flash_init(void)
{
    int32_t ret_value = -1;
    ret_value = flash_sfc_config(FLASH_MODE_SPI);
    return ret_value >= 0 ? HAL_FLASH_STATUS_OK : HAL_FLASH_STATUS_ERROR;
}

hal_flash_status_t hal_flash_deinit(void)
{
    return HAL_FLASH_STATUS_OK;
}

hal_flash_status_t hal_flash_erase(uint32_t start_address, hal_flash_block_t block)
{
    int32_t ret_value = -1;
    ret_value = flash_sfc_erase(start_address, block);
    return ret_value >= 0 ? HAL_FLASH_STATUS_OK : HAL_FLASH_STATUS_ERROR;
}


hal_flash_status_t hal_flash_read(uint32_t start_address, uint8_t *buffer, uint32_t length)
{
    hal_flash_direct_read((void *)(start_address + CM4_EXEC_IN_PLACE_BASE), buffer, length);
    return HAL_FLASH_STATUS_OK;
}

hal_flash_status_t hal_flash_write(uint32_t address, const uint8_t *data, uint32_t length)
{
    int32_t ret_value = flash_sfc_write(address, length, data);
    return ret_value >= 0 ? HAL_FLASH_STATUS_OK : HAL_FLASH_STATUS_ERROR;
}
#endif

