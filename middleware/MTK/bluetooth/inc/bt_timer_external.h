/* Copyright Statement:
 *
 */

#ifndef BT_TIMER_EXTERNAL_H
#define BT_TIMER_EXTERNAL_H
#include <stdbool.h>
#include <stdint.h>

#ifdef MTK_BT_TIMER_EXTERNAL_ENABLE
#define __BT_TIMER_EXT_SUPPORT__
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BT_TIMER_EXT_INSTANCE_NUM 10
#define BT_TIMER_EXT_EXPIRED 0x80

#define BT_TIMER_EXT_STATUS_SUCCESS  0
#define BT_TIMER_EXT_STATUS_FAIL     -1
#define BT_TIMER_EXT_STATUS_OOM      -2
typedef int32_t bt_timer_ext_status_t;

/* For BT Timer EXT ID Structure. */
/*
 * +---------+-------------+--------+
 * |Module ID| Group Mask  | Timer  |
 * +---------+-------------+--------+ */

#define BT_MODULE_TIMER_EXT   0x88000000 /**< Prefix of the timer ext module. */

#define BT_TIMER_EXT_GROUP_SINK_MASK  0x00010000
#define BT_TIMER_EXT_GROUP_SOURCE_MASK  0x00020000
#define BT_TIMER_EXT_GROUP_INVALID_MASK 0x00FFFFFF

#define BT_TIMER_EXT_GROUP_SINK(timer) \
        (BT_MODULE_TIMER_EXT | BT_TIMER_EXT_GROUP_SINK_MASK | (timer))

#define BT_TIMER_EXT_GROUP_SOURCE(timer) \
        (BT_MODULE_TIMER_EXT | BT_TIMER_EXT_GROUP_SOURCE_MASK | (timer))


/**
 * @brief                  Timeout callback function prototype
 * @param[in] timer_id     Timer ID
 * @param[in] data         User data saved in timer instance
 * @return                 None */
typedef void (*bt_timer_ext_timeout_callback_t) (uint32_t timer_id, uint32_t data);

/**
 * @brief                           Timeout instance structure */
typedef struct _bt_timer_ext_t{
    uint32_t timer_id;                /**<  module id + module defined id */
    uint32_t data;                    /**<  user data */
    uint32_t time_tick;               /**<  timer timeout in tick */
    bt_timer_ext_timeout_callback_t cb;       /**<  timer timeout callback function */
} bt_timer_ext_t;


void bt_timer_ext_init(void);

/**
 * @brief                   To start a timer
 * @param[in] timer_id      Timer ID
 * @param[in] data          User data saved in timer instance
 * @param[in] time_ms       timer timeout in ms
 * @param[in] cb            timer timeout callback function
 * @return                  bt_timer_ext_STATUS_SUCCESS if add timer success
                            bt_timer_ext_STATUS_OOM if timer reach max count
                            bt_timer_ext_STATUS_FAIL if double start */
bt_timer_ext_status_t bt_timer_ext_start(uint32_t timer_id, uint32_t data, uint32_t time_ms, bt_timer_ext_timeout_callback_t cb);

/**
 * @brief                   Stop a timer
 * @param[in] timer_id      Timer ID
 * @return                  bt_timer_ext_STATUS_SUCCESS if cancel timer success
                            bt_timer_ext_STATUS_FAIL if not found */
bt_timer_ext_status_t bt_timer_ext_stop(uint32_t timer_id);

void bt_timer_ext_check_status(void);
void bt_timer_ext_handle_interrupt(void);

/**
 * @brief                   Find a timer
 * @param[in] timer_id      Timer ID
 * @return                  A pointer to the timer instance */
bt_timer_ext_t* bt_timer_ext_find(uint32_t timer_id);



#ifdef __cplusplus
}
#endif

#endif /* BT_TIMER_EXTERNAL_H */

