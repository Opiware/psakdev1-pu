/* Copyright Statement:
 *
 */

#ifndef __BT_PLATFORM_H__
#define __BT_PLATFORM_H__

/**
 * This header file describes the task apis or packed define used by user or SDK header file.
 */

#ifdef __cplusplus
#define BT_EXTERN_C_BEGIN extern "C" {
#else
#define BT_EXTERN_C_BEGIN
#endif

#ifdef __cplusplus
#define BT_EXTERN_C_END }
#else
#define BT_EXTERN_C_END
#endif

#include <stdint.h>
#include <string.h>
BT_EXTERN_C_BEGIN

/**
 * @brief BT_PACKED is used in structure define to make the structure more compact.The define is different as per compiler.
 */
#if _MSC_VER >= 1500
#define BT_PACKED(...) __pragma(pack(push, 1)) __VA_ARGS__ __pragma(pack(pop))
#elif defined(__GNUC__)
#define BT_PACKED(...) __VA_ARGS__ __attribute__((__packed__))
#define BT_ALIGNMENT4(...) __VA_ARGS__ __attribute__((aligned(4)))
#elif defined(__ARMCC_VERSION)
#pragma anon_unions
#define BT_PACKED(...) __VA_ARGS__ __attribute__((__packed__))
#define BT_ALIGNMENT4(...) __VA_ARGS__ __attribute__((aligned(4)))
#elif defined(__ICCARM__)
#define BT_PACKED(...) __packed __VA_ARGS__
#define BT_ALIGNMENT4(...) _Pragma("data_alignment=4") __VA_ARGS__
#else
#error "Unsupported Platform"
#endif

/*
 * @brief                  It is a user define function being invoked if having new bt interrupt.
 * @param[in] is_from_isr  is the current contex isr or not.
 * @return                 None.
 * @par                    Example
 * @code
 *      static uint32_t bt_task_semaphore = 0;
 *       void bt_trigger_interrupt(uint32_t is_from_isr)
 *       {
 *           if(bt_task_semaphore == 0) {
 *               return;
 *           }
 *           if(is_from_isr != 0) {
 *               bt_os_layer_give_semaphore_from_isr(bt_task_semaphore);
 *           }
 *           else {
 *               bt_os_layer_give_semaphore(bt_task_semaphore);
 *           }
 *       }
 *       
 *      void bt_task(void * arg)
 *      {
 *
 *          //init samaphore 
 *          bt_task_semaphore = bt_os_layer_create_semaphore();
 *          BT_ASSERT(bt_task_semaphore);  
 *
 *          // power on bt 
 *          bt_power_on(NULL, NULL);
 *
 *          // main loop 
 *          do {
 *              bt_os_layer_take_semaphore(bt_task_semaphore);
 *
 *              // handle interrupt 
 *              if (BT_STATUS_SUCCESS != bt_handle_interrupt()) {
 *                  break;
 *              }
 *          } while (1);
 *      }
 * @endcode
 */
void bt_trigger_interrupt(uint32_t is_from_isr);

/**
 * @brief                This function handle the bt interrupt.
 * @return               #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
int32_t bt_handle_interrupt(void);

BT_EXTERN_C_END

#endif
