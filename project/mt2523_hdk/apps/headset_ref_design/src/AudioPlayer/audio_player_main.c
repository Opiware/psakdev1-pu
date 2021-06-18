/* Copyright Statement:
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "audio_player_main.h"
#include "syslog.h"
#include "audio_player.h"
#include "bt_sink_srv.h"
#include "bt_sink_app_event.h"
#include "portable.h"
#include "bt_sink_srv_mp3.h"
#include "audio_file_manager.h"
#ifdef MTK_MP3_ON_FLASH_ENABLE
#include "audio_file_sample.h"
#endif
#ifdef __USB_MASS_STORAGE_ENABLE__
#ifdef MTK_USB_CONNECTED_STOP_ALL
#include "usb.h"
#endif
#endif
#ifdef MTK_PROMPT_SOUND_ENABLE
#include "voice_prompt_mix.h"
#endif

#include "bt_sink_srv_resource.h"

#ifdef __LOCAL_PLAYER_ENABLE__

/* static function declare */

/*************************/

log_create_module(AudPly, PRINT_LEVEL_INFO);

#ifdef __USB_MASS_STORAGE_ENABLE__
#ifdef MTK_USB_CONNECTED_STOP_ALL
static bool usbShow = false;

static void audio_player_registerUSBPlug();

#ifdef BT_SINK_APP_TEST_EXIT_MASS_STORAGE
 extern bool bt_sink_app_usb_is_com_port_mode(void);
#endif /*BT_SINK_APP_TEST_EXIT_MASS_STORAGE*/

#endif
#endif

//#define DEBUG_USE_PRINT
//#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE
#define DEBUG_PRINT(fmt, arg...)    printf(fmt, ##arg)
#else
#define DEBUG_PRINT(fmt, arg...)
#endif

#ifndef DEBUG_USE_PRINT
#define LOGI(fmt, arg...)          LOG_I(AudPly, fmt, ##arg);
#define LOGW(fmt, arg...)          LOG_W(AudPly, fmt, ##arg);
#define LOGE(fmt, arg...)          LOG_E(AudPly, fmt, ##arg);
#else
#define LOGI(fmt, arg...)          DEBUG_PRINT(fmt, ##arg);
#define LOGW(fmt, arg...)          DEBUG_PRINT(fmt, ##arg);
#define LOGE(fmt, arg...)          DEBUG_PRINT(fmt, ##arg);
#endif

void audio_player_task_main(void *param)
{
    bt_sink_srv_music_init();
    /* build file index here, calling audio_file_manager_init() */
    audio_file_manager_init();    
    
    /* scan audio file */
    bt_sink_srv_mp3_init();

#ifdef MTK_INEAR_NOODLES_HEADSET_ENABLE
    PMIC_VR_CONTROL(PMIC_VMC    , 0);
#endif    
    
#ifdef __USB_MASS_STORAGE_ENABLE__
#ifdef MTK_USB_CONNECTED_STOP_ALL
    /* register USB plug */
    audio_player_registerUSBPlug();
#endif
#endif
    
    while (1) {
        bt_sink_srv_mp3_processing();
    }
}


void audio_player_sink_key_action_handler(bt_sink_srv_action_t action)
{
    LOG_I(AudPly, "aud_action %d", action);

#ifdef __BT_SINK_SRV_MUSIC_MODE_SUPPORT__
    if (bt_sink_srv_get_music_mode() == BT_SINK_SRV_MODE_BT_MUSIC) {
        /* Ignore in bt mode */
        LOG_I(AudPly, "[AudPly]key_action--ignore");
        return;
    }
#endif

    switch (action) {
        case AUDIO_PLAYER_ACTION_VOLUME_UP: {
            audio_player_volume_up();
            break;
        }

        case AUDIO_PLAYER_ACTION_VOLUME_DOWN: {
            audio_player_volume_down();
            break;
        }

        case AUDIO_PLAYER_ACTION_VOLUME_MIN: {
            break;
        }

        case AUDIO_PLAYER_ACTION_VOLUME_MAX: {
            break;
        }

        case AUDIO_PLAYER_ACTION_PLAY: {
            audio_player_play();
            break;
        }

        case AUDIO_PLAYER_ACTION_PAUSE: {
            audio_player_pause();
            break;
        }

        case AUDIO_PLAYER_ACTION_PAUSE_WAV: {
            audio_player_pause_wav();
            break;
        }

        case AUDIO_PLAYER_ACTION_RESUME_WAV: {
            audio_player_resume_wav();
            break;
        }

        case AUDIO_PLAYER_ACTION_NEXT_TRACK: {
            audio_player_next_track();
            break;
        }

        case AUDIO_PLAYER_ACTION_PRE_TRACK: {
            audio_player_previous_track();
            break;
        }


        default:
            break;
    }
}

int32_t audio_player_play()
{
#ifdef MTK_PROMPT_SOUND_ENABLE
    voice_prompt_mix_stop_tone();
#endif
    
#ifdef __USB_MASS_STORAGE_ENABLE__
#ifdef MTK_USB_CONNECTED_STOP_ALL
    if (usbShow != false 
        #ifdef BT_SINK_APP_TEST_EXIT_MASS_STORAGE
            && !bt_sink_app_usb_is_com_port_mode()
        #endif
        ) {
        LOG_I(AudPly, "Reject play because of USB connected");
        return 0;
    } else
#endif
#endif
    {
        return bt_sink_srv_mp3_play();
    }
}


