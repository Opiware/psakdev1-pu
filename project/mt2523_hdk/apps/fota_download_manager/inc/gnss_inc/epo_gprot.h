/* Copyright Statement:
 *
 */

#ifndef __EPO_BT_NOTI_SRV__
#define __EPO_BT_NOTI_SRV__

/* add include files here */
#include <stdint.h>
#include <stdbool.h>
#include "hal_flash.h"
#ifdef GNSS_SUPPORT_EPO_DOWNLOAD_BY_BT
#include "bt_notify.h"
#endif

#define EPO_EXTEND_CMD                         "EXCD"

/* for extend command sender and receiver */
#define EPO_EXTCMD_UPDATE_DATA_SENDER           "epo_update_data"
#define EPO_EXTCMD_UPDATE_DATA_RECEIVER         "epo_update_data"
#define EPO_EXTCMD_UPDATE_MD5_SENDER            "epo_update_md5"
#define EPO_EXTCMD_UPDATE_MD5_RECEIVER          "epo_update_md5"



/* fota receive firmware data type */
#define EPO_FILE_DATA_BEGIN                    0
#define EPO_FILE_DATA_PACK                     1
#define EPO_FILE_DATA_END                      2

/* fota error code */
#define EPO_PACK_END_CORRECT                   1
#define EPO_PACK_END_WRONG                     2
#define EPO_WRITE_FLASH_FAIL                   3
#define EPO_UBIN_OVERSIZE                      4
#define EPO_TRANSFER_DATA_FAIL                 5

/* typedef part */
typedef struct {
    uint32_t start_address;
    uint32_t end_address;
    uint32_t write_ptr;
    uint32_t reserved_size;
    uint32_t total_received;
    uint32_t block_count;
    uint32_t block_size;
    uint32_t ubin_pack_count;
    hal_flash_block_t block_type;
} epo_mem_info_t;

#ifdef GNSS_SUPPORT_EPO_DOWNLOAD_BY_BT
/* paired device bt address*/
extern bt_address_t g_epo_bt_addr;
#endif

typedef enum epo_update_notify_type {
    EPO_UPDATE_NOTIFY_TYPE_SUCCESS,
    EPO_UPDATE_NOTIFY_TYPE_FAIL
} epo_update_notify_type_t;

/* reply version info and other info to remote end */
extern void epo_init();

extern void epo_msg_hdlr(void *data);

extern bool epo_need_update();

extern void epo_update_notify(epo_update_notify_type_t type, void *param);


#endif //__FOTA_BT_NOTI_SRV__
