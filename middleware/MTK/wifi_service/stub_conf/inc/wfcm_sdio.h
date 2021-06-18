/* Copyright Statement:
 *
 */

#ifndef __WFCM_SDIO_H__
#define __WFCM_SDIO_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "wfc_stub.h"

int wfcm_if_sdio_init(void);
void wfcm_if_sdio_reinit(void);
void wfcm_if_sdio_deinit(void);

void wfcm_mq_free(T_WFC_QBUF *qbuf);
void wfcm_mq_clear(T_WFC_QBUF *qbuf);
int32_t wfcm_mq_get_buf(uint32_t ctrl_idx, uint32_t *qidx);

void wfcm_mem_align_clr(uint8_t *pbuf, uint32_t bufSize);
void wfcm_sdio_cmd_cp(uint16_t opcode, T_WFC_QBUF *qbuf, uint8_t *param, uint32_t paramSize, uint8_t forISR);
void wfcm_sdio_memq_get_qbuf(T_WFC_QBUF *qbuf);
bool wfcm_sdio_send_data(T_WFC_QBUF *qbuf, uint8_t qbuf_release);
bool wfcm_sdio_receive_cmdrsp(uint8_t *rx_buf, uint32_t *bufSize);
bool wfcm_sdio_receive_data(uint8_t *pbuf, uint32_t bufSize);
void wfcm_sdio_htx_cp(uint16_t opcode, T_WFC_QBUF *qbuf, uint8_t *htxptr, uint32_t htxSize);
void wfcm_sido_hrx_cp(T_WFC_QBUF *qbuf, uint8_t *pbuf);

void wfcm_dump_buf(uint8_t *pbuf, uint32_t bufSize);

#ifdef __cplusplus
}
#endif


#endif  /* __WFCM_SDIO_H__ */
