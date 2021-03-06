/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_AM_MED_MGR_H__
#define __BT_SINK_SRV_AM_MED_MGR_H__

#include "stdint.h"
#include "bt_type.h"
#include "bt_codec.h"
#include "bt_a2dp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define __BT_SINK_SRV_AM_MED_LIST_SUPPORT__

#define __BT_SINK_SRV_AM_MED_LIST_DEBUG__

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

#define BT_SINK_SRV_AM_MED_MGR_FLAG_READY               (0x0001)
#define BT_SINK_SRV_AM_MED_MGR_FLAG_CLEAR               (0x0002)
#define BT_SINK_SRV_AM_MED_MGR_FLAG_WRITING             (0x0004)
#define BT_SINK_SRV_AM_MED_MGR_FLAG_ODD_BTYE            (1 << 3)

#define BT_SINK_SRV_AM_MED_MGR_MAX_COUNT                (25)

#define BT_SINK_SRV_AM_MED_MGR_MAX_SIZE                 (12 * 1024)

BT_PACKED(
typedef struct _list_t {
    struct _list_t *next;
})list_t;

typedef enum {
    LIST_FRONT = 0,
    LIST_BACK,

    LIST_TOTAL
} list_dir;

BT_PACKED(
typedef struct {
    list_t node;
    uint16_t packet_length;
    uint16_t offset;
    uint8_t ref_count;
    uint32_t pad;
}) bt_hci_packet_t;

typedef struct {
    uint8_t *data;
    uint16_t length;
    uint16_t offset;
} bt_sink_srv_am_med_t;

typedef struct {
    list_t med_head;
    uint32_t med_len;
    bt_sink_srv_am_med_t reading;
    uint32_t node_cnt;
    list_t *read;
    list_t *write;
    uint32_t flag;
    uint8_t odd_byte;
    uint8_t *sill_ptr;
    uint16_t sill_len;
    uint16_t sill_offset;
} bt_sink_srv_am_med_mgr_context_t;


#define BT_SINK_SRV_SET_FLAG(FLAG, MASK) do { \
    (FLAG) |= (MASK); \
} while(0);

#define BT_SINK_SRV_REMOVE_FLAG(FLAG, MASK) do { \
    (FLAG) &= ~(MASK); \
} while(0);

void list_insert_node(list_t *head, list_t *node, list_dir dir);

void list_insert_back(list_t *node);

list_t *list_remove_node(list_t *head, list_dir dir);

list_t *list_get_node(list_t *head, list_dir dir);

void list_clear(list_t *head);

void bt_sink_srv_am_med_mgr_init(void);

int32_t bt_sink_srv_am_med_mgr_push_data(void *ptr);

int32_t bt_sink_srv_am_med_mgr_read_data(volatile uint16_t *buf, uint32_t len /* the number of buf byte */);

int32_t bt_sink_srv_am_med_mgr_get_data_count(void);

int32_t bt_sink_srv_am_med_mgr_clear_node(void);

bool bt_sink_srv_am_med_mgr_node_is_exist(void *ptr);

void BT_A2DP_MAKE_SBC_CODEC(bt_a2dp_codec_capability_t *codec,
                            bt_a2dp_role_t role,
                            uint8_t min_bit_pool, uint8_t max_bit_pool,
                            uint8_t block_length, uint8_t subband_num,
                            uint8_t alloc_method, uint8_t sample_rate,
                            uint8_t channel_mode);

void BT_A2DP_MAKE_AAC_CODEC(bt_a2dp_codec_capability_t *codec,
                            bt_a2dp_role_t role, bool vbr, uint8_t object_type,
                            uint8_t channels, uint16_t sample_rate,
                            uint32_t bit_rate);

void BT_A2DP_CONVERT_SBC_CODEC(bt_codec_capability_t *dst_codec,
                               bt_a2dp_codec_capability_t *src_codec);

void BT_A2DP_CONVERT_AAC_CODEC(bt_codec_capability_t *dst_codec,
                               bt_a2dp_codec_capability_t *src_codec);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_AM_MED_MGR_H__ */
