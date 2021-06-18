/* Copyright Statement:
 *
 */

#include "gdi_internal.h"
#include <string.h>
#include "gdi.h"
#include "gdi_lcd.h"
#include "gdi_layer.h"
#include "gdi_datatype.h"
#include "gdi_primitive.h"
#include "FreeRTOS.h"
#include <stdio.h>
/*****************************************************************************
 * FUNCTION
 *  gdi_init
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
uint32_t GDI_DEBUG_FLAG;
uint32_t GDI_DEBUG_CNT;
uint8_t GDI_DEBUG_ARG[32];

uint32_t GDI_LCD_WIDTH;
uint32_t GDI_LCD_HEIGHT;
//kal_eventgrpid gdi_event_group;

#define GDI_MEM_CACHELINE_SIZE 32
#define GDI_MEM_MAX_EXT_ALLOCATOR_NUM 2

typedef struct
{
    gdi_mem_allocate_func alloc;
    gdi_mem_free_func free;
    uint32_t min_addr, max_addr;
} gdi_mem_allocator_struct;

static struct
{
    volatile int32_t num;
    //gdi_mutex_struct mutex;
    gdi_mem_allocator_struct allocator[GDI_MEM_MAX_EXT_ALLOCATOR_NUM];
} gdi_mem_external;

static void gdi_mem_init(void)
{
    gdi_mem_external.num = 0;
    //gdi_mutex_init(&gdi_mem_external.mutex);
}

/*****************************************************************************
 * FUNCTION
 *  gdi_alloc_ext_mem
 * DESCRIPTION
 *  
 * PARAMETERS
 *  size        [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void *gdi_alloc_ext_mem_ext(int32_t size, uint8_t location)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    void *p = NULL;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/   

    p = pvPortMalloc(size);

    return p;
}


/*****************************************************************************
 * FUNCTION
 *  gdi_free_ext_mem_ext
 * DESCRIPTION
 *  
 * PARAMETERS
 *  pointer     [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void gdi_free_ext_mem_ext(void **pointer)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    vPortFree(*pointer);

    *pointer = NULL;
}

static bool is_gdi_init = false;
void gdi_init(uint32_t width, uint32_t height, gdi_color_format_t color_format, uint8_t *buffer)
{
    GDI_LOG("gdi_init\n");
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    GDI_ENTER_CRITICAL_SECTION(gdi_init)
    if(!is_gdi_init)
    {
        GDI_LOG("real gdi_init\n");
        /* set flag to true avoid re-init */
        is_gdi_init = true;
        GDI_LCD_WIDTH = width;
        GDI_LCD_HEIGHT = height;
        GDI_DEBUG_FLAG = 0;
        gdi_mem_init();

        /* init lcd */
        gdi_lcd_init();

        /* init layer */
        gdi_layer_init(color_format, buffer);

        /* set the default ABM source layer to the main LCD base layer */
        gdi_set_alpha_blending_source_layer(GDI_LAYER_MAIN_BASE_LAYER_HANDLE);

    }
    GDI_EXIT_CRITICAL_SECTION(gdi_init)
}

gdi_color_t gdi_get_color_from_argb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
{
    gdi_color_t c = gdi_act_color_from_rgb(alpha, red, green, blue);
    return c;
}

void gdi_get_argb_from_color(uint8_t *alpha, uint8_t *red, uint8_t *green, uint8_t *blue, gdi_color_t color)
{
    gdi_act_color_to_rgb(alpha, red, green, blue, color);
}
