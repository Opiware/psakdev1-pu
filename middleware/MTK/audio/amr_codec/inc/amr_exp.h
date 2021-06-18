/* Copyright Statement:
 *
 */

/*******************************************************************************
 *
 * Filename:
 * ---------
 *   amr_exp.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *   AMR codec interface API
 *
 * Author:
 * -------
 *   Stan Huang
 *
 *------------------------------------------------------------------------------
 * $Revision:$ 1.0.0
 * $Modtime:$  
 * $Log:$
 * 
 * 07 27 2012 luke.liu
 * [WCPSP00000684] [Audio][SWIP]AMR_NB modification
 * [VERSION 0.02]
 * 07/25/2012
 *         - 1. Modify for static library
 *         - 2. Remove symbols for security
 *         - 3. Use CHECK_MTK_HW_2 for SWIP protection
 *
 * 06 22 2012 luke.liu
 * [WCPSP00000684] [Audio][SWIP]AMR_NB modification
 * [VERSION 0.01]
 * 06/21/2012
 *         - 1. Merge WCP1 and WCP2 code
 *         - 2. Release for TV Project, add get version
 *
 *
 *******************************************************************************/

#ifndef AMR_CODEER_DOT_H
#define AMR_CODEER_DOT_H

#ifdef __cplusplus
extern "C"{
#endif 
/*
********************************************************************************
*                         INCLUDE FILES
********************************************************************************
*/
 
/*
********************************************************************************
*                         DEFINITION OF DATA TYPES
********************************************************************************
*/

typedef enum { BR475 = 0,
               BR515,            
               BR59,
               BR67,
               BR74,
               BR795,
               BR102,
               BR122,            
	            BRDTX	    
             }AMR_BitRate;

/*****************************************************************************
 * STRUCTURE
 *  AMR_ENC_HANDLE
 *
 * DESCRIPTION
 *  AMR encoder handler
 *
 * MEMBERS
 *  amr_enc_data   Encoder internal data pointer (these data can't be release during encoding process)
 *  BitRate         Encoder bitrate
 *  dtx_enable      DTX enable or not (1:enable, 0:disable) 
 *
 ***************************************************************************** */
typedef struct {
   void *amr_enc_data;
   int dtx_enable;    
   AMR_BitRate BitRate;
}AMR_ENC_HANDLE;

/*****************************************************************************
 * STRUCTURE
 *  AMR_DEC_HANDLE
 *
 * DESCRIPTION
 *  AMR decoder handler
 *
 * MEMBERS
 *  amr_dec_data    Decoder internal data pointer (these data can't be release during decoding process)
 *
 ***************************************************************************** */
typedef struct {
   void *amr_dec_data;
}AMR_DEC_HANDLE;
 
 
/*
********************************************************************************
*                         DECLARATION OF PROTOTYPES
********************************************************************************
*/
 
/*****************************************************************************
 * FUNCTION
 *  AMREnc_GetBufferSize
 *
 * DESCRIPTION
 *  This function gets the buffers size for encoder.
 *
 * PARAMETERS
 *  int_buf_size    [o] Internal buffer size
 *  tmp_buf_size    [o] Temporary buffer size
 *  bits_buf_size   [o] Bitstream buffer size
 *  pcm_buf_size    [o] Speech PCM buffer size 
 *
 * RETURNS
 *  None
 *
 ***************************************************************************** */
void AMREnc_GetBufferSize(
   unsigned int *int_buf_size,
   unsigned int *tmp_buf_size,
   unsigned int *bs_buf_size,
   unsigned int *pcm_buf_size   
);
/*****************************************************************************
 * FUNCTION
 *  AMRDec_GetBufferSize
 *
 * DESCRIPTION
 *  This function gets the buffers size for decoder.
 *
 * PARAMETERS
 *  int_buf_size    [o] Internal buffer size
 *  tmp_buf_size    [o] Temporary buffer size
 *  bits_buf_size   [o] Bitstream buffer size 
 *  pcm_buf_size    [o] Speech PCM buffer size
 *
 * RETURNS
 *  None
 *
 ***************************************************************************** */
void AMRDec_GetBufferSize(
   unsigned int *int_buf_size,
   unsigned int *tmp_buf_size,
   unsigned int *bs_buf_size,   
   unsigned int *pcm_buf_size
);


/*****************************************************************************
 * FUNCTION
 *  AMREnc_Init
 *
 * DESCRIPTION
 *  This function initialize the buffer for encoder.
 *
 * PARAMETERS
 *  int_buffer  [i] Encoder internal buffer pointer. This buffer can¡¦t be re-used by other application.
 *  dtx         [i] Supported DTX or not (1:enable, 0:disable).
 *  BitRate     [i] Bitrate of AMR codec
 * 	 
 * RETURNS
 *  the pointer of AMR encoder handler
 *
 ***************************************************************************** */
AMR_ENC_HANDLE *AMREnc_Init(
   void *int_buffer,
   AMR_BitRate BitRate,
   int dtx   
);

/*****************************************************************************
 * FUNCTION
 *  AMRDec_Init
 *
 * DESCRIPTION
 *  This function initialize the buffer for decoder.
 *
 * PARAMETERS
 *  int_buffer    [i] Decoder internal buffer pointer. This buffer can¡¦t be re-used by other application.
 *
 * RETURNS
 *  the pointer of AMR decoder handler
 *
 ***************************************************************************** */
AMR_DEC_HANDLE *AMRDec_Init(
   void *int_buffer
);


/*****************************************************************************
 * FUNCTION
 *  AMR_Encode
 *
 * DESCRIPTION
 *  This function encodes one frame pcm data (160 samples/frame) and output AMR bitstream.
 *
 * PARAMETERS
 *  amr_enc_handle  [i] the pointer of AMR encoder handle
 *  tmp_buffer      [i] Temporary buffer pointer. Temporary buffer could be used by other application after encoding a frame.  
 *  pcm_buffer      [i] Input PCM sample buffer pointer (input 160 samples pcm data)   
 *  bs_buffer       [o] Output bitstream buffer pointer
 *  bitrate         [i] AMR Encoder bitrate 
 *
 * RETURNS
 *  Bitstream length in byte
 *
 *
 ***************************************************************************** */
 
int AMR_Encode(
   AMR_ENC_HANDLE *amr_enc_handle,
   void *tmp_buffer,
   short *pcm_buffer,
   unsigned char *bs_buffer, 
	AMR_BitRate bitrate						
);


/*****************************************************************************
 * FUNCTION
 *  AMR_Decode
 *
 * DESCRIPTION
 *  This function decodes AMR bitstream and output 160 samples pcm data.
 *
 * PARAMETERS
 *  amr_dec_handle  [i] The pointer of AMR decoder handle  
 *  tmp_buffer      [i] Temporary buffer pointer. Temporary buffer could be used by other application after encoding a frame.
 *  pcm_buffer      [o] Output PCM sample buffer pointer (output 160 samples pcm data)   
 *  bs_buffer       [i] Input bitstream buffer pointer 
 *  quality_bit     [i] Q-bit (i.e. BFI)
 *  frame_type      [i] frame type (i.e. AMR mode)
 *
 * RETURNS
 *  None  
 *
 ***************************************************************************** */
 
void AMR_Decode(
   AMR_DEC_HANDLE *amr_dec_handle,
   void *tmp_buffer,
   short *pcm_buffer,	
   unsigned char *bs_buffer,
	unsigned char quality_bit,
	unsigned char frame_type      
); 
 

/*----------------------------------------------------------------------*/
// FUNCTION
//  AMR_GetVersion
//
// DESCRIPTION
//  This function was used to get current version of library
//
// RETURNS
//  B31-B24:  Project Type
//  B23-B16:  Compiler and Major Version
//  B15-B08:  Minor Version
//  B07-B00:  Release Version
//
/*----------------------------------------------------------------------*/
int AMR_GetVersion(void);


 
 
#ifdef __cplusplus
}
#endif 
#endif


