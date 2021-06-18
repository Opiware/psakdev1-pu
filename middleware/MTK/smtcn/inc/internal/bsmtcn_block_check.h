/* Copyright Statement:
 *
 */
 
#ifndef BSMTCN_BLOCK_CHECK_H
#define BSMTCN_BLOCK_CHECK_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>


#pragma pack(1)
#if 0
 typedef struct  bsmtcn_payload_struct  
 {
	uint16_t total_length;
	uint8_t version;
    uint16_t crc16;
	struct  { 
	uint32_t reserved:8;
	uint32_t ssid_len:6;
	uint32_t password_len:8;
	uint32_t extend_data_len:10;
#if defined(__ICCARM__)
    } __packed mix_len;
#else
    } __attribute__((__packed__)) mix_len;
#endif

#if defined(__ICCARM__)
} __packed  bsmtcn_payload_struct_t;
#else
} __attribute__((__packed__)) bsmtcn_payload_struct_t;
#endif

#endif
 typedef struct  bsmtcn_payload_struct  
 {
	uint16_t total_length;
	uint8_t version;
    uint16_t crc16;
	struct  { 
	uint32_t reserved:8;
	uint32_t ssid_len:6;
	uint32_t password_len:8;
	uint32_t extend_data_len:10;

    }  mix_len;


} bsmtcn_payload_struct_t;

#pragma pack()


void bsmtcn_block_get_payload(uint16_t *packet_table);

void bsmtcn_block_unscramble(uint16_t *packet_table);

bool bsmtcn_block_crc_check(uint16_t *packet_table);

int32_t bsmtcn_packet_decoder(uint8_t *addr, uint16_t len, uint8_t from_ds_flag);

bool bsmtcn_payload_crc_check(uint8_t *payload, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* BSMTCN_BLOCK_CHECK_H */

