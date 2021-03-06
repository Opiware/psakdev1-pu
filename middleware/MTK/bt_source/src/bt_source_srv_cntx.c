/* Copyright Statement:
 *
 */

#include "bt_source_srv_utils.h"
#include "bt_source_srv_cntx.h"
#include "bt_source_srv_avrcp.h"
#include "bt_source_srv_a2dp.h"


static bt_source_srv_context_t g_bt_source_srv_cntx;

//extern SourceProfileA2dp source_a2dp;

void bt_source_srv_cntx_init(void)
{
    int32_t i = 0;

    //bt_source_srv_report("[source][a2dp]cntx-init \r\n");

    bt_source_srv_memset(&g_bt_source_srv_cntx, 0x00, sizeof(bt_source_srv_context_t));

    for (i = 0; i < BT_SOURCE_SRV_MAX_DEVICE_NUMBER; ++i) {
        bt_source_srv_memset((void *)(&(g_bt_source_srv_cntx.source_dev[i].dev_addr)), 0x00, sizeof(bt_bd_addr_t));
        bt_source_srv_memset((void *)(&(g_bt_source_srv_cntx.source_dev[i].a2dp)), 0x00, sizeof(SourceProfileA2dp));
        bt_source_srv_memset((void *)(&(g_bt_source_srv_cntx.source_dev[i].a2dp.codec)), 0x00, sizeof(bt_a2dp_codec_capability_t));
        g_bt_source_srv_cntx.source_dev[i].conn_bit = 0x00;
        g_bt_source_srv_cntx.source_dev[i].a2dp_hd = BT_SOURCE_SRV_INVALID_HD;
        g_bt_source_srv_cntx.source_dev[i].a2dp_role = BT_A2DP_INVALID_ROLE;
        g_bt_source_srv_cntx.source_dev[i].avrcp_hd = BT_SOURCE_SRV_INVALID_HD;
        g_bt_source_srv_cntx.source_dev[i].avrcp_role = BT_AVRCP_ROLE_UNDEF;
        g_bt_source_srv_cntx.source_dev[i].avrcp_state = BT_SOURCE_SRV_AVRCP_DISCONNECTED;
        g_bt_source_srv_cntx.source_dev[i].avrcp_play_status = BT_AVRCP_EVENT_MEDIA_PLAY_STOPPED;
        g_bt_source_srv_cntx.source_dev[i].a2dp.profile.med_handle = NULL;
    }
    
    bt_source_srv_report("[source][cntx]init-\r\n");
}


bt_source_srv_context_t *bt_source_srv_get_context(void)
{
    return &g_bt_source_srv_cntx;
}


bt_source_srv_device_t *bt_source_srv_get_device(bt_source_srv_device_type_t type, const void *param)
{
    uint32_t i = 0;
    uint32_t *p_hd = NULL;
    bt_source_srv_device_t *dev = NULL;
    bt_source_srv_context_t *cntx = NULL;
    bt_bd_addr_t *dev_addr = NULL;

    //bt_source_srv_report("[source][a2dp]get-device,type:%d \r\n", type);
    cntx = bt_source_srv_get_context();
    switch (type) {
        case BT_SOURCE_SRV_DEVICE_A2DP: {
            p_hd = (uint32_t *)param;

            for (i = 0; i < BT_SOURCE_SRV_MAX_DEVICE_NUMBER; ++i) {
                if (cntx->source_dev[i].a2dp_hd != BT_SOURCE_SRV_INVALID_HD
                        && cntx->source_dev[i].a2dp_hd == *p_hd) {
                    dev = &(cntx->source_dev[i]);
                    break;
                }
            }
            break;
        }

        case BT_SOURCE_SRV_DEVICE_AVRCP: {
            p_hd = (uint32_t *)param;

            for (i = 0; i < BT_SOURCE_SRV_MAX_DEVICE_NUMBER; ++i) {
                if (cntx->source_dev[i].avrcp_hd != BT_SOURCE_SRV_INVALID_HD
                        && cntx->source_dev[i].avrcp_hd == *p_hd) {
                    dev = &(cntx->source_dev[i]);
                    break;
                }
            }
            break;
        }

        case BT_SOURCE_SRV_DEVICE_ADDR: {
            dev_addr = (bt_bd_addr_t *)param;

            for (i = 0; i < BT_SOURCE_SRV_MAX_DEVICE_NUMBER; ++i) {
                if ((cntx->source_dev[i].a2dp_hd != BT_SOURCE_SRV_INVALID_HD ||
                        cntx->source_dev[i].avrcp_hd != BT_SOURCE_SRV_INVALID_HD) &&
                        (bt_source_srv_memcmp(dev_addr, &(cntx->source_dev[i].dev_addr), sizeof(bt_bd_addr_t)) == 0)) {
                    dev = &(cntx->source_dev[i]);
                    break;
                }
            }

            break;
        }

        case BT_SOURCE_SRV_DEVICE_UNUSED: {
            for (i = 0; i < BT_SOURCE_SRV_MAX_DEVICE_NUMBER; ++i) {
                if (cntx->source_dev[i].a2dp_hd == BT_SOURCE_SRV_INVALID_HD &&
                    cntx->source_dev[i].avrcp_hd == BT_SOURCE_SRV_INVALID_HD) {
                    dev = &(cntx->source_dev[i]);
                    break;
                }
            }

            break;
        }

        case BT_SOURCE_SRV_DEVICE_USED: {
            for (i = 0; i < BT_SOURCE_SRV_MAX_DEVICE_NUMBER; ++i) {
                if (cntx->source_dev[i].a2dp_hd != BT_SOURCE_SRV_INVALID_HD) {
                    dev = &(cntx->source_dev[i]);
                    break;
                }
            }
            break;
        }

        default:
            break;
    }
    return dev;
}

//TODO
void bt_source_srv_reset_a2dp_info(bt_source_srv_device_t *dev)
{
    bt_source_srv_report("[source][a2dp]reset-info \r\n");

    bt_source_srv_memset(&(dev->a2dp), 0x00, sizeof(SourceProfileA2dp));
    dev->a2dp_hd = BT_SOURCE_SRV_INVALID_HD;
    dev->a2dp_role = BT_A2DP_INVALID_ROLE;
    dev->a2dp.profile.med_handle = NULL;
}

void bt_source_srv_reset_avrcp_info(bt_source_srv_device_t *dev)
{
    bt_source_srv_report("[source][avrcp]reset-info \r\n");

    dev->avrcp_hd = BT_SOURCE_SRV_INVALID_HD;
    dev->avrcp_role = BT_AVRCP_ROLE_UNDEF;
    dev->avrcp_state = BT_SOURCE_SRV_AVRCP_DISCONNECTED; 
    dev->avrcp_play_status = BT_AVRCP_EVENT_MEDIA_PLAY_STOPPED;
}

void bt_source_srv_reset_device(bt_source_srv_device_t *dev)
{
    bt_source_srv_report("[source][a2dp]reset-device \r\n");

    bt_source_srv_memset(dev, 0x00, sizeof(bt_source_srv_device_t)); 
    dev->conn_bit = 0x00;
    dev->a2dp_hd = BT_SOURCE_SRV_INVALID_HD;
    bt_source_srv_reset_a2dp_info(dev);
    bt_source_srv_reset_avrcp_info(dev);

}



