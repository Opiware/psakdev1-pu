/* Copyright Statement:
 *
 */
#define BT_TASK_CONSUME_CHECK
#include "bt_os_layer_api.h"
#include "bt_platform.h"
#include "bt_system.h"
#include "hal_nvic.h"
#ifdef MTK_BT_TIMER_EXTERNAL_ENABLE
#include "bt_timer_external.h"
#endif
#ifdef BT_TASK_CONSUME_CHECK
#include "syslog.h"
#include "hal_gpt.h"
#include "bt_hci_log.h"
#include <stdio.h>
#include "hal_trng.h"


void bt_task_consume_hci_log(uint32_t total, uint32_t value, int32_t retvalue)
{
    char hci_log_string[64] = {0, 0x1B, 0xFC, 60};
    LOG_I(common, "[BT TASK]bt_task_consume_hci_log(%d, %d, %d)", total, value, retvalue);
    if (total == 0) {
        snprintf(hci_log_string + 4, 60, "poweron sonsume %u ms, error %d", (unsigned int)value, (int)retvalue);
    }
    else {
        snprintf(hci_log_string + 4, 60, "bt task cpu usage: %u in %u ms, error: %d", (unsigned int)value, (unsigned int)total, (int)retvalue);
    }
    bt_hci_log(0, hci_log_string, 64);
}
#endif


static void bt_task_generate_random_address(bt_bd_addr_t addr)
{
    uint32_t random_seed, i;
    hal_trng_status_t ret = HAL_TRNG_STATUS_OK;
    ret = hal_trng_init();
    if (HAL_TRNG_STATUS_OK != ret) {
        LOG_I(common, "[BT]generate_random_address--error 1");
    }
    for (i = 0; i < 30; ++i) {
        ret = hal_trng_get_generated_random_number(&random_seed);
        if (HAL_TRNG_STATUS_OK != ret) {
            LOG_I(common, "[BT]generate_random_address--error 2");
        }
    }
    /* randomly generate address */
    ret = hal_trng_get_generated_random_number(&random_seed);
    if (HAL_TRNG_STATUS_OK != ret) {
        LOG_I(common, "[BT]generate_random_address--error 3");
    }
    addr[0] = random_seed & 0xFF;
    addr[1] = (random_seed >> 8) & 0xFF;
    addr[2] = (random_seed >> 16) & 0xFF;
    addr[3] = (random_seed >> 24) & 0xFF;
    ret = hal_trng_get_generated_random_number(&random_seed);
    if (HAL_TRNG_STATUS_OK != ret) {
        LOG_I(common, "[BT]generate_random_address--error 4");
    }
    addr[4] = random_seed & 0xFF;
    addr[5] = (random_seed >> 8) | 0xC0;
    hal_trng_deinit();
}

static uint32_t bt_task_semaphore = 0;

/**
 * @brief     It is a user define function, for bt task.
 * @return    None. */
void bt_task(void * arg)
{
    uint32_t i;
    bt_bd_addr_t random_addr;
#ifdef BT_TASK_CONSUME_CHECK
    uint32_t end;
    uint32_t wait;
    uint32_t total;
    int32_t ret;
#endif

    bt_task_generate_random_address(random_addr);
    * (((uint8_t*)random_addr) + 5) |= 0xC0;
    bt_task_semaphore = bt_os_layer_create_semaphore();
    bt_os_layer_sleep_task(1000);
#ifdef BT_TASK_CONSUME_CHECK
    ret = (int32_t)hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &i);
#endif
    if (arg != NULL) {
        // If arg is NULL means user does not want to power on BT
        bt_power_on((bt_bd_addr_ptr_t)arg, (bt_bd_addr_ptr_t)&random_addr);
    }
#ifdef BT_TASK_CONSUME_CHECK
    ret += (int32_t)hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &end);
    bt_task_consume_hci_log(0, (end - i) * 1000 / 32768, ret);
    i = end;
    ret = 0;
    total = 0;
    wait = 0;
#endif

    /* main loop */
    do {
        bt_os_layer_take_semaphore(bt_task_semaphore);
#ifdef BT_TASK_CONSUME_CHECK
        ret += (int32_t)hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &end);
        wait += end - i;
#endif

#ifdef MTK_BT_TIMER_EXTERNAL_ENABLE
        bt_timer_ext_handle_interrupt();
#endif

        /* handle events */
        if (BT_STATUS_SUCCESS != bt_handle_interrupt()) {
            break;
        }
#ifdef BT_TASK_CONSUME_CHECK
        ret += (int32_t)hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &end);
        total += end - i;
        if (total > (32768 << 3)) {
            if (total > (wait << 3)) {
                bt_task_consume_hci_log(total * 1000/32768, (total - wait) * 100 / total, ret);
            }
            total = 0;
            wait = 0;
        }
        ret = 0;
        i = end;
#endif
    } while (1);
}

/**
 * @brief     It is a user define function for receiving bt task events.
 * @return    None. */
void bt_trigger_interrupt(uint32_t is_from_isr)
{
    if (bt_task_semaphore == 0) {
        return;
    }
	
    /*Judge caller whether come from isr or not adaptively*/
	if( 0 == HAL_NVIC_QUERY_EXCEPTION_NUMBER)
        bt_os_layer_give_semaphore(bt_task_semaphore);
	else 
        bt_os_layer_give_semaphore_from_isr(bt_task_semaphore);

	return;
}

