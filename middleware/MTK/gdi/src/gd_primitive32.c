/* Copyright Statement:
 *
 */

#include "gdi_internal.h"
#include "gdi_datatype.h"
#include "gdi.h"

/*****************************************************************************
 * FUNCTION
 *  gd_color_from_rgb_32
 * DESCRIPTION
 *  
 * PARAMETERS
 *  A       [IN]        
 *  R       [IN]        
 *  G       [IN]        
 *  B       [IN]        
 * RETURNS
 *  
 *****************************************************************************/
gdi_color_t gd_color_from_rgb_32(uint8_t A, uint8_t R, uint8_t G, uint8_t B)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return (gdi_color_t) ((A << 24) | (R << 16) | (G << 8) | B);
}


/*****************************************************************************
 * FUNCTION
 *  gd_color_to_rgb_32
 * DESCRIPTION
 *  
 * PARAMETERS
 *  A       [?]         
 *  R       [?]         
 *  G       [?]         
 *  B       [?]         
 *  c       [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void gd_color_to_rgb_32(uint8_t *A, uint8_t *R, uint8_t *G, uint8_t *B, gdi_color_t c)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    *A = ((uint8_t) (c >> 24));
    *R = ((uint8_t) (c >> 16));
    *G = ((uint8_t) (c >> 8));
    *B = ((uint8_t) (c));
}


/*****************************************************************************
 * FUNCTION
 *  gd_get_pixel_32
 * DESCRIPTION
 *  
 * PARAMETERS
 *  x       [IN]        
 *  y       [IN]        
 * RETURNS
 *  
 *****************************************************************************/
gdi_color_t gd_get_pixel_32(int x, int y)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return (gdi_color_t) * (uint32_t*) (gdi_act_layer->buf_ptr + ((y * gdi_act_layer->width + x) * 4));
}


/*****************************************************************************
 * FUNCTION
 *  gd_put_pixel_32
 * DESCRIPTION
 *  
 * PARAMETERS
 *  x       [IN]        
 *  y       [IN]        
 *  c       [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void gd_put_pixel_32(int x, int y, gdi_color_t c)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    *(uint32_t*) (gdi_act_layer->buf_ptr + ((y * gdi_act_layer->width + x) * 4)) = (uint32_t) c;
}


/*****************************************************************************
 * FUNCTION
 *  gd_put_pixel_to_layer_32
 * DESCRIPTION
 *  
 * PARAMETERS
 *  x       [IN]        
 *  y       [IN]        
 *  c       [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void gd_put_pixel_to_layer_32(gdi_layer_handle_t layer_handle, int x, int y, gdi_color_t c)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    gdi_layer_struct_t *layer = (gdi_layer_struct_t*)layer_handle;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    *(uint32_t*) (layer->buf_ptr + ((y * layer->width + x) * 4)) = (uint32_t) c;
}


/*****************************************************************************
 * FUNCTION
 *  gd_get_buf_pixel_32
 * DESCRIPTION
 *  
 * PARAMETERS
 *  buf_ptr         [?]         
 *  buf_width       [IN]        
 *  x               [IN]        
 *  y               [IN]        
 * RETURNS
 *  
 *****************************************************************************/
gdi_color_t gd_get_buf_pixel_32(uint8_t *buf_ptr, uint32_t buf_width, int x, int y)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return (gdi_color_t) * (uint32_t*) (buf_ptr + ((y * buf_width + x) * 4));
}


/*****************************************************************************
 * FUNCTION
 *  gd_put_buf_pixel_32
 * DESCRIPTION
 *  
 * PARAMETERS
 *  buf_ptr         [?]         
 *  buf_width       [IN]        
 *  x               [IN]        
 *  y               [IN]        
 *  c               [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void gd_put_buf_pixel_32(uint8_t *buf_ptr, uint32_t buf_width, int x, int y, gdi_color_t c)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    *(uint32_t*) (buf_ptr + ((y * buf_width + x) * 4)) = (uint32_t) c;
}


/*****************************************************************************
 * FUNCTION
 *  gd_replace_src_key_32
 * DESCRIPTION
 *  
 * PARAMETERS
 *  dest_ptr            [?]         
 *  dest_pitch          [IN]        
 *  dest_offset_x       [IN]        
 *  dest_offset_y       [IN]        
 *  clipx1              [IN]        
 *  clipy1              [IN]        
 *  clipx2              [IN]        
 *  clipy2              [IN]        
 *  src_key             [IN]        
 *  width               [IN]        
 *  height              [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void gd_replace_src_key_32(
        uint8_t *dest_ptr,
        int32_t dest_pitch,
        int32_t dest_offset_x,
        int32_t dest_offset_y,
        int32_t clipx1,
        int32_t clipy1,
        int32_t clipx2,
        int32_t clipy2,
        gdi_color_t src_key,
        int32_t width,
        int32_t height)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    uint8_t *dest_line_start_ptr;

    int32_t jump_size;
    int32_t start_x, start_y, end;
    int32_t x_draw_count, y_draw_count;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    /* if not totally out of clip region */
    if (!((dest_offset_x > clipx2) ||
          (dest_offset_y > clipy2) || (dest_offset_x + width < clipx1) || (dest_offset_y + height < clipy1)))
    {
        /* find x_draw_count and y_draw_count */
        start_x = (dest_offset_x < clipx1) ? clipx1 : dest_offset_x;
        end = (dest_offset_x + (int32_t) width - 1 > clipx2) ? clipx2 : dest_offset_x + (int32_t) width - 1;
        x_draw_count = end - start_x + 1;

        start_y = (dest_offset_y < clipy1) ? clipy1 : dest_offset_y;
        end = (dest_offset_y + (int32_t) height - 1 > clipy2) ? clipy2 : dest_offset_y + (int32_t) height - 1;
        y_draw_count = end - start_y + 1;

        /* adjust dest ptr to the start of drawing point */
        /* find start ptr for actual drawing */
        jump_size = ((start_y * dest_pitch + start_x) * 32) >> 3;
        dest_line_start_ptr = dest_ptr + jump_size;
        
        {
            uint32_t *dest;
            int32_t x, y;

            for (y = 0; y < y_draw_count; y++)
            {
                dest = (uint32_t*) (dest_line_start_ptr + ((dest_pitch * y * 32) >> 3));

                for (x = 0; x < x_draw_count; x++)
                {
                    uint32_t c = *dest;

                    if (c == src_key)
                    {
                        c ^= 1;
                        *dest = c;
                    }
                    dest++;
                }
            }
        }
    }
}

#define PIXEL_TYPE                  uint32_t
#define PIXEL_BYTES                 4
#define GET_PIXEL(C,PTR)            C=*((PIXEL_TYPE*)(PTR))
#define PUT_PIXEL(C,PTR)            *(PIXEL_TYPE*)(PTR) = (PIXEL_TYPE) C
#define JUMP_PIXEL(PTR,N)           PTR = (((uint8_t*)PTR)+(N)* PIXEL_BYTES)

#define GD_RESIZE_BITBLT            gd_resize_bitblt_32
#define GD_BITBLT                   gd_bitblt_32
#define GD_MEMSET                   gd_memset_32
#define GD_FILL_DOT_RECTANGLE       gd_fill_dot_rect_32
#define GD_IMAGE_BITS_DRAW          gd_image_bits_draw_32
#include "gd_primitive_internal.h"
