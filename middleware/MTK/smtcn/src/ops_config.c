/* Copyright Statement:
 *
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
     
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "timers.h"
#include "type_def.h"
#include "hal_aes.h"
#include "smt_conn.h"
#include "smt_api.h"
     
#include "wifi_api.h"


extern smtcn_proto_ops elian_proto_ops;
extern smtcn_proto_ops bsmtcn_proto_ops;


#if defined(MTK_SMTCN_V4_ENABLE) && defined(MTK_SMTCN_V5_ENABLE)


static int32_t cur_protocol = USE_BOTH ;

static bool need_recover_from_timeout = TRUE;

void smt_ops_set_protocol(int32_t protocol)
{
    cur_protocol = protocol;

    need_recover_from_timeout = (protocol == USE_BOTH ? true:false);
}

static void smt_env_report(e_multi_protocol_evt_type type)
{
    switch(type)
    {
        case EVT_BC_SYNC:
            cur_protocol = USE_BC_PROTOCOL;
            break;
        case EVT_MC_SYNC:
            cur_protocol = USE_MC_PROTOCOL;
            break;
        case EVT_SYNC_TIME_OUT:
            if(need_recover_from_timeout)
                cur_protocol = USE_BOTH;
            break;
        case EVT_FINISHED:
            cur_protocol = USE_BOTH;
            break;
        default:
            break;
    }
}

static int32_t multi_ops_init(const uint8_t *key, const uint8_t key_length)
{
    elian_proto_ops.init(key,key_length);
    bsmtcn_proto_ops.init(key,key_length);
    return 0;
}


static void multi_ops_cleanup(void)
{
    elian_proto_ops.cleanup();
    bsmtcn_proto_ops.cleanup();
}

static int32_t multi_ops_reset(void)
{
    elian_proto_ops.switch_channel_rst();
    bsmtcn_proto_ops.switch_channel_rst();
    return 0;
}

static int32_t multi_ops_input(char *p, int32_t len, uint8_t channel)
{
    switch(cur_protocol)
    {
        case USE_BOTH:
        {
            elian_proto_ops.rx_handler(p,len,channel);

            if(cur_protocol!= USE_BOTH)
                break;
            
            bsmtcn_proto_ops.rx_handler(p,len,channel);
            break;
        }
        
        case USE_MC_PROTOCOL:
            elian_proto_ops.rx_handler(p,len,channel);
            break;
        case USE_BC_PROTOCOL:
            bsmtcn_proto_ops.rx_handler(p,len,channel);
            break;
        default:
            
            break;
    }
    return 0;
}


static smtcn_proto_ops multi_proto_ops = {
    .init               =   multi_ops_init,
    .cleanup            =   multi_ops_cleanup,
    .switch_channel_rst =   multi_ops_reset,
    .rx_handler         =   multi_ops_input,  
};

#endif

#ifdef MTK_WIFI_ROM_ENABLE
extern void RT_AES_Decrypt (
    uint8_t *CipherBlock,
    uint32_t CipherBlockSize,
    uint8_t *Key,
    uint32_t KeyLength,
    uint8_t *PlainBlock,
    uint32_t *PlainBlockSize);
#endif

void smtcn_aes_decrypt(uint8_t *cipher_blk, uint32_t cipher_blk_size,
                              uint8_t *key, uint8_t key_len,
                              uint8_t *plain_blk, uint32_t *plain_blk_size)
{
 
#ifdef MTK_WIFI_ROM_ENABLE
    RT_AES_Decrypt(cipher_blk,cipher_blk_size,key,key_len,plain_blk,plain_blk_size);
#else
    hal_aes_buffer_t plain_buf, cipher_buf, key_buf;
    plain_buf.buffer = plain_blk;
    plain_buf.length = *plain_blk_size;
    cipher_buf.buffer = cipher_blk;
    cipher_buf.length = cipher_blk_size;
    key_buf.buffer = key;
    key_buf.length = key_len;
    hal_aes_ecb_decrypt(&plain_buf, &cipher_buf, &key_buf); 
#endif
}


smtcn_proto_ops * smt_get_proto_ops()
{
    #if defined(MTK_SMTCN_V4_ENABLE) && defined(MTK_SMTCN_V5_ENABLE)
        elian_register_evt_cb(smt_env_report);
        bcsmtcn_register_evt_cb(smt_env_report);
        return &multi_proto_ops;
    #elif defined(MTK_SMTCN_V4_ENABLE)
        return &elian_proto_ops;
    #elif defined(MTK_SMTCN_V5_ENABLE)
        return &bsmtcn_proto_ops;
    #else
        return NULL;
    #endif  
}




