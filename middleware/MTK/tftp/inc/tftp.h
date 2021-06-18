/* Copyright Statement:
 *
 */

#ifndef __TFTP_H__
#define __TFTP_H__

#include <stdint.h>
#include "syslog.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TFTP_PORT           (69)

/**
 * 2 bytes opcode, 2 bytes block number, and 512 bytes data. */
#define TFTP_BLOCK_SIZE     (4 + 512)

typedef enum
{
    TFTP_OPCODE_RRQ = 1,
    TFTP_OPCODE_WRQ,
    TFTP_OPCODE_DATA,
    TFTP_OPCODE_ACK,
    TFTP_OPCODE_ERROR,
} tftp_opcode_t;


typedef enum {
    TFTP_ERRNO_OK,
    TFTP_ERRNO_FILE_NO_FOUND,
    TFTP_ERRNO_ACCESS_VIOLATION,
    TFTP_ERRNO_DISK_FULL_OR_ALLOCATION_EXCEEDED,
    TFTP_ERRNO_ILLEGAL_TFTP_OPERATION,
    TFTP_ERRNO_UNKNOWN_TRANSFER_ID,
    TFTP_ERRNO_FILE_ALREADY_EXISTS,
    TFTP_ERRNO_NO_SUCH_USER
} tftp_error_code_t;


typedef enum {
    TFTP_STATUS_SEND_ERROR, // sending failed
    TFTP_STATUS_SEND_DONE,  // sending done
    TFTP_STATUS_RCVD_ERROR, // receiving failed
    TFTP_STATUS_RPKT_ERROR, // received ERROR packet
    TFTP_STATUS_PROT_ERROR, // received unexpected opcode, sent error pkt
    TFTP_STATUS_RCVD_DONE,  // receive completed
    TFTP_STATUS_RECV_MORE   // more data to be received
} tftp_status_t;

typedef struct tftp_pkt_s {
    uint16_t    opcode;
} tftp_pkt_t;


typedef struct tftp_ack_pkt_s {
    uint16_t    opcode;
    uint16_t    block;
} tftp_ack_pkt_t;


typedef struct tftp_error_pkt_s {
    uint16_t    opcode;
    uint16_t    error_code;
} tftp_error_pkt_t;

#ifndef MTK_DEBUG_LEVEL_NONE
#define TFTP_DEBUG 1
#else
#define TFTP_DEBUG 0
#endif

#if TFTP_DEBUG
#define TFTP_FUNC_IN   LOG_I(tftp, "enter: %s %d\n", __FUNCTION__, __LINE__)
#define TFTP_FUNC_OUT   LOG_I(tftp, "exit: %s %d\n", __FUNCTION__, __LINE__)
#else
#define TFTP_FUNC_IN
#define TFTP_FUNC_OUT
#endif

/**
 * Create a RRQ packet and send it out.
 *
 * 1. Prepare read request.
 * 2. Send read request.
 * 3. Wait data block / error.
 * 4. if data block, send ack, if error then done.
 * 5. if data block is less than 512 bytes, done.
 *
 * @retval TFTP_STATUS_SEND_ERROR sending failed
 * @retval TFTP_STATUS_SEND_DONE  sending done */
tftp_status_t tftp_rrq(void *sock, uint8_t *buf, const char *filename);


/**
 * Receive a packet and process it according to its content.
 *
 * @retval TFTP_STATUS_RCVD_ERROR receiving failed
 * @retval TFTP_STATUS_RPKT_ERROR received ERROR packet
 * @retval TFTP_STATUS_PROT_ERROR received unexpected opcode, sent error pkt
 * @retval TFTP_STATUS_SEND_ERROR send ack packet error
 * @retval TFTP_STATUS_RCVD_DONE  receive completed
 * @retval TFTP_STATUS_RECV_MORE  more data to be received */
tftp_status_t tftp_rrq_recv(
    void                *sock,
    uint8_t             *buf,
    tftp_error_code_t   *err,
    uint16_t            *len,
    uint16_t            *block);


/** create and send an ACK packet. */
tftp_status_t tftp_ack(void *sock, uint16_t block);


/** create and send an ERROR packet. */
tftp_status_t tftp_error(void *sock, uint8_t *buf, tftp_error_code_t err);


#ifdef __cplusplus
}
#endif


#endif /* __TFTP_H__ */

