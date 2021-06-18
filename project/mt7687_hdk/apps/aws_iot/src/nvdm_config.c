/* Copyright Statement:
 *
 */

#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "nvdm.h"
#include "syslog.h"
#include "type_def.h"
#include "nvdm_config.h"


void check_default_value(const char *group_name, const group_data_item_t *group_data_array, uint32_t count)
{
    uint8_t buffer[1024] = {0};

    for (uint32_t index = 0; index < count; index++) {
        uint32_t buffer_size = 1024;
        nvdm_status_t status = nvdm_read_data_item(group_name,
                               group_data_array[index].item_name,
                               buffer,
                               &buffer_size);
        if (NVDM_STATUS_OK != status) {
            {
                status = nvdm_write_data_item(group_name,
                                              group_data_array[index].item_name,
                                              group_data_array[index].data_type,
                                              (uint8_t *)group_data_array[index].item_default_value,
                                              group_data_array[index].item_size);
                if (NVDM_STATUS_OK != status) {
                    LOG_I(common, "write to [%s]%s error", group_name, group_data_array[index].item_name);
                }
            }
        }
    }
}

void reset_to_default(const char *group_name, const group_data_item_t *group_data_array, uint32_t count)
{
    for (uint32_t index = 0; index < count; index++) {
        nvdm_status_t status;
        {
            status = nvdm_write_data_item(group_name,
                                          group_data_array[index].item_name,
                                          group_data_array[index].data_type,
                                          (uint8_t *)group_data_array[index].item_default_value,
                                          group_data_array[index].item_size);
            if (NVDM_STATUS_OK != status) {
                LOG_I(common, "write to [%s]%s error", group_name, group_data_array[index].item_name);
            }
        }
    }
}

void show_group_value(const char *group_name, const group_data_item_t *group_data_array, uint32_t count)
{
    uint8_t buffer[1024] = {0};
    for (uint32_t index = 0; index < count; index++) {
        uint32_t buffer_size = 1024;
        nvdm_status_t status = nvdm_read_data_item(group_name,
                               group_data_array[index].item_name,
                               buffer,
                               &buffer_size);
        if (NVDM_STATUS_OK == status) {
            printf("[%s]%s: %s\r\n", group_name, group_data_array[index].item_name, (char *)buffer);
        } else {
            printf("read from [%s]%s error.\r\n", group_name, group_data_array[index].item_name);
        }
    }
}

static user_data_item_operate_t user_data_item_operate_array[USER_DATA_MAX_ITEM] = {{0}};

extern user_data_item_operate_t wifi_data_item_operate_array[];
extern user_data_item_operate_t network_data_item_operate_array[];
#ifdef MTK_WIFI_CONFIGURE_FREE_ENABLE
extern user_data_item_operate_t config_free_data_item_operate_array[];
#endif
#ifdef MTK_HOMEKIT_ENABLE
extern user_data_item_operate_t homekit_data_item_operate_array[];
#endif

int32_t nvdm_register_module(user_data_item_operate_t *data_item_array,uint8_t group_num)
{
    uint32_t index;
    for (index = 0; index < USER_DATA_MAX_ITEM; index++) {
        if(user_data_item_operate_array[index].group_name == NULL)
            break;
    }
    if((USER_DATA_MAX_ITEM - index)>= group_num) {
        memcpy(user_data_item_operate_array + index,data_item_array, group_num*sizeof(user_data_item_operate_t));
        return 0;
    }else {
        LOG_E(common,"user_data_item_operate_array is not enough.");
        return -1;
    }
}

/* This function is used to check whether data is exist in NVDM region,
 * and write default value to NVDM region if no value can be found in NVDM region. */
void user_check_default_value(void)
{
    uint32_t index;
    nvdm_register_module(wifi_data_item_operate_array,3);
    nvdm_register_module(network_data_item_operate_array,1);
#ifdef MTK_WIFI_CONFIGURE_FREE_ENABLE
    nvdm_register_module(config_free_data_item_operate_array,1);
#endif
#ifdef MTK_HOMEKIT_ENABLE
    nvdm_register_module(homekit_data_item_operate_array,1);
#endif

    for (index = 0; index < USER_DATA_MAX_ITEM; index++) {
        if(user_data_item_operate_array[index].group_name != NULL)
            user_data_item_operate_array[index].check_default_value();
    }
}

void user_data_item_reset_to_default(char *group_name)
{
    uint32_t index;
    uint32_t max = sizeof(user_data_item_operate_array) / sizeof(user_data_item_operate_t);

    if (group_name == NULL) {
        for (index = 0; index < max; index++) {
            if(user_data_item_operate_array[index].group_name != NULL)
              user_data_item_operate_array[index].reset_default_value();
        }
    } else {
        for (index = 0; index < max; index++) {
            if (memcmp(user_data_item_operate_array[index].group_name, group_name,
                       strlen(user_data_item_operate_array[index].group_name)) == 0) {
                user_data_item_operate_array[index].reset_default_value();
                break;
            }
        }
    }
}

void user_data_item_show_value(char *group_name)
{
    uint32_t index;
    uint32_t max = sizeof(user_data_item_operate_array) / sizeof(user_data_item_operate_t);

    if (group_name == NULL) {
        for (index = 0; index < max; index++) {
            if(user_data_item_operate_array[index].group_name != NULL)
                user_data_item_operate_array[index].show_value();
        }
    } else {
        for (index = 0; index < max; index++) {
            if (memcmp(user_data_item_operate_array[index].group_name, group_name,
                       strlen(user_data_item_operate_array[index].group_name)) == 0) {
                user_data_item_operate_array[index].show_value();
                break;
            }
        }
    }
}


