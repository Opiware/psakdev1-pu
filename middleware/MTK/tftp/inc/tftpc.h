/* Copyright Statement:
 *
 */

#ifndef __TFTPC_H__
#define __TFTPC_H__

#include <stdint.h>

#include "tftp.h"


typedef enum {
    TFTPC_STATUS_OK,
    TFTPC_STATUS_MORE,
    TFTPC_STATUS_DONE,
    TFTPC_STATUS_ERR,
} tftpc_status_t;


typedef enum {
    TFTPC_STATE_IDLE, // TFTP client created, transmission not targetd yet.
    TFTPC_STATE_MORE, // There are more data to be received.
    TFTPC_STATE_TAIL,
    TFTPC_STATE_DONE, // Received all data.
    TFTPC_STATE_MAX,
} tftpc_state_t;


/**
 * the transmission and receive .
 * @note With LwIP, use pbuf in LwIP to reduce memory copy. */
typedef struct tftpc_s
{
    tftpc_state_t       state;                  /* state machine */
    void                *sock;                  /* socket handle */
    char                *filename;              /* filename */
    uint16_t            block;                  /* block number. */
    tftp_error_code_t   error_code;             /* error code */

    uint8_t             buf[TFTP_BLOCK_SIZE];   /* tx/rx buffer */
} tftpc_t;


/****************************************************************************
 *
 * API Functions.
 *
 ****************************************************************************/


tftpc_t *tftpc_read_init(const char      *raddr,
                         unsigned short  rport,
                         unsigned short  lport,
                         const char      *filename);


void tftpc_read_done(tftpc_t *tftpc);


tftpc_status_t tftpc_read_data(tftpc_t *tftpc, uint16_t *len);


#endif /* __TFTPC_H__ */


