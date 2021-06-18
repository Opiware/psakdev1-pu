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
//#include "connection_info.h"

BT_EXTERN_C_BEGIN
#define MY_VENDOR_SERIAL_NUMBER       "01-32-588"

//INFO:Application create record should sync record's perm(bt_gatts_service_rec_t.perm) and attribute information which will read out by client.
//     BT stack will check bt_gatts_service_rec_t.perm only.

//---------------Record define -------------------
/*------------------------------------------------------------------------------------
// ---!!IMPORTANT!!---
// If the attribute is writable, in characteristic define should support callback API.
//
-------------------------------------------------------------------------------------*/
//--------------extern server DB-----------------

extern char gatts_device_name[256];
extern uint16_t gap_appearance;

//bt_status_t bt_gatt_set_server(const bt_gatts_service_t *gatts_srv);//return starting_handle and ending handle
BT_EXTERN_C_END
#endif /*__GATT_SERVICE_H__*/
