/* Copyright Statement:
 *
 */
 
#ifndef BSMTCN_ADAPTER_H
#define BSMTCN_ADAPTER_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>

#include "bsmtcn_misc.h"
#include "bsmtcn_main_sm.h"

#define MAX_NUM_STA 15
#define BLOCK_DATA_COUNT 3
#define STA_HASH_SIZE 256
#define STA_HASH(sta) (sta[5])
#define AES_BLK_SIZE 16
#define ENCRYPTION_KEY_LENGTH AES_BLK_SIZE
#define EAPP_DEFAULT_KEY "McdwCnwCdss2_18p"
#define BMAP_MAX_LEN 32
#define BLOCK_TIMEOUT 5000 /* ms */


struct bsmtcn_sta_info {
	struct bsmtcn_sta_info *next; /* next entry in sta list */
	struct bsmtcn_sta_info *hnext; /* next entry in hash table list */
	uint8_t id[ETH_ALEN + 1];
	bool used;
    uint8_t packet_count;
	uint16_t packet_table[3 + BLOCK_DATA_COUNT];
};


typedef unsigned char BITMAP_T[BMAP_MAX_LEN];   // (0xFF+1)/8 = 32

typedef struct _BSMTCN_ADAPTER_T {
	struct bsmtcn_main_state_machine bsmtcn_main_sm;
	int32_t  num_sta;
	struct bsmtcn_sta_info *sta_list; /* STA info list head */
	struct bsmtcn_sta_info *sta_hash[STA_HASH_SIZE];
	struct bsmtcn_sta_info bsmtcn_sta_info_table[MAX_NUM_STA + 1];
	uint8_t bsmtcn_payload[256 * BLOCK_DATA_COUNT];
	uint16_t block_count;
	uint16_t base_len;
	BITMAP_T bitmap;
	uint8_t key[ENCRYPTION_KEY_LENGTH];
	uint32_t time;

}BSMTCN_ADAPTER_T, *P_BSMTCN_ADAPTER_T;


BSMTCN_ADAPTER_T *bsmtcn_get_adapter(void);

int32_t bsmtcn_adapter_init(void);

void bsmtcn_adapter_deinit(void);

void bsmtcn_adapter_reset(void);

void bsmtcn_adapter_channel_reset(void);

void bsmtcn_adapter_set_key(uint8_t *key, uint8_t key_len);

#ifdef __cplusplus
}
#endif

#endif /* BSMTCN_ADAPTER_H */
