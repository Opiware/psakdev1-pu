/* Copyright Statement:
 *
 */

#ifndef __FOTA_BT_NOTI_SRV__
#define __FOTA_BT_NOTI_SRV__

#include <stdint.h>
#include "hal_flash.h"
#include "bt_spp.h"

/*****************************************************************************
 * define
 *****************************************************************************/

/* for extend command sender and receiver */
#define FOTA_EXTCMD_UPDATE_BIN_SENDER           "fota_fbin"
#define FOTA_EXTCMD_UPDATE_BIN_RECEIVER         "fota_fbin"
#define FOTA_EXTCMD_GET_VERSION_SENDER          "fota_bt_ver"
#define FOTA_EXTCMD_GET_VERSION_RECEIVER        "fota_bt_ver"
#define FOTA_EXTCMD_CUSTOMER_COMMAND_SENDER     "fota_cust_cmd"
#define FOTA_EXTCMD_CUSTOMER_COMMAND_RECEIVER   "fota_cust_cmd"

#define FOTA_EXTCMD_GNSS_UPDATE_SENDER           "gnss_update"
#define FOTA_EXTCMD_GNSS_UPDATE_RECEIVER         "gnss_update"


/* fota receive firmware data type */
#define FOTA_FILE_DATA_BEGIN                    0
#define FOTA_FILE_DATA_PACK                     1
#define FOTA_FILE_DATA_END                      2

/* fota error code */
#define FOTA_PACK_END_CORRECT                   2
#define FOTA_PACK_END_WRONG                    -4
#define FOTA_UPDATE_SUCCESS                     3
#define FOTA_UPDATE_COMMON_ERROR               -1
#define FOTA_WRITE_FLASH_FAIL                  -2
#define FOTA_UBIN_OVERSIZE                     -3
/*****************************************************************************
 * Typedef
 *****************************************************************************/
/**
 *  memory info for store bin file on flash */
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
} fota_mem_info_t;

typedef enum {
    FOTA_UPDATE_NONE,
    FOTA_UPDATE_FBIN,
    FOTA_UPDATE_GNSS,
    FOTA_UPDATE_END
} fota_update_enum_t;

/*****************************************************************************
 * Function
 *****************************************************************************/

/**
 * this function is the main function of fota task.
 * arg       is the argument for create fota task.
 * return
 * note */

extern void fota_task(void *arg);
extern void fota_download_manager_init(void);
extern bool fota_is_power_on_after_update();


#endif //__FOTA_BT_NOTI_SRV__
