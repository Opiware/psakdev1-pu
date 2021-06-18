/* Copyright Statement:
 *
 */

#ifndef __BLE_PXP_MAIN_H__
#define __BLE_PXP_MAIN_H__

#include "ble_gatt_srv.h"
#include "stdint.h"
#include "ble_gatt_utils.h"

typedef struct {
    uint32_t flag;
} ble_pxp_context_t;


void ble_pxp_init(void);

void ble_pxp_deinit(void);

ble_pxp_context_t *ble_pxp_get_context(void);

#endif /* __BLE_PXP_MAIN_H__ */

