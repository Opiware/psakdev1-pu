/* Copyright Statement:
 *
 */

/***************************************************************************** 
 * Include
 *****************************************************************************/
#include "gdi_internal.h"
#include "gdi_imgdec_bytestream.h"
#include "gdi_imgdec_internal.h"
#include "gdi_const.h"
#include "gdi_datatype.h"
#include <string.h>
#define GDI_IMGDEC_BYTESTREAM_RAISE(h, ret_code) \
do \
{ \
    if (h->jmpbuf) \
    { \
        /*longjmp(h->jmpbuf, ret_code);*/ \
    } \
} \
while(0)

/*****************************************************************************
 * FUNCTION
 *  gdi_imgdec_bytestream_init
 * DESCRIPTION
 *  Inits IMGDEC.
 * PARAMETERS
 *  handle        [IN]  bitstream handle
 *  src           [IN]  source pointer
 *  size          [IN]  bytestream size
 *  is_file       [IN]  is file
 * RETURNS
 *  Error code.
 *****************************************************************************/
gdi_result_t gdi_imgdec_bytestream_init(gdi_imgdec_bytestream_struct *handle, uint8_t* src, uint32_t size)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    memset(handle, 0, sizeof(gdi_imgdec_bytestream_struct));

    if (size == 0)
    {
        //TODO: not support file.
    }
    else
    {
        handle->buffer = src;
        handle->buffer_ptr = src;
        handle->buffer_ptr_size = size;
        handle->is_from_memory = true;
    }

    return GDI_SUCCEED;
}

/*****************************************************************************
 * FUNCTION
 *  gdi_bytestream_free
 * DESCRIPTION
 *  free a bytestream
 * PARAMETERS
 *  void
 * RETURNS
 *  gdi_result_t, return GDI_SUCCEED if succeed
 *****************************************************************************/
gdi_result_t gdi_imgdec_bytestream_deinit(gdi_imgdec_bytestream_struct *handle)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return GDI_SUCCEED;
}

/*****************************************************************************
 * FUNCTION
 *  gdi_imgdec_bytestream_read
 * DESCRIPTION
 *  Reads bytestream.
 * PARAMETERS
 *  handle       [IN]   bitstream handle
 *  ptr          [OUT]  read buffer
 *  size         [IN]   read size
 * RETURNS
 *  Error code.
 *****************************************************************************/
gdi_result_t gdi_imgdec_bytestream_read(gdi_imgdec_bytestream_struct *handle, void *ptr, uint32_t size)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    gdi_result_t result = GDI_FAILED;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/    
    if (handle->is_from_memory == true)
    {
        // TODO: overflow check
        memcpy(ptr, handle->buffer_ptr, size);
        handle->buffer_ptr += size;

        result = GDI_SUCCEED;
    }
    
    return result;  
}

/*****************************************************************************
 * FUNCTION
 *  gdi_imgdec_bytestream_seek
 * DESCRIPTION
 *  Seeks bitstream.
 * PARAMETERS
 *  handle       [IN]   bitstream handle
 *  offset       [IN]   seek offset
 * RETURNS
 *  Error code.
 *****************************************************************************/
gdi_result_t gdi_imgdec_bytestream_seek(gdi_imgdec_bytestream_struct *handle, int32_t offset)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    gdi_result_t result;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    result = GDI_FAILED;
    if (handle->is_from_memory == true)
    {
        handle->buffer_ptr += offset;
    
        result = GDI_SUCCEED;
    }
    
    return result;
}





