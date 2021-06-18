/* Copyright Statement:
 *
 */



#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include "at_command.h"

#include "hal_gpt.h"
#include <stdlib.h>


#ifdef HAL_KEYPAD_MODULE_ENABLED
#include "hal_keypad_internal.h"
#include "hal_log.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"

extern uint32_t keypad_get_buffer_left_size(void);
extern void keypad_push_one_key_to_buffer(hal_keypad_key_state_t state, uint32_t data);


/* keypad simulate cmd: AT+EKP=<key_number>:<action_index>, for example: 
 *
 *	 AT+EKP=12:0 // release
 *	 AT+EKP=12:1 // press
 *	 AT+EKP=12:2 // long press
 *	 AT+EKP=12:3 // repeat
 * */

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_sleep_manager.h"
#include "hal_sleep_driver.h"

const static char *at_keypad_lock_sleep_name = "at_keypad";
static uint8_t at_keypad_lock_sleep_handle[32];

#define AT_KEYPAD_GET_SLEEP_HANDLE(i) \
do{ \
    at_keypad_lock_sleep_handle[i] = hal_sleep_manager_set_sleep_handle(at_keypad_lock_sleep_name); \
    if(at_keypad_lock_sleep_handle[i] == INVALID_SLEEP_HANDLE ) { \
        log_hal_error("[keypad]:get sleep handle failed\r\n"); \
        return ATCI_STATUS_ERROR; \
    } \
}while(0)

#define AT_KEYPAD_RELEASE_SLEEP_HANDLE(i) \
do{ \
    hal_sleep_manager_release_sleep_handle(at_keypad_lock_sleep_handle[i]); \
}while(0)

#define AT_KEYPAD_LOCK_SLEEP(i) \
do{ \
    hal_sleep_manager_lock_sleep(at_keypad_lock_sleep_handle[i]); \
}while(0)

#define AT_KEYPAD_UNLOCK_SLEEP(i) \
do{ \
    hal_sleep_manager_unlock_sleep(at_keypad_lock_sleep_handle[i]); \
}while(0)

#else
#define AT_KEYPAD_GET_SLEEP_HANDLE(i)
#define AT_KEYPAD_RELEASE_SLEEP_HANDLE(i)
#define AT_KEYPAD_LOCK_SLEEP(i)
#define AT_KEYPAD_UNLOCK_SLEEP(i)
#endif

/*--- Function ---*/
atci_status_t  atci_cmd_hdlr_keypad_simulate(atci_parse_cmd_param_t *parse_cmd);

extern keypad_context_t keypad_context;//.keypad_callback

/* AT command handler  */
atci_status_t atci_cmd_hdlr_keypad_simulate(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t resonse = {{0}};

    char *param1 = NULL;
    char *param2 = NULL;
    uint32_t key_number, key_action_index, key_position;

    resonse.response_flag = 0; /*    Command Execute Finish.  */

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:
            strcpy((char *)resonse.response_buf, "AT+EKP=<key_number>:<action_index>\r\n");
            resonse.response_len = strlen((char *)resonse.response_buf);
            atci_send_response(&resonse);
            break;

        case ATCI_CMD_MODE_EXECUTION:
            strcpy((char *)resonse.response_buf, "OK\r\n");
            resonse.response_len = strlen((char *)resonse.response_buf);
            atci_send_response(&resonse);

            param1 = strtok(parse_cmd->string_ptr, ":");
            param2 = strtok(NULL, ":");        /* action index parse. */
            key_action_index = atoi(param2);   /* action index parse. */
            param2 = strtok(param1, "=");
            key_number = atoi(strtok(NULL, "="));  /*  key number parse. */
            key_position = key_number;

            if (!key_action_index) {
                if (keypad_get_buffer_left_size() > 0) {
                    keypad_buffer.press_count--;
                    keypad_state.current_state[key_position] = HAL_KEYPAD_KEY_RELEASE;
                    keypad_push_one_key_to_buffer(keypad_state.current_state[key_position], key_position);

                    keypad_context.keypad_callback.callback(keypad_context.keypad_callback.user_data);
                    AT_KEYPAD_UNLOCK_SLEEP(key_position);
                    AT_KEYPAD_RELEASE_SLEEP_HANDLE(key_position);
                } else {
                    /* buffer size is not enough. */
                    strcpy((char *)resonse.response_buf, "Buffer not enough\r\n");
                    resonse.response_len = strlen((char *)resonse.response_buf);
                    atci_send_response(&resonse);
                }
            } else if (1 == key_action_index) {
                if (keypad_get_buffer_left_size() > (keypad_buffer.press_count + 1)) {
                    keypad_buffer.press_count++;
                    keypad_state.current_state[key_position] = HAL_KEYPAD_KEY_PRESS;
                    keypad_state.position[key_position] = key_position;
                    keypad_push_one_key_to_buffer(keypad_state.current_state[key_position], keypad_state.position[key_position]);
                    AT_KEYPAD_GET_SLEEP_HANDLE(key_position);
                    AT_KEYPAD_LOCK_SLEEP(key_position);

                    keypad_context.keypad_callback.callback(keypad_context.keypad_callback.user_data);
                } else {
                    /* buffer size is not enough. */
                    strcpy((char *)resonse.response_buf, "Buffer not enough\r\n");
                    resonse.response_len = strlen((char *)resonse.response_buf);
                    atci_send_response(&resonse);
                }
            }

            else if (2 == key_action_index || 3 == key_action_index) {
                if (keypad_get_buffer_left_size() > (keypad_buffer.press_count + 1)) {
                    keypad_state.current_state[key_position] = (hal_keypad_key_state_t)key_action_index;
                    keypad_state.position[key_position] = key_position;
                    keypad_push_one_key_to_buffer(keypad_state.current_state[key_position], keypad_state.position[key_position]);
                    keypad_context.keypad_callback.callback(keypad_context.keypad_callback.user_data);
                } else {
                    /* buffer size is not enough. */
                    strcpy((char *)resonse.response_buf, "Buffer not enough\r\n");
                    resonse.response_len = strlen((char *)resonse.response_buf);
                    atci_send_response(&resonse);
                }
            }
            break;
        default :
            /* others are invalid command format */
            strcpy((char *)resonse.response_buf, "ERROR\r\n");
            resonse.response_len = strlen((char *)resonse.response_buf);
            atci_send_response(&resonse);
            break;
    }
    return ATCI_STATUS_OK;
}

#endif

