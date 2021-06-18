/* Copyright Statement:
 *
 */
#include "gdi_common_language.h"

/*****************************************************************************
* Define
*****************************************************************************/
typedef struct {
    uint16_t input_char[2];
    uint16_t output_char;
} mmi_lm_latin_ligature_table, *mmi_lm_latin_ligature_table_p;

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


/*****************************************************************************
 * FUNCTION
 *  mmi_lm_common_get_current_cluster
 * DESCRIPTION
 *
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void mmi_lm_common_get_current_cluster(
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
    uint16_t curch, prevch;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    //printf("mmi_lm_common_get_current_cluster\n");
    curr_cluster->is_gap = MMI_LM_CLUSTER_ATTR_GAP;
    curch = MMI_LM_GET_CHARACTER_FROM_BUFFER(start);
    start += MMI_LM_CHARACTER_SIZE;
    curr_cluster->data_len = 1;

    curr_cluster->display_buffer[0] = curch;
    curr_cluster->display_buffer[1] = 0;
    //printf("mmi_lm_common_get_current_cluster, %s, %x, %x\n", curr_cluster->display_buffer, curr_cluster->display_buffer[0], curr_cluster->display_buffer[1]);
    curr_cluster->cluster_len = 1;

    if (!pos_only) {
        if (curr_cluster->lang_id == prev_cluster->lang_id) {
            if (MMI_LM_TEST_PREV_CONNECT(curch)) {
                curr_cluster->is_connect = MMI_LM_CLUSTER_ATTR_CONNECT;
            } else {
                prevch = MMI_LM_GET_CHARACTER_FROM_BUFFER(prev_cluster->data_ptr);
                if (MMI_LM_TEST_BACK_CONNECT(prevch) ||
                        ( MMI_LM_TEST_ALPHABETIC_CHAR(curch) &&
                          (!MMI_LM_TEST_WORD_WRAPPING_BREAK_CHARACTER(prevch) && MMI_LM_TEST_ALPHABETIC_CHAR(prevch)))) {
                    curr_cluster->is_connect = MMI_LM_CLUSTER_ATTR_CONNECT;
                }
            }
        }
        mmi_fe_query_single_cluster(prev_cluster, curr_cluster);
    }
    //printf("mmi_lm_common_get_current_cluster end\n");
}

/*****************************************************************************
 * FUNCTION
 *  mmi_lm_common_draw_cluster
 * DESCRIPTION
 *
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void mmi_lm_common_draw_cluster(mmi_lm_show_cluster_param_p param)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    mmi_fe_show_one_cluster_param_struct fe_param;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    fe_param.string = (uint8_t *)(&(param->cluster->display_buffer));
    fe_param.len = param->cluster->cluster_len;
    fe_param.baseline = param->baseline;
    fe_param.bordered = param->bordered;
    fe_param.x = param->x;
    fe_param.y = param->y;
    fe_param.langid = param->cluster->lang_id;
    fe_param.subarray_start = 0;
    fe_param.subarray_len = fe_param.len;
    //printf("mmi_lm_common_draw_cluster\n");
    mmi_fe_show_single_cluster(&fe_param);

}



