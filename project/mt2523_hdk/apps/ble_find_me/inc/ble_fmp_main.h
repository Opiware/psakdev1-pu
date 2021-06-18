/* Copyright Statement:
 *
 */

#ifndef __BLE_FMP_MAIN_H__
#define __BLE_FMP_MAIN_H__

#include "ble_gatt_srv.h"
#include "stdint.h"
#include "ble_gatt_utils.h"

typedef struct {
    uint32_t flag;
} ble_fmp_context_t;


void ble_fmp_init(void);

void ble_fmp_deinit(void);

ble_fmp_context_t *ble_fmp_get_context(void);

#endif /* __BLE_PXP_MAIN_H__ */

