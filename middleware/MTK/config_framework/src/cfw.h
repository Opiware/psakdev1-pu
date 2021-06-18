/* Copyright Statement:
 *
 */

#ifndef __CFW_H__
#define __CFW_H__
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define cfw_type_int8_t           1
#define cfw_type_uint8_t          2
#define cfw_type_int16_t          3
#define cfw_type_uint16_t         4
#define cfw_type_int32_t          5
#define cfw_type_uint32_t         6
#define cfw_type_array_int8_t     7
#define cfw_type_array_uint8_t    8
#define cfw_type_array_char       9

#undef CFW_ITEM
#undef CFW_ARRAY_ITEM
#define CFW_ITEM(key, name, type, value) CFW_INDEX_##key,
#define CFW_ARRAY_ITEM(key, name, type, size, args...) CFW_INDEX_##key,
typedef enum {
#include "cfw_item.h"
    CFW_INDEX_DUMMY,
    CFW_INDEX_END
} cfw_item_index_t;

typedef struct {
    uint16_t key;
    uint16_t offset;
    uint16_t type;
    uint16_t size;
} cfw_access_table_item_t;

typedef struct {
    uint16_t key;
    uint16_t type;
    uint16_t size;
    uint8_t* address;
    char var_name[32];
} cfw_data_info_t;

int32_t cfw_write_data(uint16_t key, const uint8_t* buff, uint32_t* size);
int32_t cfw_get_data_info_by_key(cfw_data_info_t* info);
int32_t cfw_get_data_info_by_index(cfw_data_info_t* info, uint32_t index);
int32_t cfw_flush(void);
uint32_t cfw_get_max_item_count(void);
#ifdef __CFW_CONFIG_MODE__
extern const cfw_access_table_item_t access_table[];
extern const char var_name[CFW_INDEX_END][32];
#endif
#endif
