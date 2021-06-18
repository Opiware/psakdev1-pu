/* Copyright Statement:
 *
 */

#ifndef __SERIAL_NAND_FLASH_H__
#define __SERIAL_NAND_FLASH_H__

#ifdef MTK_FATFS_ON_SERIAL_NAND
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hal_spi_master.h"

typedef struct {
    uint8_t maf_id;
    uint8_t dev_id;
    uint32_t page_size;
    uint32_t spare_size;
    uint32_t block_size;
    uint64_t chip_size;
} serial_nand_information_t;

typedef enum {
    SERIAL_NAND_STATUS_ERROR,
    SERIAL_NAND_STATUS_INVALID_PARAMETER,
    SERIAL_NAND_STATUS_DEVBUSY,
    SERIAL_NAND_STATUS_UNINITIALIZED,
    SERIAL_NAND_STATUS_OK = 0,
} serial_nand_status_t;


serial_nand_status_t serial_nand_reset_device(void);

serial_nand_status_t serial_nand_get_information(serial_nand_information_t *information);

serial_nand_status_t serial_nand_init(hal_spi_master_port_t spim_port, uint32_t frequency);

serial_nand_status_t serial_nand_deinit(void);

serial_nand_status_t serial_nand_read_page(uint32_t address, uint8_t *data, uint32_t length,
        uint32_t spare_offset, uint8_t *spare_data, uint32_t spare_length);

serial_nand_status_t serial_nand_write_page(uint32_t address, uint8_t *data, uint32_t length,
        uint32_t spare_offset, uint8_t *spare_data, uint32_t spare_length);

serial_nand_status_t serial_nand_erase(uint32_t address, uint32_t length);

#ifdef __cplusplus
}
#endif
#endif
#endif

