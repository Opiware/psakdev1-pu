/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Description:
 * ------------
 *
 *
 ****************************************************************************/


#ifndef __BT_NOTIFY_TEST_H__
#define __BT_NOTIFY_TEST_H__
#include "stdbool.h"
#include <stdint.h>

#define APP_RECEIVE_BUF_SIZE  2*1024
typedef struct {
    int32_t write_len;
    int32_t write_total_len;
    char write_buffer[APP_RECEIVE_BUF_SIZE];
    bool is_write_done;
    int32_t read_len;
    int32_t read_total_len;
    uint8_t read_buffer[APP_RECEIVE_BUF_SIZE];
} bt_notify_test_cntx_t;

typedef struct {
    uint32_t event_id;
    void *data_ptr;
} app_queue_struct_t;

void bt_notify_test_task_init(void);

#endif/*__BT_NOTIFY_TEST_H__*/

