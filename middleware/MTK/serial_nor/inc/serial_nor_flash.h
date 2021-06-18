/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#ifndef _SERIAL_FLASH_H_
#define _SERIAL_FLASH_H_ 

#ifdef SERIAL_NOR_WITH_SPI_SUPPORT
#if ((PRODUCT_VERSION == 7687)||(PRODUCT_VERSION == 7697))

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes */
#include "hal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

//transfer data length, can define it by self.
#define FLASH_DADA_MAX_LENGTH (0x100)

#define COMMAND_SIZE    (0x5)
#define FLASH_BUSY      (1)
#define FLASH_INIT      (2)
#define FLASH_NOT_INIT  (-1)


typedef enum {
    FLASH_STATUS_BUSY = 1,
    FLASH_STATUS_IDLE = 0
}flash_status_t;

typedef enum {
    SERIAL_NOR_STATUS_NOT_INIT = -2,
    SERIAL_NOR_STATUS_ERROR = -1,
    SERIAL_NOR_STATUS_OK,
}serial_nor_status_t;

typedef enum {
    FLASH_SECTOR_4K,        //erase sector 4kB
    FLASH_SECTOR_32K,       //erase block 32kB
    FLASH_SECTOR_64K,       //erase block 64kB
    FLASH_SECTOR_ALL,       //erase flash chip
}block_size_type_t;

/*****************************************************************************
 * Functions
 *****************************************************************************/
/**
 * @brief  flash and spi init
 * @param[in]  spim_port, spi master port
 * @param[in]  frequency, spi master frequency
 * @return
 * #SERIAL_FLASH_STATUS_OK on success
 */
 serial_nor_status_t serial_nor_init(hal_spi_master_port_t spim_port, uint32_t frequency);

/**
 * @brief     flash deinit
 * @return
 * #SERIAL_NOR_STATUS_OK on success */

serial_nor_status_t serial_nor_deinit(void);

/**
 * @brief     get current flash status.
 * @return
 * # 0 is idle; 1 is busy
 */
int32_t serial_nor_status(void);

/**
 * @brief     get flash RDID
 * @param[in]  buff, a point to a four bytes buffer
 * #SERIAL_NOR_STATUS_OK on reading success
 */
serial_nor_status_t serial_nor_get_information(uint8_t *buff);

/**
 * @brief     extearnal flash read
 * @param[in]  start_address, starting address to read the data from
 * @param[out]  buffer, place to hold the incoming data
 * @param[in]  length,the length of the data content
 * @return
 * #SERIAL_NOR_STATUS_OK on success
 */
serial_nor_status_t serial_nor_read(uint32_t address, uint8_t *buffer, uint32_t length);

/**
 * @brief     flash write
 * @param[in]  start_address, starting address to write from.Before the address can be written to for the first time,
 *            the address located sector or block must first be erased.
 * @param[in]  length, data length
 * @param[in]  data, source data to be written
 * @return
 * #SERIAL_NOR_STATUS_OK on success
 */
serial_nor_status_t serial_nor_write(uint32_t address, uint8_t *data, uint32_t length);

/**
 * @brief     flash erase
 * @param[in]  start_address, starting address to erase from
 * @param[in]  block_type, the size of block to be erased
 * @return
 * #SERIAL_NOR_STATUS_OK on success
 */
serial_nor_status_t serial_nor_erase(uint32_t address, block_size_type_t block_size);
/*-----------------------------------------------------------*/
#endif
#endif
#endif

