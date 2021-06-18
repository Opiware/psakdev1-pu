/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_DB_H__
#define __BT_SINK_SRV_DB_H__

#include <stdint.h>
#include <stdbool.h>
#include "bt_sink_srv_resource.h"
#include "bt_sink_srv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT_SINK_SRV_DB_FLUSH_TIMER 10000

#define BT_SINK_SRV_DB_DEVICE_INFO "devinfo"
#define BT_SINK_SRV_DB_SCAN_INFO "scan"
#define BT_SINK_SRV_DB_SDAP_INFO "sdap"

typedef uint8_t(*bt_sink_srv_db_comparator_t)(const uint8_t *record, const void *key);

typedef struct {
    char *name_p;
    bool dirty;
    uint16_t size;
    uint16_t count;
    uint16_t used;
    bt_sink_srv_db_comparator_t comparator_function_p;
    uint8_t *buffer_p;
} bt_sink_srv_db_t;

bt_sink_srv_status_t bt_sink_srv_db_open(bt_sink_srv_db_t *db_p);

bt_sink_srv_status_t bt_sink_srv_db_flush(bt_sink_srv_db_t *db_p);

bt_sink_srv_status_t bt_sink_srv_db_find_record(bt_sink_srv_db_t *db_p, const void *key, uint8_t *record);

bt_sink_srv_status_t bt_sink_srv_db_add_record(bt_sink_srv_db_t *db_p, uint8_t *record, const void *key);

bt_sink_srv_status_t bt_sink_srv_db_delete_record(bt_sink_srv_db_t *db_p, const void *key);

bt_sink_srv_status_t bt_sink_srv_db_delete_all_records(bt_sink_srv_db_t *db_p);

bt_sink_srv_status_t bt_sink_srv_db_close(bt_sink_srv_db_t *db_p);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_DB_H__ */