int32_t audio_player_pause()
{
    return bt_sink_srv_mp3_pause();
}

int32_t audio_player_pause_wav()
{
    wav_pause_test();
    
    return 0;
}

int32_t audio_player_resume_wav()
{
    wav_resume_test();
    
    return 0;
}

int32_t audio_player_next_track()
{
    return bt_sink_srv_mp3_next_track();
}


int32_t audio_player_previous_track()
{
    return bt_sink_srv_mp3_prev_track();
}


int32_t audio_player_volume_up()
{
    return bt_sink_srv_mp3_volume_up();
}


int32_t audio_player_volume_down()
{
    return bt_sink_srv_mp3_volume_down();
}


int32_t bt_sink_srv_mp3_file_callback(bt_sink_srv_mp3_file_event_type_t msg,  bt_sink_srv_mp3_event_t event)
{
    int32_t err = 0;
    switch (msg) {
        case BT_SINK_SRV_MP3_EVENT_GETFILENUM:
#ifndef MTK_MP3_ON_FLASH_ENABLE
            err = audio_file_manager_get_file_num_by_idx(event.get_file_num, 1);
#else
            *(event.get_file_num) = AUDIO_FILE_SAMPLE_FILE_TOTAL;
#endif
            break;
        case BT_SINK_SRV_MP3_EVENT_GETFILEPATHBYIDX:
#ifndef MTK_MP3_ON_FLASH_ENABLE
            err = audio_file_manager_get_file_path_by_idx(event.get_file_path_by_idx.path, 
                    MAX_FILE_PATH_LEN, 1, event.get_file_path_by_idx.idx);
#endif
            break;
        case BT_SINK_SRV_MP3_EVENT_OPEN:
            err = audio_file_manager_open(event.file_event.fp, event.file_event.path);
            break;
        case BT_SINK_SRV_MP3_EVENT_LSEEK:
            err = audio_file_manager_lseek(event.file_event.fp, event.file_event.pos,
                    event.file_event.offset);
            break;
        case BT_SINK_SRV_MP3_EVENT_READ:
            err = audio_file_manager_read(event.file_event.fp, event.file_event.buf,
                    event.file_event.bytetoread, event.file_event.byteread,
                    event.file_event.index, event.file_event.offset);
            break;
        case BT_SINK_SRV_MP3_EVENT_TELL:
            err = audio_file_manager_tell(event.file_event.fp, event.file_event.offset);
            break;
        case BT_SINK_SRV_MP3_EVENT_EOF:
            err = audio_file_manager_eof(event.file_event.fp, event.file_event.index,
                    event.file_event.offset);
            break;
        case BT_SINK_SRV_MP3_EVENT_SIZE:
            err = audio_file_manager_size(event.file_event.fp, event.file_event.index);
            break;
        case BT_SINK_SRV_MP3_EVENT_GET_BREAKPOINT:
            err = audio_file_manager_get_breakpoint((void *)event.bp_data);
            break;
        case BT_SINK_SRV_MP3_EVENT_SET_BREAKPOINT:
            err = audio_file_manager_set_breakpoint((void *)event.bp_data);
            break;
        default:
            break;
    }
    //LOGI("[AudPly]bt_sink_srv_mp3_file_callback msg %d ret %d", msg, err);
    return err;
}

#ifdef __USB_MASS_STORAGE_ENABLE__
#ifdef MTK_USB_CONNECTED_STOP_ALL
static void audio_player_USBPlugCallback(msc_callback_event_t event)
{
    LOG_I(AudPly, "event = %d\r\n", event);
    
#ifdef BT_SINK_APP_TEST_EXIT_MASS_STORAGE
    if(bt_sink_app_usb_is_com_port_mode()) {
        return;
    }
#endif
    if (event == MSC_EVENT_USB_CONNECTION) {
        if (usbShow == true) {
            LOG_E(AudPly, "abnormal connection event\r\n");
            return; // do not show if current screen is mass storage
        } else {
            usbShow = true;
        }
        // disable hci to prevent sending hci log to usb
        bt_hci_log_enabled();
        bt_demo_hci_log_switch(false);
        audio_player_pause();
        bt_sink_srv_mp3_deinit();
        audio_file_manager_deinit();

        LOG_I(AudPly, "ap_usb_deinit() = %d\r\n", ap_usb_deinit());
        LOG_I(AudPly, "ap_usb_init(USB_MASS_STORAGE) = %d\r\n", ap_usb_init(USB_MASS_STORAGE));
    } else {
        if (usbShow == false) {
            LOG_E(AudPly, "abnormal disconnection event\r\n");
            return; // do not show if current screen is not mass storage
        } else {
            usbShow = false;
        }
        LOG_I(AudPly, "ap_usb_init() = %d\r\n", ap_usb_deinit());

        bt_hci_log_enabled();
        bt_demo_hci_log_switch(true);
        audio_file_manager_init();
        bt_sink_srv_mp3_init();
    }
}

static void audio_player_registerUSBPlug()
{
    ap_usb_register_msc_callback(audio_player_USBPlugCallback);
}

#endif
#endif

#endif /* __LOCAL_PLAYER_ENABLE__ */

