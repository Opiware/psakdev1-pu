/* Copyright Statement:
 *
 */

#ifndef __BT_CALLBACK_MANAGER_CONFIG_H__
#define __BT_CALLBACK_MANAGER_CONFIG_H__


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @addtogroup BluetoothServices_CM BT Callback Manager
 * @{
 * @{
*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @addtogroup BluetoothServices_CM_define Define
 * @{ */
#define BT_CALLBACK_MANAGER_APP_EVENT_CALLBACK_MAX (20)     /**< The maximum number of callbacks that can be registered for #bt_callback_type_app_event. */
#if !defined(__MTK_BLE_ONLY_ENABLE__)
#define BT_CALLBACK_MANAGER_USER_RECORD_MAX (10)            /**< The maximum number of user records. */
#endif

/**
 * @} */

#ifdef __cplusplus
}
#endif

/**
 * @}
 * @} */

#endif /* __BT_CALLBACK_MANAGER_CONFIG_H__ */

