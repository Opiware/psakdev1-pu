/* Copyright Statement:
 *
 */

/**
 * @file spim.h
 *
 *  SPI Master fuction support
 * */

#ifndef __SPI_H__
#define __SPI_H__

#ifdef HAL_SPI_MASTER_MODULE_ENABLED

#include "stdint.h"
#include "nvic.h"


#ifdef __cplusplus
extern "C" {
#endif


#define SPIM_BUSY (1)
#define SPIM_IDLE (0)

#define spim_check_and_set_busy(busy_status)               \
do {                                                       \
       uint32_t saved_mask;                                \
       saved_mask = save_and_set_interrupt_mask();         \
       if(g_spi_master_status == SPIM_BUSY) {              \
           busy_status = HAL_SPI_MASTER_STATUS_ERROR_BUSY; \
       } else {                                            \
           g_spi_master_status = SPIM_BUSY;                \
           busy_status = HAL_SPI_MASTER_STATUS_OK;         \
       }                                                   \
       restore_interrupt_mask(saved_mask);                 \
}while(0)

#define spim_set_idle()                                    \
do {                                                       \
       g_spi_master_status = SPIM_IDLE;                    \
}while(0)


#define SPI_MASTER_MB_LSB_FIRST             (0x1UL << 3)
#define SPI_MASTER_MB_MSB_FIRST             (0x0UL << 3)

#define SPI_MASTER_CPOL_0                   (0x0UL << 4)
#define SPI_MASTER_CPOL_1                   (0x1UL << 4)

#define SPI_MASTER_CPHA_0                   (0x0UL << 5)
#define SPI_MASTER_CPHA_1                   (0x1UL << 5)

#define SPI_MASTER_INT_DISABLE              (0x0UL << 9)
#define SPI_MASTER_INT_ENABLE               (0x1UL << 9)

#define SPI_MASTER_HALF_DUPLEX              (0x0UL << 10)
#define SPI_MASTER_FULL_DUPLEX              (0x1UL << 10)

#define SPI_MASTER_SLAVE_SEL_0              (0x0UL << 29)
#define SPI_MASTER_SLAVE_SEL_1              (0x1UL << 29)


/*Extension flag*/
#define NO_EXTN        (0x0)
/*Transfer flag*/
#define CMD_ONLY       (0x0)
#define SPI_READ       (0x1)
#define SPI_WRITE      (0x2)

typedef void (*USER_CALLBACK)(void);

/**
 * @brief  Initialize SPI master with specific setting.
 *
 * @param setting   [IN] Initial setting for SPI master.
 *                       MSB_FIRST | CPOL_0 | CPHA_0 |
 *                       INT_ENABLE | HALF_DUPLEX | SLAVE_SEL_0.
 * @param clock     [IN] output_clock = 120Mhz/(clock+2), output_clock max value is 12Mhz
 * @param callback  [IN] Callback function
 *
 * @return Negative value if there is a failure. Success otherwise.
 *
 * @note Use gpio_32, gpio_31, gpio_30, gpio_29. */
//int32_t spim_init(uint32_t setting, uint32_t clock, USER_CALLBACK callback);
int32_t spim_init(uint32_t setting, uint32_t clock);

/**
 * @brief  SPI master TX data routines.
 *
 * @param  buf              [IN] The data buffer. The data in the buffer would be sent out to SPI bus.
 * @param  buf_cnt          [IN] The number of buffer to WRITE.
 *
 * @return Negative value if there is a failure. Success otherwise. */
int32_t spim_write(uint8_t *buf, const uint32_t buf_cnt);

/**
 * @brief  SPI master RX data routines.
 *
 * @param  cmd              [IN] Read command.
 * @param  n_cmd_byte       [IN] The number of command bytes. The range should be less than 4 bytes
 * @param  buf              [IN] The data buffer. The buffer would be the data read from SPI bus.
 * @param  buf_cnt          [IN] The number of buffer to READ.
 *
 * @return Negative value if there is a failure. Success otherwise. */
int32_t spim_read(const uint32_t cmd, const uint32_t n_cmd_byte, uint8_t *buf, const uint32_t buf_cnt);

#ifdef __cplusplus
}
#endif

#endif /* HAL_SPI_MASTER_MODULE_ENABLED */

#endif
