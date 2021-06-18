/* Copyright Statement:
 *
 */

#include <string.h>
#include "bt_gattc.h"
#include "bt_gatt.h"
#include "bt_gatts.h"
#include "ble_ias.h"
#include "ble_bas.h"
#include "bt_gatts_service.h"

//Declare every record here
//service collects all bt_gatts_service_rec_t
//IMPORTAMT: handle:0x0000 is reserved, please start your handle from 0x0001
//GAP 0x0001

#ifdef MTK_BLE_SMTCN_ENABLE
extern const bt_gatts_service_t bt_if_dtp_service;
#endif
//extern const bt_gatts_service_t bt_if_gatt_service;
//extern const bt_gatts_service_t bt_if_gap_service;
extern const bt_gatts_service_t bt_if_dogp_service;
//extern const bt_gatts_service_t ble_bas_service;
//extern const bt_gatts_service_t ble_ias_service;

/**< gatt server collects all service. */
const bt_gatts_service_t * bt_if_clm_gatt_server[] = {
    &bt_if_gap_service, /**< handle range: 0x0001 to 0x0009. */
    &bt_if_gatt_service,/**< handle range: 0x0011 to 0x0015. */
#ifdef MTK_BLE_SMTCN_ENABLE
    &bt_if_dtp_service, //0x0014-0x0017
#endif
    &bt_if_dogp_service,/**< handle range: 0x0020 to 0x0025. */
    &ble_bas_service,/**< handle range: 0x0031 to 0x0034. */
    &ble_ias_service,/**< handle range: 0x0040 to 0x0042. */
    NULL
    };


/**< When GATTS get req from remote client, GATTS will call bt_get_gatt_server() to get application's gatt service DB. */
/**< You have to return the DB(bt_gatts_service_t pointer) to gatts stack. */
const bt_gatts_service_t** bt_get_gatt_server()
{ 
    return bt_if_clm_gatt_server;
}

