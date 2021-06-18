/* Copyright Statement:
 *
 */

/**
 * @file wifi_nvdm_config.h
 * */

#ifndef __NVDM_CONFIG_H__
#define __NVDM_CONFIG_H__


#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#define USER_DATA_MAX_ITEM 6
#define NVDM_DATA_ITEM(X,Y) {X,NVDM_DATA_ITEM_TYPE_STRING,Y,sizeof(Y)}

typedef struct {
    char *item_name;
    nvdm_data_item_type_t data_type;
    char *item_default_value;
    uint32_t item_size;
} group_data_item_t;

typedef struct {
    const char *group_name;
    void (*check_default_value)(void);
    void (*reset_default_value)(void);
    void (*show_value)(void);
} user_data_item_operate_t;

void check_default_value(const char *group_name, const group_data_item_t *group_data_array, uint32_t count);
void reset_to_default(const char *group_name, const group_data_item_t *group_data_array, uint32_t count);
void show_group_value(const char *group_name, const group_data_item_t *group_data_array, uint32_t count);

#ifdef __cplusplus
}
#endif

#endif /* __NVDM_CONFIG_H__ */

