/* Copyright Statement:
 *
 */

#ifndef _KAL_DATA_TYPES_H
#define _KAL_DATA_TYPES_H

/*******************************************************************************
 * Type Definitions
 *******************************************************************************/

#define LOCAL_PARA_HDR \
    uint8_t	    ref_count; \
    uint8_t     lp_reserved; \
    uint16_t    msg_len;
/*  common local_para header */

/*USB driver*/
typedef struct {
    LOCAL_PARA_HDR
    void        *pData; /* Pointer to data buffer */
    int32_t     nBuffLen; /* Length of data buffer */
    int32_t     nBytesRecv; /* Number of bytes received */
} usb_ms_rec_done_conf_struct;

#endif  /* _KAL_GENERAL_TYPES_H */
