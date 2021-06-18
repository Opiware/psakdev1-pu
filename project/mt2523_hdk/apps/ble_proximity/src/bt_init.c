/* Copyright Statement:
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "nvdm.h"
#include "bt_system.h"
#include "hal_trng.h"
#include "syslog.h"

#include "project_config.h"
#include <string.h>
#include <stdlib.h>
#include "bt_gap.h"

#include "task_def.h"

#define BT_TIMER_BUF_SIZE (BT_TIMER_NUM * BT_CONTROL_BLOCK_SIZE_OF_TIMER)
#define BT_CONNECTION_BUF_SIZE (BT_CONNECTION_MAX* BT_CONTROL_BLOCK_SIZE_OF_LE_CONNECTION)

bt_gap_config_t ble_pxp_gap_config = {
        .inquiry_mode  = 2, /**< It indicates the inquiry result format.
                                                            0: Standerd inquiry result format (Default).
                                                            1: Inquiry result format with RSSI.
                                                            2: Inquiry result with RSSI format or Extended Inquiry Result(EIR) format. */
        .io_capability = BT_GAP_IO_CAPABILITY_NO_INPUT_NO_OUTPUT,
        .cod           = 0x240404, /* It defines the class of the local device. */
        .device_name   = {"PXP"}, /* It defines the name of the local device with '\0' ending. */
    };

BT_ALIGNMENT4(
static char timer_cb_buf[BT_TIMER_BUF_SIZE]//one timer control block is 20 bytes
);
BT_ALIGNMENT4(
static char connection_cb_buf[BT_CONNECTION_BUF_SIZE]
);

BT_ALIGNMENT4(
static char tx_buf[BT_TX_BUF_SIZE]
);

BT_ALIGNMENT4(
static char rx_buf[BT_RX_BUF_SIZE]
);

bt_bd_addr_t local_public_addr;
extern void bt_task(void * arg);

/**
 * @brief             Common function to print address
 * @param[in] addr    is the address of bluetooth
 * @return            None. */

static void bt_show_address(bt_bd_addr_t addr)
{
 
    LOG_I(common, "[BT addr] [%02X:%02X:%02X:%02X:%02X:%02X]\n", addr[0],
          addr[1], addr[2], addr[3], addr[4], addr[5]);
}

/**
 * @brief             Generate random address for bt static address
 * @param[in]         is the buff to save generated static address
 * @return            None. */
static void bt_preread_local_address(bt_bd_addr_t addr)
{
    nvdm_status_t status;
    int8_t i;
    uint32_t random_seed;
    uint32_t size = 12;
    uint8_t buffer[18] = {0};
    uint8_t tmp_buf[3] = {0};
    bt_bd_addr_t tempaddr = {0};
    hal_trng_status_t ret = HAL_TRNG_STATUS_ERROR;
    if (memcmp(addr, &tempaddr, sizeof(bt_bd_addr_t)) == 0) {
        LOG_I(common, "[BT]Empty bt address after bt_gap_le_get_local_address()\n");
        LOG_I(common, "[BT]Try to read from NVDM.\n");
        status = nvdm_read_data_item("BT", "address", buffer, &size);
        if (NVDM_STATUS_OK == status) {
            LOG_I(common, "[BT]Read from NVDM:%s\n", buffer);
            for (i = 0; i < 6; ++i) {
                tmp_buf[0] = buffer[2 * i];
                tmp_buf[1] = buffer[2 * i + 1];
                addr[i] = (uint8_t)strtoul((char *)tmp_buf, NULL, 16);
            }

            LOG_I(common, "[BT]Read address from NVDM"); 
            bt_show_address(addr);
            return;
        } else {
            LOG_I(common, "[BT]Failed to Read from NVDM:%d.\n", status);
            ret = hal_trng_init();
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BT]generate_random_address--error 1");
            }
            for (i = 0; i < 30; ++i) {
                ret = hal_trng_get_generated_random_number(&random_seed);
                if (HAL_TRNG_STATUS_OK != ret) {
                    LOG_I(common, "[BT]generate_random_address--error 2");
                }
                LOG_I(common, "[BT]generate_random_address--trn: 0x%x", random_seed);
            }
            /* randomly generate address */
            ret = hal_trng_get_generated_random_number(&random_seed);
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BT]generate_random_address--error 3");
            }
            LOG_I(common, "[BT]generate_random_address--trn: 0x%x", random_seed);
            addr[0] = random_seed & 0xFF;
            addr[1] = (random_seed >> 8) & 0xFF;
            addr[2] = (random_seed >> 16) & 0xFF;
            addr[3] = (random_seed >> 24) & 0xFF;
            ret = hal_trng_get_generated_random_number(&random_seed);
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BT]generate_random_address--error 3");
            }
            LOG_I(common, "[BT]generate_random_address--trn: 0x%x", random_seed);
            addr[4] = random_seed & 0xFF;
            addr[5] = (random_seed >> 8) & 0xCF;
            hal_trng_deinit();
        }
    }
    /* save address to NVDM */
    for (i = 0; i < 6; ++i) {
        snprintf((char *)buffer + 2 * i, 3, "%02X", addr[i]);
    }
    LOG_I(common, "[BT]address to write:%s len:%d\n", buffer, strlen((char *)buffer));
    status = nvdm_write_data_item("BT", "address", NVDM_DATA_ITEM_TYPE_STRING, buffer, strlen((char *)buffer));
    if (NVDM_STATUS_OK != status) {
        LOG_I(common, "[BT]Failed to store address.\n");
    } else {
        LOG_I(common, "[BT]Successfully store address to NVDM");
        bt_show_address(addr);
    }
}

/**
 * @brief     This function is prepare all fix memory for BT SDK use.
 * @return    None. */
void bt_mm_init()
{
    bt_memory_init_packet(BT_MEMORY_TX_BUFFER, tx_buf, BT_TX_BUF_SIZE);
    bt_memory_init_packet(BT_MEMORY_RX_BUFFER, rx_buf, BT_RX_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_TIMER, timer_cb_buf, BT_TIMER_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION, connection_cb_buf,
                                  BT_CONNECTION_BUF_SIZE);
}

/**
 * @brief     This function is to config BT SDK fix memory and create task for BT SDK.
 * @return    None. */
void bt_create_task(void)
{
    bt_mm_init();
    log_config_print_switch(BTMM, DEBUG_LOG_OFF);
    log_config_print_switch(BTHCI, DEBUG_LOG_OFF);
    /* bt address should send to BT SDK when create BT task */
    bt_preread_local_address(local_public_addr);
    bt_show_address(local_public_addr);
    /* create task for BT SDK use */
    if (pdPASS != xTaskCreate(bt_task, BT_TASK_NAME, BT_TASK_STACKSIZE/(sizeof(StackType_t)), (void *)local_public_addr, BT_TASK_PRIORITY, NULL)) {
        LOG_E(common, "cannot create bt_task.");
    }
}

/**
 * @brief     This function defined by user, it is used to configure the Bluetooth information.
 * @return    the configuration information supplied by user. */
const bt_gap_config_t* bt_gap_get_local_configuration(void)
{
    return &ble_pxp_gap_config;
}

