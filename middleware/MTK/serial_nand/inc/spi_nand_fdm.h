/* Copyright Statement:
 *
 */

#ifndef __SERIAL_NAND_FLASH_FDM_H__
#define __SERIAL_NAND_FLASH_FDM_H__

#ifdef MTK_FATFS_ON_SERIAL_NAND

#include <stdint.h>

typedef struct {
    uint32_t block_size;
    uint16_t sector_size;
    uint32_t sectors;
} DEVICE_INFO_T;

extern int32_t spi_nand_fdm_ReadSectors(uint32_t Sector, uint32_t Sector_length, void *Data);

extern int32_t spi_nand_fdm_WriteSectors(uint32_t Sector, uint32_t Sector_length, void *Data);

extern int32_t spi_nand_fdm_LowLevelFormat(void);


extern int32_t spi_nand_GetDiskGeometry(DEVICE_INFO_T *info);

extern int32_t spi_nand_fdm_DAL_init(void);

extern void ms_mutex_lock(void);

extern void ms_mutex_unlock(void);

#endif
#endif

