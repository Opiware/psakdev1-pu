/* Copyright Statement:
 *
 */

#include "bt_sink_app_led.h"

#ifndef  __CFW_CONFIG_MODE__
static const bt_sink_app_led_state_config_table_t bt_sink_app_led_state_cfg_table[] = {
#if (defined( MTK_CORD_FREE_HEADSET_ENABLE) || defined (MTK_INEAR_NOODLES_HEADSET_ENABLE))
    /*Led 1, blue; led2, red*/
    { /*long on*/
        BT_SINK_APP_LED_STATE_CHARGING, BT_SINK_APP_LED_2,
        BT_SINK_APP_LED_DURATION_INFINITE, 0, 1, 0, 1, 1
    },
    { /*long on*/
        BT_SINK_APP_LED_STATE_BATTERY_FULL, BT_SINK_APP_LED_1,
        BT_SINK_APP_LED_DURATION_INFINITE, 0, 1, 0, 1, 1
    },
    {  /*led on 100ms and led off 100ms 2 times*/
        BT_SINK_APP_LED_STATE_RESET_PAIRED_LIST, BT_SINK_APP_LED_2,
        200, 200, 2, 0, 1, 1
    },
    { /*led on 100ms and led off 100ms 1 times every 8s*/
        BT_SINK_APP_LED_STATE_ACTIVE_CALL, BT_SINK_APP_LED_1,
        200, 2000, BT_SINK_APP_LED_COUNT_INFINITE, 0, 1, 1
    },
    { /*led on 100ms and led off 100ms 1 times every 8s*/
        BT_SINK_APP_LED_STATE_INCOMING_CALL, BT_SINK_APP_LED_1,
        200, 200, BT_SINK_APP_LED_COUNT_INFINITE, 0, 1, 1
    },
    { /*led on 100ms and led off 100ms 1 times every 8s*/
        BT_SINK_APP_LED_STATE_OUTGOING_CALL, BT_SINK_APP_LED_1,
        200, 200, BT_SINK_APP_LED_COUNT_INFINITE, 0, 1, 1
    },
    {/*led on 100ms and led off  8000 always*/
        BT_SINK_APP_LED_STATE_IDLE, BT_SINK_APP_LED_2,
        200, 8000, BT_SINK_APP_LED_COUNT_INFINITE, 0, 1, 1
    },
    {/*led on 100ms and led off  8000 always*/
        BT_SINK_APP_LED_STATE_CONNECTED_IDLE, BT_SINK_APP_LED_1,
        200, 8000, BT_SINK_APP_LED_COUNT_INFINITE, 0, 1, 1
    },
    { /*led on 50ms and led off 50ms three times*/
        BT_SINK_APP_LED_STATE_PAIR_COMPLETE, BT_SINK_APP_LED_1,
        200, 200, 5, 0, 1, 1
    },
    { /*led on 100ms and led off  100 45 times*/
        BT_SINK_APP_LED_STATE_PAIRING, (BT_SINK_APP_LED_1 |BT_SINK_APP_LED_2),
        200, 200, 500, 0, 1, 1
    },
    { /*led on 100ms and led off 100ms each 8s*/
        BT_SINK_APP_LED_STATE_POWER_ON,  BT_SINK_APP_LED_1,
        1000, 1000, 1, 0, 1, 1
    },
    { /*led on 2s*/
        BT_SINK_APP_LED_STATE_LOCAL_MUSIC_PLAYING, BT_SINK_APP_LED_1,
        200, 3000, BT_SINK_APP_LED_COUNT_INFINITE, 0, 1, 1
    },
    { /*led on 2s*/
        BT_SINK_APP_LED_STATE_BT_MUSIC_PLAYING, BT_SINK_APP_LED_1,
       200, 3000, BT_SINK_APP_LED_COUNT_INFINITE, 0, 1, 1
    },
    { /*led on 2s*/
        BT_SINK_APP_LED_STATE_POWER_OFF, BT_SINK_APP_LED_2,
        2000, 0, 0, 0, 1, 1
    },
    { /*led on 50ms and led off 50ms always*/
        BT_SINK_APP_LED_STATE_DISCONNECTED, BT_SINK_APP_LED_1,
        200, 200, 5, 0, 1, 1
    } 
#else /*defined( MTK_CORD_FREE_HEADSET_ENABLE) || defined (MTK_INEAR_NOODLES_HEADSET_ENABLE)*/
    /*Led 1, red; led2, blue*/
    { /*long on*/
        BT_SINK_APP_LED_STATE_CHARGING, BT_SINK_APP_LED_2,
        BT_SINK_APP_LED_DURATION_INFINITE, 0, 1, 0, 1, 1
    }
#endif /*defined( MTK_CORD_FREE_HEADSET_ENABLE) || defined (MTK_INEAR_NOODLES_HEADSET_ENABLE)*/        
};

const bt_sink_app_led_state_config_table_t *bt_sink_app_led_get_state_cfg_table(void)
{
    return bt_sink_app_led_state_cfg_table;
}
#else /*__CFW_CONFIG_MODE__*/

#include "cfw_define.h"
const bt_sink_app_led_state_config_table_t *bt_sink_app_led_get_state_cfg_table(void)
{
    return (const bt_sink_app_led_state_config_table_t *)(CFW_CFG_ITEM_VALUE(led_state_01));
}

#endif /*__CFW_CONFIG_MODE__*/

