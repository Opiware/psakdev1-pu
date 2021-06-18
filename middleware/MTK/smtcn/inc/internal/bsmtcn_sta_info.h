/* Copyright Statement:
 *
 */
 
#ifndef BSMTCN_STA_INFO_H
#define BSMTCN_STA_INFO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct bsmtcn_sta_info * bsmtcn_get_sta(void *adapter, const uint8_t *id);

void bsmtcn_sta_hash_add(void *adapter, struct bsmtcn_sta_info *sta);

struct bsmtcn_sta_info * bsmtcn_sta_add(void *adapter, const uint8_t *id);

void bsmtcn_sta_hash_del(void *adapter, struct bsmtcn_sta_info *sta);

void bsmtcn_sta_list_del(void *adapter, struct bsmtcn_sta_info *sta);

void bsmtcn_free_sta(void *adapter, struct bsmtcn_sta_info *sta);

void bsmtcn_flush_sta(void *adapter);

void bsmtcn_flush_other_sta(void *adapter, struct bsmtcn_sta_info *sta);

#ifdef __cplusplus
}
#endif

#endif /* BSMTCN_STA_INFO_H */
