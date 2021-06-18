/* Copyright Statement:
 *
 */

#ifndef _FOTA_H_
#define _FOTA_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FOTA_HEADER_MAGIC                   0x004D4D4D
typedef struct {
    int32_t m_magic_ver;
    int32_t m_fota_triggered;
} fota_trigger_info_t;

#define BL_FOTA_BIN_NUMBER_MAX                     1

/* this structure contains 1. update information for DM, 2. marker for power loss recovery */
typedef struct {
    /* version of structure */
    uint32_t m_ver;
    /* update information for DM*/
    uint32_t m_error_code;
    /* the behavior of bootloader for this error */
    uint32_t m_behavior;    /* 0 : reboot, 1 : hang */
    /* check if DM has read */
    uint32_t m_is_read;     /* 0 : read, 1 : not read */
    /* marker for power loss recovery , 32 is FOTA_MARKER_REGION_SIZE*/
    char  m_marker[32];
    /* reserved & make the structure 64 bytes */
    uint32_t reserved[4];

} bl_fota_update_info_t;

typedef struct {
    uint32_t m_bin_offset;       /*bin offset from FOTA Pkg Head*/
    uint32_t m_bin_start_addr;   /*bin start addr in ROM*/
    uint32_t m_bin_length;       /*bin length*/
    uint32_t m_partition_length;
    uint32_t m_sig_offset;       /*sig offset from FOTA Pkg Head*/
    uint32_t m_sig_length;       /*sig length*/
    uint32_t m_is_compressed;
    uint8_t m_bin_reserved[4];
} bl_fota_bin_info_t;

typedef struct {
    uint32_t m_magic_ver;
    uint32_t m_bin_num;
    bl_fota_bin_info_t m_bin_info[BL_FOTA_BIN_NUMBER_MAX];
} bl_fota_header_t;

void bl_fota_process(void);

#define BL_FOTA_HEADER_MAGIC                   0x004D4D4D  /* "MMM" */
#define BL_FOTA_HEADER_MAGIC_END_MARK          0x45454545  /* "EEEE" */
#define BL_FOTA_HEADER_GET_MAGIC(magic_ver)    ((magic_ver)&0x00FFFFFF)
#define BL_FOTA_HEADER_GET_VER(magic_ver)      ((magic_ver)>>24)
#define BL_FOTA_SIGNATURE_SIZE                 (20) /* sha1 */

#define BL_FOTA_PAGE_SIZE                      (512)
#define BL_FOTA_UPDATE_INFO_RESERVE_SIZE       (512)      /*512byts ( FOTA_Update_Info size = 4*4 + 1*32 + 4*4 = 64 Bytes ) */

#define BL_FOTA_UPDATE_INFO_VERSION            (1)
#define BL_FOTA_MARKER                         (0x544e5546)
#define BL_FOTA_MARKER_REGION_SIZE             (32)

typedef enum {
    BL_FOTA_ERROR_NONE = 0,
    BL_FOTA_ERROR_LOADING_HEADER,
    BL_FOTA_ERROR_HEADER_FORMAT,
    BL_FOTA_ERROR_LOADING_BODY,
    BL_FOTA_ERROR_WRITE_TO_PARTITON,
    BL_FOTA_ERROR_LOADING_CHECKSUM,
    BL_FOTA_ERROR_CHECKSUM_VERIFY,
    BL_FOTA_ERROR_LOADING_MARKER,
    BL_FOTA_ERROR_ERASE_MARKER,
    BL_FOTA_ERROR_FS_OP
} bl_fota_status_t;

#ifdef __cplusplus
}
#endif

#endif /* _BL_FOTA_H_ */
