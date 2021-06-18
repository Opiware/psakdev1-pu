/* Copyright Statement:
 *
 */

#include "hal_platform.h"

#ifndef __HAL_SLEEP_MANAGER_PLATFORM_H__
#define __HAL_SLEEP_MANAGER_PLATFORM_H__

#ifdef HAL_SLEEP_MANAGER_ENABLED

typedef enum {
    SLEEP_LOCK_DMA              = 0,
    SLEEP_LOCK_AUDIO_TOP        = 1,
    SLEEP_LOCK_ASYS_TOP         = 2,
    SLEEP_LOCK_SPI_MASTER       = 3,
    SLEEP_LOCK_SPI_SLAVE        = 4,
    SLEEP_LOCK_UART0            = 5,
    SLEEP_LOCK_UART1            = 6,
    SLEEP_LOCK_UART2            = 7,
    SLEEP_LOCK_I2C0             = 8,
    SLEEP_LOCK_I2C1             = 9,
    SLEEP_LOCK_AUDIO_TOP_AHB    = 10,
    SLEEP_LOCK_ASYS_TOP_AHB     = 11,
    SLEEP_LOCK_SDIO_MST         = 12,
    SLEEP_LOCK_SDIO_SLV         = 13,
    SLEEP_LOCK_USER_START_ID    = 14,
    SLEEP_LOCK_INVALID_ID       = 0xFF
} sleep_management_lock_request_t;

typedef enum {
    SLEEP_BACKUP_RESTORE_FLASH          = 0,
    SLEEP_BACKUP_RESTORE_AUDIO_TOP      = 1,
    SLEEP_BACKUP_RESTORE_ASYS_TOP       = 2,
    SLEEP_BACKUP_RESTORE_SPI_MASTER     = 3,
    SLEEP_BACKUP_RESTORE_SPI_SLAVE      = 4,
    SLEEP_BACKUP_RESTORE_UART           = 5,
    SLEEP_BACKUP_RESTORE_I2C            = 6,
    SLEEP_BACKUP_RESTORE_PWM            = 7,
    SLEEP_BACKUP_RESTORE_AUDIO_TOP_AHB  = 8,
    SLEEP_BACKUP_RESTORE_ASYS_TOP_AHB   = 9,
    SLEEP_BACKUP_RESTORE_SDIO_MST       = 10,
    SLEEP_BACKUP_RESTORE_SD_CARD        = 11,
    SLEEP_BACKUP_RESTORE_UART_RX_EINT   = 12,
    SLEEP_BACKUP_RESTORE_CONNNSYS       = 13,
    SLEEP_BACKUP_RESTORE_AUXADC         = 14, 
    SLEEP_BACKUP_RESTORE_MODULE_MAX     = 15,
    SLEEP_BACKUP_RESTORE_USER           = 16
} sleep_management_backup_restore_module_t;

#define SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX 8
#define DEEP_SLEEP_GPT HAL_GPT_0

#endif /* HAL_SLEEP_MANAGER_ENABLED */
#endif

