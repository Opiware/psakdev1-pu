/* Copyright Statement:
 *
 */

#ifndef __CFW_DEFINE_H__
#define __CFW_DEFINE_H__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#ifdef SCT_KEY_EVENT_ENABLE
#include "sct_key_cfw.h"
#endif

#undef CFW_ITEM
#undef CFW_ARRAY_ITEM
#define CFW_ITEM(key, name, type, value) type name;
#define CFW_ARRAY_ITEM(key, name, type, size, args...) type name[size];

typedef struct {
#ifdef __CFW_CONFIG_MODE__
    uint8_t begin[4096];
#endif
#include "cfw_item.h"
#ifdef __CFW_CONFIG_MODE__
    uint8_t end[4096];
#endif
} cfw_data_struct_t;
extern const cfw_data_struct_t* cfw_data_ptr;
#define CFW_CFG_ITEM_VALUE(name) (cfw_data_ptr->name)

#endif
