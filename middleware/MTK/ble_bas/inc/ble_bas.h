/* Copyright Statement:
 *
 */

#ifndef __BLE_BAS_H__
#define __BLE_BAS_H__

/**
 * @addtogroup Bluetooth_Services_Group Bluetooth Services
 * @{
 * @addtogroup BluetoothServices_BAS BLE BAS
 * @{
 * This section manages the read/write events of Battery Level Characteristic from a peer device and provides API to send notification to the peer device when the battery state changes.
 *
 * Terms and Acronyms
 * ======
 * |Terms                         |Details                                                                  |
 * |------------------------------|-------------------------------------------------------------------------|
 * |\b BAS                        | Battery Service. This service exposes the battery state and battery level to the peer device. |
 *
 * @section ble_bas_api_usage How to use this module
 * - Step 1. Add BAS service to the application's GATT service database. And then return the bt_gatts_service_t pointer to GATTS stack by implementing the user-defined callback @ref bt_get_gatt_server(). 
 *  - Sample Code:
 *     @code
 *               // The GATTS collects all services.
 *               const bt_gatts_service_t * ble_gatt_server[] = {
 *                   &ble_gap_service,  // handle range: 0x0001 to 0x0009.
 *                   &ble_gatt_service, // handle range: 0x0011 to 0x0015.
 *                   &ble_bas_service,  // handle range: 0x0031 to 0x0034.
 *                   NULL
 *                };
 *                const bt_gatts_service_t** bt_get_gatt_server()
 *                { 
 *                    return ble_gatt_server;
 *                }

 *     @endcode
 * - Step 2. Implement the user-defined callback @ref ble_bas_read_callback() to listen to the read event of Battery Level Characteristic and Client Configuration Characteristic Descriptor from the peer device.
 *  - Sample Code:
 *     @code
 *                uint8_t ble_bas_read_callback(ble_bas_event_t event, uint16_t conn_handle)
 *                {
 *                    if (conn_handle) {
 *                        switch (event) {
 *                            case BLE_BAS_EVENT_BATTRY_LEVEL_READ:
 *                                uint8_t battery_level = 100;
 *                                return battery_level;
 *                            case BLE_BAS_EVENT_CCCD_READ:
 *                                uint8_t notify_enabled = 1;
 *                                return notify_enabled;
 *                            default :
 *                                break;
 *                        }
 *                    }
 *                    return 0;
 *                }
 *     @endcode
 * - Step 3. Implement the user-defined callback @ref ble_bas_write_callback() to listen to the write event of Client Configuration Characteristic Descriptor from the peer device.
 *  - Sample Code:
 *     @code
 *                void ble_bas_write_callback(ble_bas_event_t event, bt_handle_t conn_handle, void *data)
 *                {
 *                    uint16_t cccd_value = 0;
 *                    cccd_value = *(uint16_t *)data;
 *                    if ((conn_handle) && (BLE_BAS_EVENT_CCCD_WRITE == event)) {
 *                        //Save the data;
 *                    }
 *                }
 *     @endcode
 * - Step 4. Notify the Battery State of the device to the peer device.
 *  - Sample code:
 *     @code 
 *                uint8_t battery_level = get_current_battery_api();
 *                ble_bas_notify_battery_level(conn_handle, battery_level);
 *     @endcode */

#include "bt_type.h"
#include "bt_system.h"
#include "bt_gatt.h"
#include "bt_gatts.h"
#include "bt_gap_le.h"
#include "bt_platform.h"


BT_EXTERN_C_BEGIN

/**
 * @defgroup BluetoothServices_BAS_define Define
 * @{
 * This section defines the BAS event types. */

typedef uint16_t ble_bas_event_t;
#define BLE_BAS_EVENT_BATTRY_LEVEL_READ         0x00 /**< Battery Level Characteristic Read event. */
#define BLE_BAS_EVENT_CCCD_READ                 0x01 /**< Client Characteristic Configuration Read event. */
#define BLE_BAS_EVENT_CCCD_WRITE                0x02 /**< Client Characteristic Configuration Write event. */

/**
 * @} */

/* --------------Extern Service --------------------- */
extern const bt_gatts_service_t ble_bas_service; /*< Battery Service. */

/**
 * @brief   This function sends a notification to a peer device about the current battery level.
 * @param[in] conn_handle        is the connection handle.
 * @param[in] battery_level      is the current battery level.
 * @return    BT_STATUS_SUCCESS, the notification is sent successfully.
 *            BT_STATUS_FAIL, the notification failed to send. */
bt_status_t ble_bas_notify_battery_level(bt_handle_t conn_handle, uint8_t battery_level);


/**
 * @brief   This function is a user-defined callback for the application to listen to the read event of Battery Level Characteristic and Client Configuration Characteristic Descriptor.
 * @param[in] event           is the event of type @ref ble_bas_event_t.
 * @param[in] conn_handle     is the connection handle.
 * @return                    the response to the read event of Battery Level Characteristic or Client Configuration Characteristic Descriptor. If the read event type is @ref BLE_BAS_EVENT_BATTRY_LEVEL_READ, 
 *                            the return value is the corresponding battery level. If the read event type is @ref BLE_BAS_EVENT_CCCD_READ, the return value is either 0 or 1. */
uint8_t ble_bas_read_callback(ble_bas_event_t event, bt_handle_t conn_handle);

/**
 * @brief   This function is a user-defined callback for the application to listen to the write event of Client Configuration Characteristic Descriptor.
 * @param[in] event           is the event of type @ref ble_bas_event_t.
 * @param[in] conn_handle     is the connection handle.
 * @param[in] data            is the data of write event from a remote device.
 * @return    void. */
void ble_bas_write_callback(ble_bas_event_t event, bt_handle_t conn_handle, void *data);


BT_EXTERN_C_END
/**
 * @}
 * @} */

#endif /*__BLE_BAS_H__*/


