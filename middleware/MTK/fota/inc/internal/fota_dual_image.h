/* Copyright Statement:
 *
 */

#ifndef __FOTA_DUAL_IMAGE_H__
#define __FOTA_DUAL_IMAGE_H__

#include "stdint.h"
#include "fota_internal.h"

#define FOTA_CONTROL_BLOCK_ADDR          (0x8000) // to be determined
#define FOTA_CONTROL_BLOCK_MAGIC         (0x4455414C) // "DUAL"
#define FOTA_IMAGE_A_MARK              (0xABCDDCBA)
#define FOTA_IMAGE_B_MARK              (~(FOTA_IMAGE_A_MARK))

typedef struct {
    uint32_t magic_num;
    uint32_t active_flag;
} fota_control_block_t;

typedef enum {
    FOTA_DUAL_IMAGE_A = 0,
    FOTA_DUAL_IMAGE_B
} fota_image_type_t;


typedef struct {
    uint8_t SHA512_hash_n9[64];
    uint8_t SHA512_hash_cm4[64];
} fota_hash_check_t;


extern fota_status_t fota_switch_active_image (void);

extern fota_status_t fota_query_active_image(fota_image_type_t *type);

extern fota_status_t fota_dual_image_init(void);

extern fota_status_t fota_dual_image_download(char* address);

#endif /*__FOTA_DUAL_IMAGE_H__ */

