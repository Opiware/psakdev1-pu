/* Copyright Statement:
 *
 */

#include "hal_gdma_internal.h"

#ifdef HAL_GDMA_MODULE_ENABLED

gdma_transfer_size_format_t gdma_calculate_size(
    uint32_t length,
    uint32_t *count)
{
    if (length == MAX_LENGTH_VALUE) {
        *count = MAX_COUNT_VALUE;
        return GDMA_WORD;
    }
    if (0 == (length % 4)) {
        *count = length / 4;
        return GDMA_WORD;
    } else if (0 == (length % 2)) {
        *count = length / 2;
        return GDMA_HALF_WORD;
    } else {
        *count = length;
        return GDMA_BYTE;
    }

}

#endif /*HAL_GDMA_MODULE_ENABLED*/


