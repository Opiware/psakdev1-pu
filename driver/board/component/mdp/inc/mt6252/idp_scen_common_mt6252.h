/* Copyright Statement:
 *
 */

#if 0 //defined(IDP_MM_COLOR_SUPPORT)
#include <color_api.h>
#include <color_enum.h>
#include <color_structure.h>
#endif
//#include "drv_features.h"

#if defined(IDP_TILE_MODE_SUPPORT)
typedef struct tile_calc_para
{
    /* Tile parameters */
    kal_uint32  tile_bi_sa_src_start_pos[2];  // Input tile start position of bilinear interpolation/source accumulation
    kal_uint32  tile_bi_sa_src_end_pos[2];    // Input tile end position of bilinear interpolation/source accumulation

    kal_uint32  tile_adj_src_start_pos[2];    // Adjust tile_bi_sa_src_start_pos for alignment
    kal_uint32  tile_adj_src_end_pos[2];      // Adjust tile_bi_sa_src_end_pos for alignment
    kal_uint32  tile_src_size_x[2];           // Tile Org width

    kal_uint32  tile_sa_init_weight[2];       // Initial weight of source accumulation
    kal_uint32  tile_start_pos_x[2];          // Input tile start position
    kal_uint32  tile_start_pos_y[2];          // Input tile start position
    kal_uint16  tile_trunc_err_comp_x[2];
    kal_uint16  tile_trunc_err_comp_y[2];
    kal_uint16  tile_init_resid_x[2];         // Initial accumulated residual for truncation error compensation
    kal_uint16  tile_init_resid_y[2];
} tile_calc_para;
#endif

extern kal_bool
idp_common_open_hook(
    idp_owner_t * const owner);

extern kal_bool
idp_common_stop_hook(
    idp_owner_t * const owner);

extern kal_bool
idp_common_start_input_hook(
    idp_owner_t * const owner);

extern kal_bool
idp_common_start_output_hook(
    idp_owner_t * const owner);

extern kal_bool
idp_common_is_busy_hook(
    idp_owner_t const * const owner,
    kal_bool * const busy);

extern kal_bool
idp_common_is_in_use_hook(void);

extern kal_bool
idp_common_query_hook(
    idp_owner_t * const owner,
    va_list ap);

extern kal_bool
idp_dummy_hook(
    idp_owner_t * const owner);

extern void
idp_dummy_hook2(
    idp_owner_t * const owner);

extern kal_bool
idp_dummy_hook3(void);

extern void idp_config_crz_crop(
    kal_uint16 image_src_width,
    kal_uint16 image_src_height,
    kal_uint16 crop_width,
    kal_uint16 crop_height);

#if defined(IDP_TILE_MODE_SUPPORT)
void
idp_bi_tile_calc(
    kal_uint32 src_w, kal_uint32 src_h,
    kal_uint32 tar_w, kal_uint32 tar_h,
    tile_calc_para *tile_result);

void
idp_sa_tile_calc(
    kal_uint32 src_w, kal_uint32 src_h,
    kal_uint32 tar_w, kal_uint32 tar_h,
    tile_calc_para *tile_result);
#endif

// this flag is used to indicate whether MDP triple display buffer is enabled or not
#if defined(MDP_SUPPORT_CP_TRIPLE_DISPLAY_BUFFER)
extern kal_bool _idp_scen_triple_display_buffer_enable;
extern kal_uint32 _idp_scen_display_buffer_addr[3];
extern kal_uint32 _idp_scen_display_buffer_cnt;
#endif

// this buffer used for delay one frame trigger LCD display
#if defined(__ATV_SUPPORT__)
extern kal_uint32 completed_display_buffer_count;
#endif

// this handle is used for mm color control
#if 0 //defined(IDP_MM_COLOR_SUPPORT)
extern COLOR_HANDLE mm_color_handle;
#endif

#if defined(__MTK_TARGET__)
#if defined(__CAMERA_MATV_ESD_RECOVERY_SUPPORT__)
extern volatile kal_bool resz_esd_check_flag;
#endif
#endif

