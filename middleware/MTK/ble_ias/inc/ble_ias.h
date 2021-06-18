/* Copyright Statement:
 *
 */
#ifndef __BLE_IAS_H__
#define __BLE_IAS_H__

/**
 * @addtogroup Bluetooth_Services_Group Bluetooth Services
 * @{
 * @addtogroup BluetoothServices_IAS BLE IAS
 * @{
 * This section defines the database of Immediate Alert Service and manages the write event of Alert Level Characteristic from a peer device.
 *
 * Terms and Acronyms
 * ======
 * |Terms                         |Details                                                                  |
 * |------------------------------|-------------------------------------------------------------------------|
 * |\b IAS                        | Immediate Alert Service. This service exposes a control point to allow a peer device to cause the device to immediately alert. |
 *
 * @section ble_ias_api_usage How to use this module
 * - Step 1. Add IAS service to the application's GATT service database. And then return the bt_gatts_service_t pointer to GATTS stack by implementing the user-defined callback @ref bt_get_gatt_server(). 
 *  - Sample Code:
 *     @code
 *               // The GATTS collects all services.
 *               const bt_gatts_service_t * ble_gatt_server[] = {
 *                   &ble_gap_service,  // handle range: 0x0001 to 0x0009.
 *                   &ble_gatt_service, // handle range: 0x0011 to 0x0015.
 *                   &ble_ias_service,  // handle range: 0x0040 to 0x0042.
 *                   NULL
 *                };
 *                const bt_gatts_service_t** bt_get_gatt_server()
 *                { 
 *                    return ble_gatt_server;
 *                }

 *     @endcode
 * - Step 2. Implement the user-defined callback @ref ble_ias_alert_level_write_callback() to listen to the write event of the Alert Level Characteristic.
 *  - Sample Code:
 *     @code
 *                void ble_ias_alert_level_write_callback(uint16_t conn_handle, uint8_t alert_level)
 *                {
 *                    if (conn_handle) {
 *                        // Save the alert level.
 *                    }
 *                }
 *     @endcode */

#include "bt_type.h"
#include "bt_system.h"
#include "bt_gatt.h"
#include "bt_gatts.h"
#include "bt_gap_le.h"
#include "bt_platform.h"


BT_EXTERN_C_BEGIN
/* --------------Extern Service --------------------- */
extern const bt_gatts_service_t ble_ias_service; /*< Immediate Alert Service. */

/**
 * @brief   This function is a user-defined callback for the application to listen to the write event of Alert Level Characteristic.
 * @param[in] conn_handle     is the connection handle.
 * @param[in] alert_level     is the alert level value written by the remote device.
 * @return    void. */
void ble_ias_alert_level_write_callback(uint16_t conn_handle, uint8_t alert_level);

BT_EXTERN_C_END

/**
 * @}
 * @} */

#endif /*__BT_BATTERY_SERVICE_H__*/
