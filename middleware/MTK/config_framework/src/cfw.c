/* Copyright Statement:
 *
 */

#include "cfw_define.h"
#include "cfw.h"
#include "hal_flash.h"
#include "memory_map.h"
#include "syslog.h"

#ifdef __CFW_CONFIG_MODE__
static uint32_t load_address;
static uint8_t  flash_data[4096];
static int32_t cfw_write_flash_int(uint32_t dest, const uint8_t* buff, uint32_t size);
static uint32_t cfw_get_index_by_key(uint16_t key);

int32_t cfw_write_data(uint16_t key, const uint8_t* buff, uint32_t* size)
{
    cfw_data_info_t info;
    info.key = key;
    if (cfw_get_data_info_by_key(&info) != 0) {
        LOG_I(common, "[CFW]cfw_write_data return -1");
        return -1;
    }
    if (info.size < *size) {
        *size = info.size;
    }
    return cfw_write_flash_int((uint32_t)(info.address), buff, *size);
}

static int32_t cfw_write_flash_int(uint32_t dest, const uint8_t* buff, uint32_t size)
{
    int32_t ret;
    uint32_t write = size;
    if ((load_address != 0) && (load_address != (dest & 0xFFFFF000)))
    {
        LOG_I(common, "[CFW]cfw_write_flash_int flush old data");
        ret = cfw_flush();
        if (0 != ret) {
            LOG_I(common, "[CFW]cfw_write_flash_int error");
            return ret;
        }
    }
    if (load_address == 0) {
        //load data.
        LOG_I(common, "[CFW]cfw_write_flash_int load flash data");
        load_address = dest & 0xFFFFF000;
        memcpy(flash_data, (uint8_t*)load_address, sizeof(flash_data));
    }
    if (load_address != ((dest + size) & 0xFFFFF000))
    {
        write = load_address + 0x1000 - dest;
        LOG_I(common, "[CFW]cfw_write_flash_int write part of data %d", write);
        memcpy(flash_data + dest - load_address, buff, write);
        return cfw_write_flash_int(load_address + 0x1000, buff + write, size - write);
    }
    LOG_I(common, "[CFW]cfw_write_flash_int write data %d", write);
    memcpy(flash_data + dest - load_address, buff, write);
    return 0;
}


int32_t cfw_get_data_info_by_key(cfw_data_info_t* info)
{
    uint32_t index;
    if (info->key == 0)
    {
        return -1;
    }
    index = cfw_get_index_by_key(info->key);
    return cfw_get_data_info_by_index(info, index);
}
int32_t cfw_get_data_info_by_index(cfw_data_info_t* info, uint32_t index)
{
    if (index >= CFW_INDEX_DUMMY) {
        return -1;
    }
    info->key = access_table[index].key;
    info->type = access_table[index].type;
    info->size = access_table[index].size;
    info->address = ((uint8_t*)cfw_data_ptr) + access_table[index].offset;
    memcpy(info->var_name, var_name[index], 32);
    return 0;
}

int32_t cfw_flush(void)
{
    hal_flash_status_t ret;
    if (load_address != 0) {
        ret = hal_flash_erase(load_address - BL_BASE, HAL_FLASH_BLOCK_4K);
        if (HAL_FLASH_STATUS_OK != ret) {
            LOG_I(common, "[CFW] erase %x error %d", load_address - BL_BASE, ret);
            return -3;
        }
        ret = hal_flash_write(load_address - BL_BASE, flash_data, sizeof(flash_data));
        if (HAL_FLASH_STATUS_OK != ret) {
            LOG_I(common, "[CFW] flash write %x, size %d error %d", flash_data, sizeof(flash_data), ret);
            return -4;
        }
    }
    load_address = 0;
    return 0;
}

uint32_t cfw_get_max_item_count(void)
{
    return (uint32_t)CFW_INDEX_DUMMY;
}

static uint32_t cfw_get_index_by_key(uint16_t key)
{
    int i;
    for (i = 0; i < CFW_INDEX_DUMMY; i++) {
        if (access_table[i].key == key) {
            break;
        }
    }
    return i;
}
#endif
