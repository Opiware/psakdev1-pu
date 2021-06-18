/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_MEDIA_MGR_H__
#define __BT_SINK_SRV_MEDIA_MGR_H__

#include "stdint.h"

#if _MSC_VER >= 1500
#define BT_PACKED(...) __pragma(pack(push, 1)) __VA_ARGS__ __pragma(pack(pop))
#elif defined(__GNUC__) || defined(__ARMCC_VERSION)
#define BT_PACKED(...) __VA_ARGS__ __attribute__((__packed__))
#define BT_ALIGNMENT4(...) __VA_ARGS__ __attribute__((aligned(4)))
#elif defined(__ICCARM__)
#define BT_PACKED(...) __packed __VA_ARGS__
#else
#error "Unsupported Platform"
#endif

#define __BT_SINK_SRV_AM_MED_LIST_SUPPORT__

#define BT_SINK_SRV_MEDIA_MGR_ITEM_COUNT                   (64)
#define BT_SINK_SRV_MEDIA_MGR_HOLD_SIZE                    (14 * 1024)


#define BT_SINK_SRV_MEDIA_MGR_ITEM_FLAG_ACCESS             (1 << 0)    /**< Decoder can access it */
#define BT_SINK_SRV_MEDIA_MGR_ITEM_FLAG_FREE               (1 << 1)    /**< Garbage free */


#define DATA_BLOCK_FLAG_RELEASE                            (1 << 0)    /**< Need release */
#define DATA_BLOCK_ODD_BYTE                                (0x100)

#define BT_SINK_SRV_MEDIA_MGR_FLAG_READY                   (1 << 0)    /**< Media mgr ready */

#define BT_SINK_SRV_MEDIA_PKT_HEADER_LEN                   (12)
#define BT_SINK_SRV_MEDIA_SBC_SYNC_WORD                    (0x3453)
#define BT_SINK_SRV_MEDIA_SBC_SYNC_WORD_LEN                (4)

#define BT_SINK_SRV_AAC_ADTS_LENGTH                        (7)


typedef struct {
    uint32_t ptr;
    uint16_t size;
    uint8_t flag;
} data_block_struct_t;

typedef struct {
    uint16_t skip;
    uint16_t size;
    uint16_t db_count;
    data_block_struct_t *db;
} copy_data_struct_t;

typedef struct {
    uint32_t item[BT_SINK_SRV_MEDIA_MGR_ITEM_COUNT];
    uint8_t iflag[BT_SINK_SRV_MEDIA_MGR_ITEM_COUNT];
    uint32_t size;
    uint16_t item_count;
    uint16_t bt_ac_index;
    uint16_t garbage_ac_index;
    uint16_t decoder_ac_index;
    uint16_t skip;
    uint16_t odd_byte;
    uint32_t last_check_item;
    uint32_t flag;
    uint32_t codec_type;
    bt_a2dp_codec_capability_t *codec;
} bt_sink_srv_media_mgr_context_t;

BT_PACKED(
typedef struct _list_t {
    struct _list_t *next;
})list_t;

BT_PACKED(
typedef struct {
    list_t node;
    uint16_t packet_length;
    uint16_t offset;
    uint8_t ref_count;
    uint32_t pad;
}) bt_hci_packet_t;


#define BT_SINK_SRV_MEDIA_MGR_ERR_FAIL_6TH                          (-6)
#define BT_SINK_SRV_MEDIA_MGR_ERR_FAIL_5TH                          (-5)
#define BT_SINK_SRV_MEDIA_MGR_ERR_FAIL_4TH                          (-4)
#define BT_SINK_SRV_MEDIA_MGR_ERR_FAIL_3RD                          (-3)
#define BT_SINK_SRV_MEDIA_MGR_ERR_FAIL_2ND                          (-2)
#define BT_SINK_SRV_MEDIA_MGR_ERR_FAIL_1ST                          (-1)
#define BT_SINK_SRV_MEDIA_MGR_ERR_SUCCESS                           (0)
#define BT_SINK_SRV_MEDIA_MGR_ERR_SUCCESS_1ST                       (1)
#define BT_SINK_SRV_MEDIA_MGR_ERR_SUCCESS_2ND                       (2)
#define BT_SINK_SRV_MEDIA_MGR_ERR_SUCCESS_3RD                       (3)
#define BT_SINK_SRV_MEDIA_MGR_ERR_SUCCESS_4TH                       (4)
#define BT_SINK_SRV_MEDIA_MGR_ERR_SUCCESS_5TH                       (5)
#define BT_SINK_SRV_MEDIA_MGR_ERR_SUCCESS_6TH                       (6)

#ifdef __cplusplus
extern "C" {
#endif

void bt_sink_srv_media_mgr_init(void);

bt_sink_srv_media_mgr_context_t *bt_sink_srv_media_mgr_get_context(void);

void bt_sink_srv_media_mgr_set_codec_type(uint32_t type, bt_a2dp_codec_capability_t *codec);

int32_t bt_sink_srv_media_mgr_push_item(uint32_t item);

void bt_sink_srv_media_mgr_garbage_free(void);

int32_t bt_sink_srv_media_mgr_read_data(volatile uint16_t *buf, uint32_t length /* word length */);

void bt_sink_srv_media_mgr_clear(void);

uint32_t bt_sink_srv_media_mgr_get_last_item(void);

uint32_t bt_sink_srv_media_mgr_get_first_item(void);

uint32_t bt_sink_srv_media_mgr_pop_first_item(void);

int32_t bt_sink_srv_media_mgr_get_data_count(void);

#ifdef __cplusplus
}
#endif

#endif

