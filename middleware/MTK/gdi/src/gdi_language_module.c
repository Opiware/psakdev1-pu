/* Copyright Statement:
 *
 */


/*****************************************************************************
*  Include
*****************************************************************************/
#include "gdi_common_language.h"
#include "gdi_language_module.h"
#include "gdi_font_engine_internal.h"
#include <assert.h>

/*****************************************************************************
* Define
*****************************************************************************/

/******************************************************************************
* External Global variables
***************************************************************************** */

/******************************************************************************
* External Global Functions
***************************************************************************** */

/******************************************************************************
* Global variables
***************************************************************************** */

/*****************************************************************************
* Local Variables
*****************************************************************************/


/*****************************************************************************
* Local Function
*****************************************************************************/
static void mmi_lm_get_current_cluster_int(
    uint8_t *start,
    uint8_t *end,
    mmi_lm_cluster_info_p prev2_cluster,
    mmi_lm_cluster_info_p prev_cluster,
    mmi_lm_cluster_info_p curr_cluster,
    bool pos_only);






/*****************************************************************************
 * FUNCTION
 *  mmi_lm_get_current_cluster
 * DESCRIPTION
 *  To get cluster information
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void mmi_lm_get_current_cluster(
    uint8_t *start,
    uint8_t *end,
    mmi_lm_cluster_info_p prev2_cluster,
    mmi_lm_cluster_info_p prev_cluster,
    mmi_lm_cluster_info_p curr_cluster)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    mmi_lm_get_current_cluster_int(start, end, prev2_cluster, prev_cluster, curr_cluster, false);
}




/*****************************************************************************
 * FUNCTION
 *  mmi_lm_get_current_cluster_int
 * DESCRIPTION
 *  To get cluster info
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
static void mmi_lm_get_current_cluster_int(
    uint8_t *start,
    uint8_t *end,
    mmi_lm_cluster_info_p prev2_cluster,
    mmi_lm_cluster_info_p prev_cluster,
    mmi_lm_cluster_info_p curr_cluster,
    bool pos_only)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_lm_lang_enum lang_id;
    uint16_t curCh = 0;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    curCh = (uint16_t)MMI_LM_GET_CHARACTER_FROM_BUFFER(start);
    lang_id = (curCh == 0x0) ? MMI_LM_LANG_NONE : MMI_LM_LANG_OTHERS;
    //printf("mmi_lm_get_current_cluster_int, curCh %x, lang_id %d\n", curCh, lang_id);
    curr_cluster->data_ptr = start;
    curr_cluster->lang_id = lang_id;

    if (lang_id == MMI_LM_LANG_NONE) {
        curr_cluster->data_len = curr_cluster->cluster_len = 1;
        curr_cluster->display_buffer[0] = 0;
        curr_cluster->adv_x = 0;
        curr_cluster->adv_y = 0;
        curr_cluster->w = 0;
        curr_cluster->h = 0;
        curr_cluster->rx = 0;
        curr_cluster->ry = 0;
        curr_cluster->bx = 0;
        curr_cluster->by = 0;
        curr_cluster->is_gap = MMI_LM_CLUSTER_ATTR_GAP;
        curr_cluster->is_connect = MMI_LM_CLUSTER_ATTR_DISCONNECT;
        //printf("mmi_lm_get_current_cluster_int, end with LANG NONE\n");
        return;
    }

    /*
     * special process for different behavior between editor and font engine.
     * editor pass unshaping string but font engine passed shaping string into languagemodule.
     * for arabic present form, we would not treat as arabic character becuase we don't want to do shaping twice.
     * but we still have to treat it as arabic cluster.
     */
    if (prev_cluster->lang_id != curr_cluster->lang_id) {
        curr_cluster->is_gap = MMI_LM_CLUSTER_ATTR_GAP;
    }
    mmi_lm_common_get_current_cluster(
        start,
        end,
        prev2_cluster,
        prev_cluster,
        curr_cluster,
        pos_only);
    //printf("mmi_lm_get_current_cluster_int\n");
}


/*****************************************************************************
 * FUNCTION
 *  mmi_lm_draw_cluster
 * DESCRIPTION
 *
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void mmi_lm_draw_cluster(mmi_lm_show_cluster_param_p param)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_lm_cluster_info_p cluster;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    cluster = param->cluster;
    if (cluster->cluster_len == 0 || cluster->lang_id == MMI_LM_LANG_NONE) {
        return;
    }
    
    //printf("mmi_lm_draw_cluster\n");
    mmi_lm_common_draw_cluster(param);
}



