/* Copyright Statement:
 *
 */

#ifndef __GDI_IMGDEC_INTERNAL_H__
#define __GDI_IMGDEC_INTERNAL_H__

/***************************************************************************** 
 * Include
 *****************************************************************************/
#include "gdi_datatype.h"

/***************************************************************************** 
 * Define
 *****************************************************************************/
//#define GDI_IMGDEC_RAISE(h, ret_code)   longjmp(h->jmpbuf, ret_code)
#define GDI_IMGDEC_RAISE(h, ret_code)

#define GDI_IMGDEC_TRY(h)                     \
   {                                           \
      /*int jmpret;*/                              \
      /* GDI_ASSERT(!gdi_jmpbuf_is_used); */   \
      /* gdi_jmpbuf_is_used = TRUE; */         \
      if (1)                        \
      {
      
#define GDI_IMGDEC_CATCH_BEGIN(h)                     \
      }                                     \
      else                                  \
      {                                     \
         {

#define GDI_IMGDEC_CATCH_END(h)            \
         }                       \
      }                          \
      /* gdi_jmpbuf_is_used = FALSE; */ \
   }

//#define GDI_IMGDEC_CATCH(h, N) if (jmpret == N)
#define GDI_IMGDEC_CATCH(h, N) if (N)

/* clip test utility */
#define GDI_IMGDEC_LAYER_CLIP_RECT_TEST(layer, X1, Y1, X2, Y2, NULL_ACTION)    \
{                                                         \
   if (X1 > X2) { NULL_ACTION; }                          \
   else if (Y1 > Y2)  { NULL_ACTION; }                    \
   else if (X2 < (layer)->clipx1) { NULL_ACTION; }        \
   else if (Y2 < (layer)->clipy1) { NULL_ACTION; }        \
   else if (X1 > (layer)->clipx2) { NULL_ACTION; }        \
   else if (Y1 > (layer)->clipy2) { NULL_ACTION; }        \
   else                                                   \
   {                                                      \
      if (X1 < (layer)->clipx1) { X1 = (layer)->clipx1; } \
      if (Y1 < (layer)->clipy1) { Y1 = (layer)->clipy1; } \
      if (X2 > (layer)->clipx2) { X2 = (layer)->clipx2; } \
      if (Y2 > (layer)->clipy2) { Y2 = (layer)->clipy2; } \
   }                                                      \
}

/* IMGDEC lock */
#define GDI_IMGDEC_HW_LOCK      gdi_imgdec_hw_dec_mutex_take
#define GDI_IMGDEC_HW_UNLOCK    gdi_imgdec_hw_dec_mutex_give

#define GDI_IMGDEC_IS_ABORTED(h)    ((h)->is_aborted && *((h)->is_aborted))

/***************************************************************************** 
 * Typedef
 *****************************************************************************/
#define GDI_IMGDEC_BASE_STRUCT \
    gdi_layer_handle_t  out_layer; \
    uint32_t         flag; \
    bool        *is_aborted;

typedef struct 
{
    GDI_IMGDEC_BASE_STRUCT
} gdi_imgdec_struct;

/***************************************************************************** 
 * Global Function
 *****************************************************************************/
extern void gdi_imgdec_init(void);
extern void gdi_imgdec_hw_dec_mutex_take(void);
extern void gdi_imgdec_hw_dec_mutex_give(void);

#endif /* __GDI_IMGDEC_INTERNAL_H__ */



