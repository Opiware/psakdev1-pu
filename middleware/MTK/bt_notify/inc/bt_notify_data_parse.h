/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Description:
 * ------------
 * The header file of 'bt_notify_data_parse.c'.
 *
 ****************************************************************************/



#ifndef __BT_NOTIFY_DATA_PARSE_H__
#define __BT_NOTIFY_DATA_PARSE_H__
#include "stdbool.h"
#include <stdint.h>
#include "bt_notify.h"

/*****************************************************************************
 * define
 *****************************************************************************/

#define BT_NOTIFY_NODE_LEVEL_1              1
#define BT_NOTIFY_NODE_LEVEL_2              2
#define BT_NOTIFY_NODE_LEVEL_3              3
#define BT_NOTIFY_NODE_LEVEL_4              4


#define BT_NOTIFY_TYPE_DATA                 1
#define BT_NOTIFY_TYPE_ATTR                 2
#define NOTIFY_READ_BUFFER_LEN              240

#define ENCODING_LENGTH 2

/*page releated*/
#define BT_NOTIFY_PAGE_MAX_NUM              3

/*****************************************************************************
 * Typedef
 *****************************************************************************/

/* notification category enum */
typedef enum {
    BT_NOTIFY_CATEGORY_NONE,                /* none category */
    BT_NOTIFY_CATEGORY_NOTI,                /* notification category */
    BT_NOTIFY_CATEGORY_CALL                 /* call category */
} bt_notify_category_t;
/* notification subtype enum */
typedef enum {
    BT_NOTIFY_SUBTYPE_TEXT,                 /* for category noti text subtype */
    BT_NOTIFY_SUBTYPE_SMS,                  /* for category noti sms subtype */
    BT_NOTIFY_SUBTYPE_MISSED_CALL,          /* for category call */
    BT_NOTIFY_SUBTYPE_NOTI_DELETE           /*for delete the remote notification*/
} bt_notify_subtype_t;
/* notification action enum */
typedef enum {
    BT_NOTIFY_ACTION_ADD,                   /* add action */
    BT_NOTIFY_ACTION_DELETE,                /* delete action */
    BT_NOTIFY_ACTION_DELETE_ALL,            /* delete all action */
    BT_NOTIFY_ACTION_UPDATE                 /* update action */
} bt_notify_opeate_t;

/* notification header struct */
typedef struct {
    bt_notify_category_t category;          /* notification category */
    bt_notify_subtype_t subtype;            /* notification subtype */
    bt_notify_opeate_t action;              /* notification action */
    uint32_t msg_id;                        /* notification msg id */
} bt_notify_header_t;

typedef enum {
    BT_NOTIFY_PARSE_NONE,
    BT_NOTIFY_PARSE_HEADER,
    BT_NOTIFY_PARSE_NOTI_BODY,
    BT_NOTIFY_PARSE_SMS_BODY,
    BT_NOTIFY_PARSE_CALL_BODY,
} bt_notify_parse_para_t;

typedef struct {
    bool is_waiting_parser_callback;
} bt_notify_data_msg_context_t;

typedef union {
    bt_notify_notification_t noti;
    bt_notify_sms_t sms;
    bt_notify_missed_call_t call;
} bt_notify_body_union_t;

typedef struct {
    uint8_t cntx_chnl;
    uint8_t recv_paser_buf[BT_NOTIFY_MIN_PARSER_BUF_SIZE];
    int32_t recv_paser_buf_len;
} bt_notify_paser_t;
typedef struct {
    uint8_t cntx_chnl;
    bt_notify_callback_data_t callback_struct;

} bt_notify_callback_item_t;

typedef void (*bt_parse_xml_callback)(bt_notify_parse_para_t para_flag, void *data, void *user_data, bool ret_val);

/*****************************************************************************
 * Function
 *****************************************************************************/

void bt_notify_deinit_data(void);
bt_notify_paser_t *bt_notify_get_parser_buffer(uint8_t cntx_chnl);
void bt_notify_data_handle_new_msg(int32_t cntx_chnl, uint8_t *paser_buf, bt_notify_header_t *header);
int32_t bt_notify_xml_parse(uint8_t *buffer, bt_notify_parse_para_t para_flag, bt_parse_xml_callback callback, void *data, void *user_data);
void bt_notify_data_init(void);



#endif/*__BT_NOTIFY_DATA_PARSE_H__*/

