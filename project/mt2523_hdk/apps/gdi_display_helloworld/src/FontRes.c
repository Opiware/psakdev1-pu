/* Copyright Statement:
 *
 */
#include "gdi_font_resource.h"
#include "gdi_font_engine.h"

#include "L_English_small.h"
#include "L_gMTKProprietaryFont_small.h"

const sCustFontData * const g_small_font_data_array[] = {
&English_small,
&gMTKProprietaryFont_small
}; 

const sCustFontData * const g_medium_font_data_array[] = {
&English_small,
&gMTKProprietaryFont_small
}; 

const sCustFontData * const g_large_font_data_array[] = {
&English_small,
&gMTKProprietaryFont_small
}; 

const font_group_struct g_fontfamily[MAX_FONT_SIZE] = {
{2, g_small_font_data_array},
{2, g_medium_font_data_array},
{2, g_large_font_data_array},
};
const uint8_t g_fontfamily_count = 3 ;

