/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#ifndef _SERIAL_FLASH_H_
#define _SERIAL_FLASH_H_ 


/* 4 bytes Command + 256 byte data */
#define WRITE_BUFFER_SIZE     (0x104)
#define FLASH_DADA_MAX_LENGTH (0x100)

#define COMMAND_SIZE    (0x5)
#define FLASH_BUSY      (0x1)
#define FLASH_INIT      (2)
#define FLASH_NOT_INIT  (-1)


typedef enum {
    FLASH_STATUS_IDLE = 0,
    FLASH_STATUS_BUSY = 1,
} flash_status_t;

typedef enum {
	  SPI_FLASH_STATUS_NOT_INIT = -2,
    SPI_FLASH_STATUS_ERROR = -1,
    SPI_FLASH_STATUS_OK,
} spi_flash_status_t;

typedef enum {
    FLASH_SECTOR_4K,
   	FLASH_SECTOR_32K,
   	FLASH_SECTOR_64K,
   	FLASH_SECTOR_ALL,
} block_size_type_t;	


flash_status_t get_flash_status(void);

flash_status_t wait_flash_ready(uint32_t sleep_ms);

int32_t spi_external_flash_get_rdid(uint8_t *buffer);

int32_t spi_external_flash_init(uint32_t frequency);

int32_t spi_external_flash_deinit();

int32_t spi_external_flash_read(uint32_t address, uint8_t *buffer, uint32_t length);

int32_t spi_external_flash_write(uint32_t address, uint8_t *data, int32_t length);

int32_t spi_external_flash_erase(uint32_t address, block_size_type_t block_size);

/*-----------------------------------------------------------*/
#endif


