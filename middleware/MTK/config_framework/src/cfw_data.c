/* Copyright Statement:
 *
 */

#include "cfw_define.h"
#include "cfw.h"

#ifdef __CFW_CONFIG_MODE__
#undef CFW_ITEM
#undef CFW_ARRAY_ITEM
#define CFW_ITEM(key, name, type, value) {key, offsetof(cfw_data_struct_t, name), cfw_type_##type,sizeof(type)},
#define CFW_ARRAY_ITEM(key, name, type, size, args...) {key, offsetof(cfw_data_struct_t, name), cfw_type_array_##type,size},
const cfw_access_table_item_t access_table[CFW_INDEX_END] = {
    #include "cfw_item.h"
    {0,0,0,0}
};

#undef CFW_ITEM
#undef CFW_ARRAY_ITEM
#define CFW_ITEM(key, name, type, value) {#name},
#define CFW_ARRAY_ITEM(key, name, type, size, args...) {#name},
const char var_name[CFW_INDEX_END][32] = {
    #include "cfw_item.h"
    {""}
};
#endif

#undef CFW_ITEM
#undef CFW_ARRAY_ITEM
#define CFW_ITEM(key, name, type, value) .name = value,
#define CFW_ARRAY_ITEM(key, name, type, size, args...) .name = args,
const cfw_data_struct_t cfw_data =
{
    #include "cfw_item.h"
};
const cfw_data_struct_t* cfw_data_ptr = &cfw_data;

