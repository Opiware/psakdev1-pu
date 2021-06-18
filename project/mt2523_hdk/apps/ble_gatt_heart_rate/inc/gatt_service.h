/* Copyright Statement:
 *
 */

#ifndef __GATT_SERVICE_H__
#define __GATT_SERVICE_H__

#include "bt_uuid.h"
#include "bt_system.h"
#include "bt_gattc.h"
#include "bt_gatt.h"
#include "bt_gatts.h"
#include "connection_info.h"

BT_EXTERN_C_BEGIN
#define BT_SIG_UUID_VENDOR_SERVICE              \
    {0x12,0x34,0x56,0x78,0x90,0x13,0x57,0x91,   \
     0x24,0x68,0x82,0x11,0x22,0x33,0x44,0x55}
#define MY_VENDOR_SERIAL_NUMBER       "01-32-588"
#define CLIENT_CHARC_CONFIGURATION_NOTIFICATION  0x0001
#define CLIENT_CHARC_CONFIGURATION_INDICATION  0x0002

//INFO:Application create record should sync record's perm(bt_gatts_service_rec_t.perm) and attribute information which will read out by client.
//     BT stack will check bt_gatts_service_rec_t.perm only.

//---------------Record define -------------------
/*------------------------------------------------------------------------------------
// ---!!IMPORTANT!!---
// If the attribute is writable, in characteristic define should support callback API.
//
-------------------------------------------------------------------------------------*/

//--------------extern UUID ---------------------
extern const bt_uuid_t BT_SIG_UUID_SERVICE_CHANGED;
extern const bt_uuid_t BT_SIG_UUID_DEVICE_NAME;
extern const bt_uuid_t BT_SIG_UUID_BATTERY_LEVEL;
extern const bt_uuid_t BT_SIG_UUID_SERIAL_NUMBER;
extern const bt_uuid_t BT_SIG_UUID_MANUFACTURER_NAME;
extern const bt_uuid_t BT_SIG_UUID_CENTRAL_ADDRESS_RESOLUTION;
//--------------extern server DB-----------------

extern char gatts_device_name[256];
extern uint16_t gap_appearance;
extern char gatts_manufacture_name[64];
extern uint32_t length_of_gatts_manufacture_name;
extern uint32_t buf_size_of_gatts_manufacture_name;
extern char gatts_manufacture_name_1[64];
extern uint32_t length_of_gatts_manufacture_name_1;
extern uint32_t buf_size_of_gatts_manufacture_name_1;

void bt_gatt_service_gap_gatts_bqb(void);
void bt_gatt_service_signed_write_with_authenticated_pairing(uint8_t authen_req);
void bt_gatt_service_change_1(void);
void bt_gatt_service_change_2(void);
void bt_gatt_service_regular_handle(void);
BT_EXTERN_C_END
#endif /*__GATT_SERVICE_H__*/

