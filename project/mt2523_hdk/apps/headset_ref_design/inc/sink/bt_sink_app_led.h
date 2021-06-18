/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_APP_LED_H__
#define __BT_SINK_APP_LED_H__

#include "bt_sink_srv.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief IME_COMMAND is used in structure define to make the structure more compact.The define is different as per compiler. */
#if _MSC_VER >= 1500
#define LED_CONFIG_STATE(...) __pragma(pack(push, 1)) __VA_ARGS__ __pragma(pack(pop))
#elif defined(__GNUC__)
#define LED_CONFIG_STATE(...) __VA_ARGS__ __attribute__((__packed__))
#define LED_CONFIG_STATE_ALIGNMENT4(...) __VA_ARGS__ __attribute__((aligned(4)))
#elif defined(__ARMCC_VERSION)
#pragma anon_unions
#define LED_CONFIG_STATE(...) __VA_ARGS__ __attribute__((__packed__))
#define LED_CONFIG_STATE_ALIGNMENT4(...) __VA_ARGS__ __attribute__((aligned(4)))
#elif defined(__ICCARM__)
#define LED_CONFIG_STATE(...) __packed __VA_ARGS__
#define LED_CONFIG_STATE_ALIGNMENT4(...) _Pragma("data_alignment=4") __VA_ARGS__
#else
#error "Unsupported Platform"
#endif



#define bt_sink_app_led_report(_message,...) LOG_I(LED_APP, (_message), ##__VA_ARGS__)

#define BT_SINK_APP_LED_DURATION_INFINITE      (0xFFFF)
#define BT_SINK_APP_LED_COUNT_INFINITE             (0xFF)

/** @brief This enum define number of LED */
typedef enum {
    BT_SINK_APP_LED_STATE_NONE,                             /**<  0 */
    BT_SINK_APP_LED_STATE_POWER_ON,                 /**<  1  */ 
    BT_SINK_APP_LED_STATE_POWER_OFF,               /**<  2  */
    BT_SINK_APP_LED_STATE_IDLE,                               /**<   3  */
    BT_SINK_APP_LED_STATE_PAIRING,                       /**<   4  */
    BT_SINK_APP_LED_STATE_PAIR_COMPLETE,      /**<  5 */
    BT_SINK_APP_LED_STATE_INCOMING_CALL,        /**< 6 */
    BT_SINK_APP_LED_STATE_OUTGOING_CALL,    /**<  7 */
    BT_SINK_APP_LED_STATE_CONNECTED_IDLE,   /**<  8  */
    BT_SINK_APP_LED_STATE_ACTIVE_CALL,             /**<  9 */
    BT_SINK_APP_LED_STATE_RECONNECT,             /**<   10  */
    BT_SINK_APP_LED_STATE_CHARGING,                 /**<  11  */
    BT_SINK_APP_LED_STATE_BATTERY_FULL,       /**<   12 */
    BT_SINK_APP_LED_STATE_LOW_BATTERY,        /**<   13 */
    BT_SINK_APP_LED_STATE_DISCONNECTED,        /**< 14 */
    BT_SINK_APP_LED_STATE_LOCAL_MUSIC_PLAYING,     /**< 15 */
    BT_SINK_APP_LED_STATE_BT_MUSIC_PLAYING,     /**< 16 */
    BT_SINK_APP_LED_STATE_RESET_PAIRED_LIST,  /**<  17 */
    BT_SINK_APP_LED_STATE_END                            /**< The total number of LED state. */
} bt_sink_app_led_state_t;

/** @brief This enum define LED number*/
typedef enum {
    BT_SINK_APP_LED_NUM_1 = 0,                  /**<  LED 1. */
    BT_SINK_APP_LED_NUM_2 = 1,                  /**<  LED 2. */
    BT_SINK_APP_LED_MAX_NUM  /**< The total number of LED (invalid LED number). */
} bt_sink_app_led_num_t;

typedef uint8_t bt_sink_app_led_mask_t;
#define BT_SINK_APP_LED_NONE         (0x00)  /**< This value means no led*/
#define BT_SINK_APP_LED_1                   (0x01)  /**< This value means led1*/
#define BT_SINK_APP_LED_2                   (0x02) /**< This value means  led2*/

LED_CONFIG_STATE(
typedef struct {
    bt_sink_app_led_state_t state;
    bt_sink_app_led_mask_t led_mask;
    uint16_t flash_on_duration;
    uint16_t flash_off_duration;
    uint8_t  flash_count;
    uint16_t interval;
    uint8_t period_count;
    uint8_t enable;
}) bt_sink_app_led_state_config_table_t;

void bt_sink_app_led_init(void);
void bt_sink_app_led_light(bt_sink_app_led_state_t state);
bool bt_sink_app_led_check_if_in_the_state(bt_sink_app_led_state_t state);
bt_sink_srv_status_t bt_sink_app_update_led_by_sink_event(bt_sink_srv_event_t event_id, void *parameters);
void bt_sink_app_update_led_by_battery(int32_t charger_exist, int32_t capacity);

#ifdef __cplusplus
}
#endif

#endif /*__BT_SINK_APP_LED_H__*/

