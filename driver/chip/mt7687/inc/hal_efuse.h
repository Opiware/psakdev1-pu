/* Copyright Statement:
 *
 */

#ifndef __HAL_EFUSE_H__
#define __HAL_EFUSE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file hal_efuse.h
 *
 * @brief see sys_efuse.c in DVT tree. */

#define HAL_EFUSE_WRITE_MAGIC (0x35929054)

typedef enum {
    HAL_EFUSE_OK,
    HAL_EFUSE_INVALID_PARAMETER,
    HAL_EFUSE_INVALID_MAGIC,
    HAL_EFUSE_INVALID_ACCESS
} hal_efuse_status_t;


/**
 * Write data into eFuse.
 *
 * Write <i>len</i> bytes of data in buffer <i>buf</i> into eFuse at the
 * specified address <i>addr</i>.
 *
 * @param addr  address to write to.
 * @param buf   the data sequence to be write into eFuse.
 * @param len   the length of the date.
 *
 * @retval HAL_EFUSE_OK if write succeeded.
 * @retval HAL_EFUSE_INVALID_PARAMETER buf is incorrect, address is not supported,
 *         or length is not supported.
 * @retval HAL_EFUSE_INVALID_MAGIC the magic is wrong.
 *
 * @note On MT7687, eFuse write/read unit is 16 bytes aligned, and 16 bytes
 *       date is required to be written into flash. */
hal_efuse_status_t hal_efuse_write(uint32_t magic, uint16_t addr, const uint8_t *buf, uint8_t len);


/**
 * Read data from eFuse.
 *
 * Read <i>len</i> bytes of data from specified address <i>addr</i> in eFuse
 * into buffer <i>buf</i>.
 *
 * @param addr  address to read from.
 * @param buf   keep the read data sequence into this buffer.
 * @param len   the length of the date.
 *
 * @retval HAL_EFUSE_OK if read succeeded.
 * @retval HAL_EFUSE_INVALID_PARAMETER buf is incorrect, address is not supported,
 *         or length is not supported.
 *
 * @note On MT7687, eFuse write/read unit is 16 bytes aligned, and 16 bytes
 *       date is required to be written into flash.
 */
hal_efuse_status_t hal_efuse_read(uint16_t addr, uint8_t *buf, uint8_t len);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_EFUSE_H__ */

