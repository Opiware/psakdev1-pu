/* Copyright Statement:
 *
 */

#include "bt_sink_srv_db.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_custom_db.h"

static bt_sink_srv_status_t bt_sink_srv_db_find_record_internal(bt_sink_srv_db_t *db_p, const void *key, uint32_t *index)
{
    uint32_t i;

    if (NULL != index) {
        *index = 0;
    }

    for (i = 0; i < db_p->used; i++) {
        if (db_p->comparator_function_p(&db_p->buffer_p[db_p->size * i], key)) {
            if (NULL != index) {
                *index = i;
            }
            return BT_SINK_SRV_STATUS_SUCCESS;
        }
    }
    return BT_SINK_SRV_STATUS_DB_NOT_FOUND;
}

static void bt_sink_srv_db_flush_timeout_handler(void *parameter)
{
    if (parameter) {
        bt_sink_srv_db_flush((bt_sink_srv_db_t *)parameter);
    }
}

static void bt_sink_srv_db_update_internal(bt_sink_srv_db_t *db_p)
{
    if (!db_p->dirty) {
        db_p->dirty = true;
        bt_sink_srv_timer_start((uint32_t)db_p, BT_SINK_SRV_DB_FLUSH_TIMER, bt_sink_srv_db_flush_timeout_handler, (void *)db_p);
    }
}

bt_sink_srv_status_t bt_sink_srv_db_open(bt_sink_srv_db_t *db_p)
{
    if (NULL != db_p && NULL != db_p->name_p && db_p->count > 0 && NULL != db_p->buffer_p && db_p->size > 0) {
        bt_sink_srv_report("[Sink][DB]bt_sink_srv_db_open(0x%x) : name=%s, size=%u, count=%u", db_p, db_p->name_p, db_p->size, db_p->count);
        bt_sink_srv_db_custom_read(db_p);
    } else {
        return BT_SINK_SRV_STATUS_INVALID_PARAM;
    }

    return BT_SINK_SRV_STATUS_SUCCESS;
}

bt_sink_srv_status_t bt_sink_srv_db_flush(bt_sink_srv_db_t *db_p)
{
    if (db_p->dirty) {
        bt_sink_srv_db_custom_write(db_p);
        bt_sink_srv_timer_stop((uint32_t)db_p);
        db_p->dirty = false;
    }
    return BT_SINK_SRV_STATUS_SUCCESS;
}

bt_sink_srv_status_t bt_sink_srv_db_find_record(bt_sink_srv_db_t *db_p, const void *key, uint8_t *record)
{
    uint32_t index;
    bt_sink_srv_status_t result;

    result = bt_sink_srv_db_find_record_internal(db_p, key, &index);
    if (BT_SINK_SRV_STATUS_SUCCESS == result && NULL != record) {
        bt_sink_srv_memcpy(record, &db_p->buffer_p[db_p->size * index], db_p->size);
    }

    bt_sink_srv_report("[Sink][DB] bt_sink_srv_db_find_record, result:%d, index:%d", result, index);

    return result;
}

bt_sink_srv_status_t bt_sink_srv_db_add_record(bt_sink_srv_db_t *db_p, uint8_t *record, const void *key)
{
    uint32_t index;
    bt_sink_srv_status_t result;

    result = bt_sink_srv_db_find_record_internal(db_p, key, &index);

    if (BT_SINK_SRV_STATUS_DB_NOT_FOUND == result) {
        if (db_p->used == db_p->count) {
            index = db_p->count - 1;
            bt_sink_srv_memcpy(db_p->buffer_p, &db_p->buffer_p[db_p->size], (db_p->count - 1)*db_p->size);
        } else {
            index = db_p->used;
            db_p->used++;
        }
    }
    bt_sink_srv_memcpy(&db_p->buffer_p[db_p->size * index], record, db_p->size);

    if (BT_SINK_SRV_CUSTOM_DB_MAX != bt_sink_srv_db_custom_is_special_type(db_p)) {
        bt_sink_srv_db_update_internal(db_p);
    }

    bt_sink_srv_report("[Sink][DB] bt_sink_srv_db_add_record, 0x%x, index:%d", db_p, index);

    return BT_SINK_SRV_STATUS_SUCCESS;
}

bt_sink_srv_status_t bt_sink_srv_db_delete_record(bt_sink_srv_db_t *db_p, const void *key)
{
    uint32_t index;
    bt_sink_srv_status_t result;

    result = bt_sink_srv_db_find_record_internal(db_p, key, &index);
    if (BT_SINK_SRV_STATUS_SUCCESS == result) {
        db_p->used--;
        if (index < db_p->used) {
            bt_sink_srv_memcpy(&db_p->buffer_p[db_p->size * index],
                               &db_p->buffer_p[db_p->size * (index + 1)],
                               (db_p->size * (db_p->used - index)));
            bt_sink_srv_memset(&db_p->buffer_p[db_p->size * db_p->used], 0, (db_p->size));
        } else {
            bt_sink_srv_memset(&db_p->buffer_p[db_p->size * index], 0, (db_p->size));
        }

        if (BT_SINK_SRV_CUSTOM_DB_MAX != bt_sink_srv_db_custom_is_special_type(db_p)) {
            bt_sink_srv_db_update_internal(db_p);
        }
        result = BT_SINK_SRV_STATUS_SUCCESS;
    }

    bt_sink_srv_report("[Sink][DB] bt_sink_srv_db_delete_record, 0x%x, index:%d", db_p, index);

    return result;

}

bt_sink_srv_status_t bt_sink_srv_db_delete_all_records(bt_sink_srv_db_t *db_p)
{
    bt_sink_srv_status_t result = BT_SINK_SRV_STATUS_FAIL;

    if (NULL != db_p) {
        bt_sink_srv_memset(db_p->buffer_p, 0, (db_p->size * db_p->count));
        db_p->used = 0;
        db_p->dirty = true;

        if (BT_SINK_SRV_CUSTOM_DB_MAX != bt_sink_srv_db_custom_is_special_type(db_p)) {
            result = bt_sink_srv_db_flush(db_p);
        }
    }
    bt_sink_srv_report("[Sink][DB] bt_sink_srv_db_delete_all_records, 0x%x, result:%d", db_p, result);
    return result;

}

bt_sink_srv_status_t bt_sink_srv_db_close(bt_sink_srv_db_t *db_p)
{
    bt_sink_srv_status_t status;
    bt_sink_srv_report("[Sink][DB] bt_sink_srv_db_close(0x%x)", db_p);
    status = BT_SINK_SRV_STATUS_FAIL;

    if (bt_sink_srv_db_flush(db_p) == BT_SINK_SRV_STATUS_SUCCESS) {
        status = BT_SINK_SRV_STATUS_SUCCESS;
    }
    db_p->used = 0;
    return status;
}

