/* Copyright Statement:
 *
 */

#include "bt_sink_srv_resource.h"



#ifdef __BT_SINK_SRV_MUSIC_MODE_SUPPORT__
#include "bt_sink_srv_mp3.h"
#include "bt_a2dp.h"
#include "bt_avrcp.h"
#include "bt_sink_srv_music.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_conmgr.h"



static bt_sink_srv_music_mode_t g_bt_sink_srv_music_mode = BT_SINK_SRV_MODE_LOCAL_MUSIC;

static void bt_sink_srv_handle_local_music_mode(void)
{
    int32_t ret1 = BT_SINK_SRV_MUSIC_ERR_FAIL_1ST;
    int32_t ret2 = BT_SINK_SRV_MUSIC_ERR_FAIL_1ST;
    bt_sink_srv_music_device_t *dev = NULL;
    bt_bd_addr_t *dev_addr = NULL;
    bt_bd_addr_t addr_list[BT_SINK_SRV_CM_MAX_DEVICE_NUMBER];
    uint32_t addr_count = 0;
    int32_t i = 0;

    addr_count = bt_sink_srv_cm_get_connected_device(BT_SINK_SRV_PROFILE_NONE, addr_list);

    for (i = 0; i < addr_count; ++i) {
        dev_addr = &(addr_list[i]);
        dev = bt_sink_srv_music_get_device(BT_SINK_SRV_MUSIC_DEVICE_ADDR_A2DP, (void *)dev_addr);
        if (dev) {
            ret1 = bt_a2dp_disconnect(dev->a2dp_hd);
        }
        dev = bt_sink_srv_music_get_device(BT_SINK_SRV_MUSIC_DEVICE_ADDR_AVRCP, (void *)dev_addr);
        if (dev) {
            ret2 = bt_avrcp_disconnect(dev->avrcp_hd);
        }
        bt_sink_srv_report("[Sink][mode]handle_local-ret1: %d, ret2: %d", ret1, ret2);
    }

    bt_sink_srv_report("[Sink][mode]handle_local(e)-count: %d", addr_count);
}


static void bt_sink_srv_handle_bt_music_mode(void)
{
    int32_t ret = 0, err = 0;
    bt_sink_srv_music_device_t *dev = NULL;
    uint32_t hd = 0;
    bt_bd_addr_t *dev_addr = NULL;
    bt_bd_addr_t addr_list[BT_SINK_SRV_CM_MAX_DEVICE_NUMBER];
    uint32_t addr_count = 0;
    int32_t i = 0;

    addr_count = bt_sink_srv_cm_get_connected_device(BT_SINK_SRV_PROFILE_NONE, addr_list);
    for (i = 0; i < addr_count; ++i) {
        /* Connect a2dp i */
        dev_addr = &(addr_list[i]);
        ret = bt_a2dp_connect(&hd, (const bt_bd_addr_t *)dev_addr, BT_A2DP_SINK);
        if (BT_STATUS_SUCCESS == ret) {
            dev = bt_sink_srv_music_get_device(BT_SINK_SRV_MUSIC_DEVICE_ADDR_A2DP, dev_addr);
            if (dev) {
                dev->a2dp_hd = hd;
                dev->role = BT_A2DP_SINK;
                /* unexpected, need handle */
                err = BT_SINK_SRV_MUSIC_ERR_FAIL_1ST;
            } else {
                dev = bt_sink_srv_music_get_device(BT_SINK_SRV_MUSIC_DEVICE_UNUSED, AUDIO_SRC_SRV_PSEUDO_DEVICE_A2DP);
                if (dev) {
                    dev->a2dp_hd = hd;
                    dev->role = BT_A2DP_SINK;
                    bt_sink_srv_memcpy(&(dev->dev_addr), dev_addr, sizeof(bt_bd_addr_t));
                    /* normal case */
                    err = BT_SINK_SRV_MUSIC_ERR_SUCCESS_1ST;
                } else {
                    /* unexpected, no unused device, please check log */
                    err = BT_SINK_SRV_MUSIC_ERR_FAIL_2ND;
                }
            }
        }
        bt_sink_srv_report("[Sink][mode]handle_bt_music_mode-i: %d, ret: %d, err: %d", i, ret, err);
    }

    bt_sink_srv_report("[Sink][mode]handle_bt_music_mode-num: %d", addr_count);
}


static void bt_sink_srv_send_mode_change_event(void)
{
    ;
}


void bt_sink_srv_music_mode_timer_hdl(uint32_t timer_id, uint32_t data)
{
    bt_sink_srv_music_mode_t mode = 0;
    int32_t err = 0, ret = 0;


    mode = bt_sink_srv_get_music_mode();

    if (mode == BT_SINK_SRV_MODE_LOCAL_MUSIC) {
        bt_sink_srv_handle_local_music_mode();
    } else if (mode == BT_SINK_SRV_MODE_BT_MUSIC) {
        //bt_sink_srv_handle_bt_music_mode();
        /* Stop local music */
        bt_sink_srv_mp3_pause();
    } else {
        err = BT_SINK_SRV_MUSIC_ERR_FAIL_1ST;
    }

    bt_sink_srv_send_mode_change_event(); 

    bt_sink_srv_report("[Sink][mode]mode_timer_hdl-err: %d, ret: %d, mode: %d", err, ret, mode);
}


void bt_sink_srv_notify_mode_change(bt_sink_srv_music_mode_t old_mode, bt_sink_srv_music_mode_t new_mode)
{
    int32_t err = 0;


    if (bt_timer_ext_find(BT_SINK_SRV_MUSIC_MODE_TIMER_ID)) {
        /* Just connect, wait timeout handle */
        err = BT_SINK_SRV_MUSIC_ERR_SUCCESS_1ST;
    } else {
        if (new_mode == BT_SINK_SRV_MODE_LOCAL_MUSIC) {
            bt_sink_srv_handle_local_music_mode();
        } else if (new_mode == BT_SINK_SRV_MODE_BT_MUSIC) {
            bt_sink_srv_handle_bt_music_mode();
            /* Stop local music */
            bt_sink_srv_mp3_pause();
        } else {
            err = BT_SINK_SRV_MUSIC_ERR_FAIL_1ST;
        }
        bt_sink_srv_send_mode_change_event();
        err = BT_SINK_SRV_MUSIC_ERR_SUCCESS_2ND;
    }

    bt_sink_srv_report("[Sink][mode]notify_mode_change-err: %d", err);
}


static int32_t bt_sink_srv_music_switch_mode(bt_sink_srv_music_mode_t mode)
{
    int32_t ret = 0;
    bt_sink_srv_music_mode_t old_mode;

    if (g_bt_sink_srv_music_mode != mode) {
        old_mode = g_bt_sink_srv_music_mode;
        g_bt_sink_srv_music_mode = mode;
        bt_sink_srv_notify_mode_change(old_mode, mode);
    }

    return ret;
}


int32_t bt_sink_srv_set_music_mode(bt_sink_srv_music_mode_t mode)
{
    bt_sink_srv_report("[Sink][mode]set_mode--old: %d, new: %d", g_bt_sink_srv_music_mode, mode);

    return bt_sink_srv_music_switch_mode(mode);
}


bt_sink_srv_music_mode_t bt_sink_srv_get_music_mode(void)
{
    bt_sink_srv_report("[Sink][mode]get_mode--: %d", g_bt_sink_srv_music_mode);

    return g_bt_sink_srv_music_mode;
}

#endif /* __BT_SINK_SRV_MUSIC_MODE_SUPPORT__ */

