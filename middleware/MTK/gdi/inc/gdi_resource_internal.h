/* Copyright Statement:
 *
 */

#ifndef __GDI_RESOURCE_INTERNAL_H__
#define __GDI_RESOURCE_INTERNAL_H__

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "memory_attribute.h"

#define GDI_RESOURCE_4_BYTE_ALIGN ATTR_4BYTE_ALIGN

typedef struct {
    uint8_t *image; /* Customizable Image filenames. */
} gdi_resource_custom_image_t;
#if 0
typedef struct ImageNameList {
    int8_t filename[MAX_FILENAME_LEN];
} IMAGENAME_LIST;
#endif
/* Custom_ImageMap is the mapping array btw image_id & ImageNum. */
typedef struct {
    uint16_t image_number;  /* Index of str in Custom_Image. */
} gdi_resource_custom_image_map_t;

typedef struct {
    uint16_t minimum_image_id; /* Minimum image_id defined by the developer. */
    uint16_t maximum_image_id; /* Maximum image_id defined by the developer. */
    uint16_t index; 	 /* Index of str in Custom_Image. */
} gdi_resource_custom_image_search_map_t;

/* Custom_String is the typedef array of customizable strings. */
typedef uint8_t gdi_resource_custom_string_t;

/* Custom_StringMap is the mapping array btw string_id & StringNum. */

typedef uint32_t gdi_resource_custom_string_map_t;
typedef uint16_t gdi_resource_custom_string_map_16_t;

typedef struct {
    uint16_t minimum_string_id;  /* Minimum StringID defined by the developer. */
    uint16_t maximum_string_id;  /* Maximum StringID defined by the developer. */
    uint16_t map_index;  /* Index of str in Custom_String_MAP. */
} gdi_resource_string_map_search_t;


typedef struct {
    gdi_resource_custom_string_t *string_resource;
    uint16_t total_string_resource;
    void *string_map;
    uint16_t total_string_map; /* for dup str res entry, total_string_map stores the high 16 bits of max offset to non dup strings*/
    gdi_resource_string_map_search_t *string_map_search;
    uint16_t total_string_map_search; /* for dup str res entry, total_string_map_search stores the low 16 bits of max offset to non dup strings */
    bool is16bit;
} gdi_resource_string_resource_list_t;


/**
 * @brief	   This function is used to get image raw data by image id.
 * @param[in] image_id    is the image id which add by resource generator tool flow.
 * @return    uint8_t*        is the image raw data. */
uint8_t *gdi_resource_get_image_data(uint16_t image_id);

/**
 * @brief 	This function is used to get string raw data by string id.
 * @param[in] string_id    is the string id which add by resource generator tool flow.
 * @return	uint8_t*	   is the string raw data. */
uint8_t *gdi_resource_get_string_data(uint16_t string_id);

#endif /* __GDI_RESOURCE_INTERNAL_H__ */
