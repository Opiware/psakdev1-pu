/* Copyright Statement:
 *
 */
#include "gdi_font_engine_internal.h"
#define FONT_DRAW_PATTERN(SET_PIXEL,XFUNC,YFUNC)      \
    {                                                 \
        for(Y2 = 0; Y2 < 8; Y2++) {                   \
            if(pattern&1)                             \
                SET_PIXEL(XFUNC, YFUNC, color);       \
            ++X2;                                     \
            if(X2 == (int32_t)( char_width ) ) {          \
                X1=x;                                 \
                char_height--;                        \
                ++Y1;                                 \
                if(char_height == 0)                  \
                    return ;                          \
                X2=0;                                 \
            } else {                                  \
                ++X1;                                 \
            }                                         \
            pattern >>=1;                             \
        }                                             \
    }
/*****************************************************************************
 * FUNCTION
 *  __GDI_SHOW_CHAR__
 * DESCRIPTION
 *  
 * PARAMETERS
 *  x                   [IN]        
 *  y                   [IN]        
 *  color               [IN]        
 *  font_data           [?]         
 *  font_data_size      [IN]        
 *  char_width          [IN]        
 *  char_height         [IN]        
 *  font_attr           [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
static void __GDI_SHOW_CHAR__(
                int32_t x,
                int32_t y,
                gdi_color_t color,
                uint8_t *font_data,
                uint32_t font_data_size,
                uint16_t char_width,
                uint16_t char_height,
                uint8_t font_attr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int32_t X1, Y1;
    int32_t X2 = 0, Y2;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    X1 = x;
    Y1 = y;
    X2 = 0;

    while (font_data_size--) {
        uint8_t pattern = *font_data++;
        if (!pattern) {
            uint32_t nTemp;
            X2 += 8;
            nTemp = X2 / char_width;
            if (nTemp) {
                Y1 += nTemp;
                char_height -= (uint16_t) nTemp;
                if (!char_height)
                    return;
            }
            X2 %= char_width;
            X1 = x + X2;
        } else {
			if ((font_attr & (FONTATTRIB_ITALIC | FONTATTRIB_OBLIQUE)) == 0)    /* normal font */
                FONT_DRAW_PATTERN(__GDI_SET_PIXEL__, X1, Y1)
            else if (font_attr & FONTATTRIB_ITALIC)
                FONT_DRAW_PATTERN(__GDI_SET_PIXEL__, X1 + (int32_t) gdi_tilt_table[char_height], Y1)
            else    /* if(font_attr&FONTATTRIB_OBLIQUE) */
                FONT_DRAW_PATTERN(__GDI_SET_PIXEL__, X1 + (int32_t) gdi_tilt_table[char_height] / 2, Y1)
        }
	}
}

