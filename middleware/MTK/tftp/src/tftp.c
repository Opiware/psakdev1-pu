/* Copyright Statement:
 *
 */

#ifdef __linux__
#include <arpa/inet.h>
#endif /* __linux__ */

#include <stdio.h>
#include <string.h>


#include "tftp.h"
#include "port.h"

#define get_opcode(buf)         ntohs(*(uint16_t *)buf)
#define get_errcode(buf)        ntohs( *( ((uint16_t *)buf) + 1 ) )
#define get_block(buf)        ntohs( *( ((uint16_t *)buf) + 1 ) )

#ifdef TFTP_DEBUG
log_create_module(tftp, PRINT_LEVEL_INFO);
#endif

/**
 * Append a string to ptr and a null character. */
static void *_append_str(uint8_t *ptr, const char *str)
{
    uint16_t len = os_strlen(str);

    os_memcpy(ptr, str, len);

    ptr += len;

    ((char *)ptr)[0] = '\0';

    return ++ptr;
}


tftp_status_t tftp_ack(void *sock, uint16_t block)
{
    tftp_ack_pkt_t pkt;

    TFTP_FUNC_IN;

    pkt.opcode = htons(TFTP_OPCODE_ACK);
    pkt.block  = htons(block);

    if (tftp_sock_send(sock, (const uint8_t *)&pkt, sizeof(pkt)) < 0) {
        TFTP_FUNC_OUT;
        return TFTP_STATUS_SEND_ERROR;
    }

    TFTP_FUNC_OUT;
    return TFTP_STATUS_SEND_DONE;
}


tftp_status_t tftp_error(void *sock, uint8_t *buf, tftp_error_code_t err)
{
    tftp_error_pkt_t    *pkt = (tftp_error_pkt_t *)buf;
    uint8_t             *ptr;

    TFTP_FUNC_IN;

    pkt->opcode     = htons(TFTP_OPCODE_ERROR);
    pkt->error_code = htons(err);
    ptr             = buf + sizeof(pkt);
    ptr             = _append_str(ptr, "ERROR");

    if (tftp_sock_send(sock, buf, ptr - buf) < 0) {
        TFTP_FUNC_OUT;
        return TFTP_STATUS_SEND_ERROR;
    }

    TFTP_FUNC_OUT;
    return TFTP_STATUS_SEND_DONE;
}


tftp_status_t tftp_rrq(void *sock, uint8_t *buf, const char *filename)
{
    tftp_pkt_t  *pkt = (tftp_pkt_t *)buf;
    uint8_t     *ptr;

    TFTP_FUNC_IN;

    pkt->opcode = htons(TFTP_OPCODE_RRQ);
    ptr         = buf + sizeof(pkt->opcode);
    ptr         = _append_str(ptr, filename);
    ptr         = _append_str(ptr, "octet");

    if (tftp_sock_send(sock, buf, ptr - buf) < 0) {
        TFTP_FUNC_OUT;
        return TFTP_STATUS_SEND_ERROR;
    }

    TFTP_FUNC_OUT;
    return TFTP_STATUS_SEND_DONE;
}

// for memset
#include <string.h>


tftp_status_t tftp_rrq_recv(
    void                *sock,
    uint8_t             *buf,
    tftp_error_code_t   *err,
    uint16_t            *len,
    uint16_t            *block)
{
    int16_t     rx_len;
    uint16_t    opcode;
    uint16_t    new_block;

    TFTP_FUNC_IN;

    os_memset(buf, 0, TFTP_BLOCK_SIZE);

    if ((rx_len = tftp_sock_recv(sock, buf, TFTP_BLOCK_SIZE)) < 0) {
        TFTP_FUNC_OUT;
        return TFTP_STATUS_RCVD_ERROR;
    }

    opcode = get_opcode(buf);
    if (opcode == TFTP_OPCODE_ERROR) {
        *err = (tftp_error_code_t)get_errcode(buf);
        TFTP_FUNC_OUT;
        return TFTP_STATUS_RPKT_ERROR;
    } else if (opcode != TFTP_OPCODE_DATA) {
        tftp_error(sock, buf, TFTP_ERRNO_ILLEGAL_TFTP_OPERATION);
        TFTP_FUNC_OUT;
        return TFTP_STATUS_PROT_ERROR;
    }

    if (rx_len < 4) {
        printf("-");
        *len = 0;
        TFTP_FUNC_OUT;
        return TFTP_STATUS_RECV_MORE;
    } else if (rx_len > TFTP_BLOCK_SIZE) {
        printf("+");
        *len = 0;
        TFTP_FUNC_OUT;
        return TFTP_STATUS_RECV_MORE;
    }

    new_block = get_block(buf);

    if (new_block == ((*block) + 1)) {
        *block = new_block;

        if (tftp_ack(sock, new_block) == TFTP_STATUS_SEND_ERROR) {
            TFTP_FUNC_OUT;
            return TFTP_STATUS_SEND_ERROR;
        }

        *len = rx_len;
        printf("receive_data_pack, size = %d\n", rx_len);

        if (rx_len == TFTP_BLOCK_SIZE || rx_len == 0) {
            TFTP_FUNC_OUT;
            printf("pack_count = %d\n", new_block);
            return TFTP_STATUS_RECV_MORE;
        }

        printf("end at block %d\n", new_block);
        TFTP_FUNC_OUT;
        return TFTP_STATUS_RCVD_DONE;
    }

    if (new_block == *block) {
        printf("= %d\n", new_block);
        if (tftp_ack(sock, new_block) == TFTP_STATUS_SEND_ERROR) {
            TFTP_FUNC_OUT;
            return TFTP_STATUS_SEND_ERROR;
        }
    } else if (new_block > *block) {
        printf(">");
    } else {
        printf("<");
    }

    /* error handling */
    new_block   = *block;
    *len        = 0;

    TFTP_FUNC_OUT;
    return TFTP_STATUS_RECV_MORE;
}

