/* Copyright Statement:
 *
 */

#ifndef __WFC_SDIO_H__
#define __WFC_SDIO_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_sdio.h"
#include "wfc_stub.h"

hal_sdio_status_t wfc_if_sdio_init(void);
void wfc_sdio_send_response(T_WFC_OPCODE *pwfc, uint16_t rspcode, uint8_t *txptr, uint32_t txsize, uint32_t hsize);
void wfc_sdio_send_data(uint8_t *txptr, uint32_t txsize);

void wfc_sido_htx_cp(T_WFC_QBUF *qbuf, uint8_t *pbuf, uint32_t offset);
void wfc_sdio_hrx_cp(T_WFC_QBUF *qbuf, uint8_t *hrxptr, uint32_t hrxSize);
void wfc_sdio_hevt_cp(T_WFC_QBUF *qbuf, uint8_t *hrxptr, uint32_t hrxSize);

int wfc_sdio_set_cmd_buf(void);
int wfc_sdio_set_htx_buf(void);

void wfc_sdio_free_cmd_buf(uint32_t qidx);
uint8_t *wfc_sdio_get_cmd_buf(uint32_t qidx);

void wfc_sdio_mq_reset(uint32_t ctrl);

void wfc_mq_push_hrx(T_WFC_QBUF *qbuf);
T_WFC_QBUF  *wfc_mq_pop_hrx(void);

int32_t wfc_mq_get_buf(uint32_t ctrl_idx, uint32_t *qidx);
void wfc_mq_clear(T_WFC_QBUF *qbuf);
void wfc_mq_free(T_WFC_QBUF *qbuf);
uint8_t wfc_mq_opcmd_process(T_WFC_QBUF *qbuf, uint8_t *isDTW);

void wfc_dump_buf(uint8_t *pbuf, uint32_t bufSize);

#ifdef __cplusplus
}
#endif


#endif  /* __WFC_SDIO_H__ */
