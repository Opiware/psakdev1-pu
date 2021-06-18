/* Copyright Statement:
 *
 */

#ifndef BT_SINK_APP_VOICE_PROMPT_H
#define BT_SINK_APP_VOICE_PROMPT_H

#include "bt_sink_srv.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************
 * Macro & Define
 *
 ********************************************************/

#define bt_sink_app_voice_prompt_report(_message,...) LOG_I(VOICE_PROMPT_APP, (_message), ##__VA_ARGS__)

/********************************************************
 * Enum & Structures
 *
 ********************************************************/
/** @brief This enum define tone of voice prompt */
typedef enum {
    VOICE_PROMPT_TONE_POWER_ON,                   /**<  0  */ 
    VOICE_PROMPT_TONE_POWER_OFF,                 /**<  1  */
    VOICE_PROMPT_TONE_RESET_PAIRED_LIST,  /**< 2 */
    VOICE_PROMPT_TONE_PAIRING,                            /**<  3  */
    VOICE_PROMPT_TONE_CONNECTED,                  /**<  4  */
    VOICE_PROMPT_TONE_DISCONNECTED,           /**< 5 */
    VOICE_PROMPT_TONE_VOLUME_CHANGE,     /**<  6 */
    VOICE_PROMPT_TONE_CALL_AUDIO_TRANSFER,     /**<  7 */
    VOICE_PROMPT_TONE_CALL_END,                       /**<  8*/
    VOICE_PROMPT_TONE_CALL_REFUSED,             /**<  9 */
    VOICE_PROMPT_TONE_CALL_REDIALING,           /**<  10 */
    VOICE_PROMPT_TONE_LOW_BATTERY,              /**<   11 */
    VOICE_PROMPT_TONE_MP3_MUSIC,                    /**< 12 */
    VOICE_PROMPT_TONE_BT_MUSIC,                      /**< 13 */
    VOICE_PROMPT_TONE_NUM                   /**< The total number of voice prompt tone. */
} bt_sink_app_voice_prompt_tone_t;

typedef struct {
    const uint8_t *buf;
    uint32_t size;
} bt_sink_app_voice_prompt_buf_t;


typedef struct {
    bt_sink_srv_action_t curr_action;
} bt_sink_app_voice_prompt_context_t;

/********************************************************
 * External Function
 *
 ********************************************************/
void bt_sink_app_voice_prompt_by_sink_action(bt_sink_srv_action_t action);
void bt_sink_app_voice_prompt_by_battery(int32_t charger_exist, int32_t capacity);
bt_sink_srv_status_t bt_sink_app_voice_prompt_by_sink_event(bt_sink_srv_event_t event_id, void *parameters);
void bt_sink_app_voice_prompt_play(uint8_t tone_idx);

#ifdef __cplusplus
    }
#endif

#endif /* BT_SINK_APP_VOICE_PROMPT_H */

