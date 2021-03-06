/* Copyright Statement:
 *
 */

#ifndef __FLASH_DISK_INTERNAL_H__
#define __FLASH_DISK_INTERNAL_H__

/*******************************************
*   Include File
********************************************/

#include "hal_flash_disk.h"
#ifdef HAL_FLASH_MODULE_ENABLED
#include "hal_flash_custom_memorydevice.h"
#include "hal_flash_opt.h"
#include "hal_flash_mtd.h"
#include "mt7686.h"
#include <stdio.h>
#include <stdlib.h>
#include "hal_flash_drvflash.h"

#if defined(__SINGLE_BANK_NOR_FLASH_SUPPORT__)
//#include "intrCtrl.h"
//#include "drv_comm.h"
#endif /*__SINGLE_BANK_NOR_FLASH_SUPPORT__*/

#ifdef __INTEL_SIBLEY__
#include "app_buff_alloc.h" //get control buffer
#endif //__INTEL_SIBLEY__


/*******************************************
*   Structure and Macro Definition
********************************************/
#define RAW_DISK0 0
#define RAW_DISK1 1


#ifdef __SYSDRV_BACKUP_DISK_RAW__

#define BACKUP_HEADER_LEN (FILE_PREFIX_LEN + sizeof(uint32_t))
#define INIT_MARK  0x1234
#define LOCK_MARK  0x4321

#ifdef __INTEL_SIBLEY__
#define SIBLEY_REGION_SIZE 1024
#endif //__INTEL_SIBLEY__

#endif //__SYSDRV_BACKUP_DISK_RAW__


// Flash raw disk driver's data
typedef ONE_BYTE_ALIGN_ADS struct {
    uint32_t   DiskSize;
    NOR_MTD_Driver *MTDDriver;       ///< MTD driver
    void    *MTDData;                ///< MTD data
    NOR_MTD_FlashInfo FlashInfo;     ///< Flash information
#if defined (__INTEL_SIBLEY__) && defined(__SYSDRV_BACKUP_DISK_RAW__)
    uint32_t    bufIdx;
    BYTE    *Buffer;                 ///< SIBLEY Backup Partition Buffer(1024 bytes): used as write buffer and write data in control mode
#endif
    bool is_mount;
} NOR_FLASH_DISK_Data;

/*******************************************
*   Function and Variable Definition
********************************************/
#ifdef __NOR_SUPPORT_RAW_DISK__
extern NOR_FLASH_DISK_Data FlashDiskDriveData[NOR_BOOTING_NOR_DISK_NUM];
#endif

extern bool         INT_QueryExceptionStatus(void);
extern uint32_t       BlockIndex(void *DriverData, uint32_t blk_addr);
extern kal_mutexid      fdm_reclaim_mutex;

hal_flash_status_t get_NOR_init_status(void);
/* Raw disk API */
int32_t readRawDiskData(NOR_FLASH_DISK_Data *D, uint32_t addr, uint8_t *data_ptr, uint32_t len);
#if defined(__NOR_SUPPORT_RAW_DISK__) || defined(__NOR_FULL_DRIVER__)
int32_t writeRawDiskData(NOR_FLASH_DISK_Data *D, uint32_t addr, uint8_t *data_ptr, uint32_t len);
int32_t eraseRawDiskBlock(NOR_FLASH_DISK_Data *D, uint32_t block_baseaddr);
#endif //__NOR_SUPPORT_RAW_DISK__ || __NOR_FULL_DRIVER__

#endif
#endif //__FLASH_DISK_H__
