/* Copyright Statement:
 *
 */

#ifndef __HAL_UID_H__
#define __HAL_UID_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file hal_uid.h
 *
 * @brief This file provides the API for reading a UID for the device. A UID
 * is a ID for identifying a device. It could be used in identification,
 * authorization, or as an MAC address, and so on. */

#define MT7687_UID_LENGTH   (8)

typedef enum {
    HAL_UID_OK,
    HAL_UID_INVALID_PARAMETER
} hal_uid_status_t;


/**
 * Read UID of the chip.
 *
 * Read a predefined UID from the chip.
 *
 * @param buf   the data buffer to write the UID into.
 * @param len   the length of the buffer.
 *
 * @retval HAL_UID_OK if read succeeded.
 * @retval HAL_UID_INVALID_PARAMETER buf pointer is incorrect or length is
 *         not supported. */
hal_uid_status_t hal_uid_read(uint8_t *buf, uint8_t len);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_UID_H__ */

