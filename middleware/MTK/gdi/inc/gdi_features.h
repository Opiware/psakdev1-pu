/* Copyright Statement:
 *
 */
#ifndef _GDI_FEATURES_H_
#define _GDI_FEATURES_H_

#define DRV_LAYER_TOTAL_COUNT 4

//#define GDI_USING_MUTEX
#define GDI_USING_LAYER
#define GDI_4_LAYERS
#define GDI_LAYER_HW_LAYER_COUNT       DRV_LAYER_TOTAL_COUNT
#define GDI_LAYER_TREE_MAX_DEPTH       8

/*
 * general layer information */
#define GDI_LAYER_CLIP_STACK_COUNT        (8)
#define GDI_LAYER_ACT_LAYER_STACK_COUNT   (8)
#define GDI_LAYER_OFFSET    0
#define GDI_LAYER_LAYER_COUNT          (12)
#define GDI_LAYER_TOTAL_LAYER_COUNT GDI_LAYER_LAYER_COUNT

#define GDI_USE_RGB565_TO_SHOW_BW

#endif /* _GDI_FEATURES_H_ */

