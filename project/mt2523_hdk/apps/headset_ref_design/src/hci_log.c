/* Copyright Statement:
 *
 */


#include "hci_log.h"
#include <stdio.h>
#include <string.h>
#include "memory_attribute.h"
#include "atci.h"

#define HCI_MAGIC_HI    0xab
#define HCI_MAGIC_LO    0xcd

#define MEDIA_HEAD_MAGIC_HI  (0x80)
#define MEDIA_HEAD_MAGIC_LOW_V1  (0x60)
#define MEDIA_HEAD_MAGIC_LOW_V2  (0x62)
#define L2CAP_MEDIA_HEAD_LEN (16)       // L2CAP:4, MEDIA:12
#define L2CAP_MEDIA_TOTAL_LEN (24)      // HEAD:16, payload: frame_num 1, frame header: 5, payload len:2
#define HCI_CONTINUE_TAG (0x10)

#define CUSTOM_MED_MAGIC_HI (0xFE)
#define CUSTOM_MED_MAGIC_LOW (0x00)

static unsigned char g_a2dp_omit_buf[28];
static unsigned char* hci_log_a2dp_streaming_data_omit(int32_t buf_len, unsigned char* buf, uint32_t *out_len)
{
    bool a2dp_cond = (buf[8] == MEDIA_HEAD_MAGIC_HI) && (buf[9] == MEDIA_HEAD_MAGIC_LOW_V1 || buf[9] == MEDIA_HEAD_MAGIC_LOW_V2);
    bool mp3_cond = (buf[8] == CUSTOM_MED_MAGIC_HI) && (buf[9] == CUSTOM_MED_MAGIC_LOW);
    if (buf_len > 26 && (a2dp_cond || mp3_cond))
    {
        uint32_t l2cap_total_len = (buf[3]<<8) | buf[2];
        uint32_t media_payload_len = l2cap_total_len - L2CAP_MEDIA_HEAD_LEN;
        memcpy(g_a2dp_omit_buf, buf, 26);
        g_a2dp_omit_buf[2] = L2CAP_MEDIA_TOTAL_LEN;
        g_a2dp_omit_buf[3] = 0;
        g_a2dp_omit_buf[4] = L2CAP_MEDIA_TOTAL_LEN - 4;
        g_a2dp_omit_buf[5] = 0;
        g_a2dp_omit_buf[26] = media_payload_len >> 8;
        g_a2dp_omit_buf[27] = media_payload_len & 0xff;
        *out_len = 28;
        return g_a2dp_omit_buf;
    }
    else if (buf_len > 159 && (buf[1]&HCI_CONTINUE_TAG) == HCI_CONTINUE_TAG)
    {
        uint32_t media_payload_len = (buf[3]<<8) | buf[2];
        memcpy(g_a2dp_omit_buf, buf, 26);
        g_a2dp_omit_buf[2] = L2CAP_MEDIA_TOTAL_LEN;
        g_a2dp_omit_buf[3] = 0;
        g_a2dp_omit_buf[26] = media_payload_len >> 8;
        g_a2dp_omit_buf[27] = media_payload_len & 0xff;
        *out_len = 28;
        return g_a2dp_omit_buf;
    }
    else
    {
        *out_len = buf_len;
        return buf;
    }
}

static int32_t hci_log(unsigned char type, unsigned char* buf, int32_t length)
{
    __disable_irq();
    {
        atci_response_t output = {{0}};

        output.response_buf[0] = HCI_MAGIC_HI;
        output.response_buf[1] = HCI_MAGIC_LO;
        output.response_buf[2] = type;
        output.response_buf[3] = (uint8_t)((length & 0xff00)>>8);
        output.response_buf[4] = (uint8_t)(length & 0xff);

        memcpy((void *)(output.response_buf+5), (void *)buf, length);
        output.response_len = length+5;
        output.response_flag = ATCI_RESPONSE_FLAG_URC_FORMAT;

        atci_send_response(&output);
    }
    __enable_irq();
    
    return 1;
}

int32_t hci_log_cmd(unsigned char* buf, int32_t length)
{
    return hci_log(HCI_COMMAND, buf, length);
}

int32_t hci_log_event(unsigned char* buf, int32_t length)
{
    return hci_log(HCI_EVENT, buf, length);
}

int32_t hci_log_acl_out(unsigned char* buf, int32_t length)
{
    uint32_t out_len;
    unsigned char* omit_buf = hci_log_a2dp_streaming_data_omit(length, buf, &out_len);
    return hci_log(HCI_ACL_OUT, omit_buf, out_len);
}

int32_t hci_log_acl_in(unsigned char* buf, int32_t length)
{
    uint32_t out_len;
    unsigned char* omit_buf = hci_log_a2dp_streaming_data_omit(length, buf, &out_len);
    return hci_log(HCI_ACL_IN, omit_buf, out_len);
}

