/* Copyright Statement:
 *
 */

#ifndef __GDI_COMMON_LANGUAGE_H__
#define __GDI_COMMON_LANGUAGE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


#include "gdi_common_language.h"
#include "gdi_language_module.h"
#include "gdi_font_engine_internal.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/*****************************************************************************
* Define
*****************************************************************************/

/*****************************************************************************
* Typedef
*****************************************************************************/






/*****************************************************************************
* Extern Global Variable
*****************************************************************************/

/*****************************************************************************
* Extern Global Function
*****************************************************************************/
extern void mmi_lm_common_get_current_cluster(
    uint8_t *start,
    uint8_t *end,
    mmi_lm_cluster_info_p prev2_cluster,
    mmi_lm_cluster_info_p prev_cluster,
    mmi_lm_cluster_info_p curr_cluster,
    bool pos_only);
extern void mmi_lm_common_get_next_cluster(
    uint8_t *start,
    uint8_t *end,
    uint8_t *cursor,
    bool pos_only,
    mmi_lm_cluster_info_p next_cluster);
extern void mmi_lm_common_get_prev_cluster(
    uint8_t *start,
    uint8_t *end,
    uint8_t *cursor,
    bool pos_only,
    mmi_lm_cluster_info_p prev_cluster);

extern void mmi_lm_common_draw_cluster(mmi_lm_show_cluster_param_p param);
extern int32_t mmi_lm_common_cluster_translate(uint16_t *src, uint16_t *dst, int32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __GDI_COMMON_LANGUAGE_H__ */

