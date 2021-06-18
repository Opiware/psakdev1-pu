/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_DB_CUSTOM_H__
#define __BT_SINK_SRV_DB_CUSTOM_H__
#include <stdint.h>
#include <stdbool.h>
#include "bt_sink_srv_db.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT_SINK_SRV_DB_FILE "devinfo.db"
#define BT_SINK_SRV_SCAN_DB_FILE "devscaninfo.db"
#define BT_SINK_SRV_DB_COD_FILE "devcod.db"
#define BT_SINK_SRV_SDAP_DEVDB_FILE "dev_sdap.db"
#define BT_SINK_SRV_DB_PATH "d:\\@bt"

#define BT_SINK_SRV_NVDM_GROUP "BT_SINK"
#define BT_SINK_SRV_NVDM_ITEM_DEV_INFO "devinfo"
#define BT_SINK_SRV_NVDM_ITEM_SCAN "scan"
#define BT_SINK_SRV_NVDM_ITEM_SDAP "sdap"

typedef enum {
    BT_SINK_SRV_CUSTOM_DB_DEV_INFO,
    BT_SINK_SRV_CUSTOM_DB_SCAN_INFO,
    BT_SINK_SRV_CUSTOM_DB_SDAP_INFO,
    BT_SINK_SRV_CUSTOM_DB_MAX,
} bt_sink_srv_custom_db_type_t;
bt_sink_srv_custom_db_type_t bt_sink_srv_db_custom_is_special_type(bt_sink_srv_db_t *db);
bool bt_sink_srv_db_custom_read(bt_sink_srv_db_t *db);
bool bt_sink_srv_db_custom_write(bt_sink_srv_db_t *db);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_DB_CUSTOM_H__ */
