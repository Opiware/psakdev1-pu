/* Copyright Statement:
 *
 */

#ifndef MP3DEC_EXP_H
#define MP3DEC_EXP_H
#ifdef __cplusplus
extern "C" {
#endif


#ifndef NULL
#define NULL    0
#endif

/* The error message return by "MP3Dec_Decode()" */
#define NULL_HANDLE             -1
#define NULL_PCM_BUF            -2
#define PCM_BUF_NOT_ALIGNED     -3
#define NULL_BS_BUF             -4
#define NULL_BS_READ            -5
#define BS_BUF_SIZE_INCORRECT   -6
#define FORMAT_NOT_SUPPORT      -7


typedef struct {
    short sampleRateIndex;
    short CHNumber;
    int PCMSamplesPerCH;
} Mp3dec_handle;

/*----------------------------------------------------------------------*/
// FUNCTION
//  MP3Dec_GetVersion
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
int MP3Dec_GetVersion(void);

/*----------------------------------------------------------------------*/
/* Get required buffer size for MP3 Decoder                             */
/*----------------------------------------------------------------------*/
void MP3Dec_GetMemSize(int
                       *Min_BS_size,        /* Output, the required min. Bitsream buffer size in byte*/
                       int *PCM_size,           /* Output, the required PCM buffer size in byte          */
                       int *Working_BUF1_size,   /* Output, the required Working buffer1 size in byte    */
                       int *Working_BUF2_size);  /* Output, the required Working buffer2 size in byte    */


/*----------------------------------------------------------------------*/
/* Get the MP3 decoder handler.                                         */
/*   Return: the handle of current MP3 Decoder                          */
/*----------------------------------------------------------------------*/
Mp3dec_handle *MP3Dec_Init(void
                           *pWorking_BUF1,          /* Input, pointer to Working buffer1  */
                           void *pWorking_BUF2);         /* Input, pointer to Working buffer2  */

/*----------------------------------------------------------------------*/
/* Decompress the bitstream to PCM data                                 */
/*   Return: The consumed data size of Bitsream buffer for this  frame  */
/*----------------------------------------------------------------------*/
int MP3Dec_Decode(Mp3dec_handle
                  *handle,             /* the handle of current MP3 Decoder    */
                  void *pPCM_BUF,                    /* Input, pointer to PCM buffer         */
                  void *pBS_BUF,                     /* Input, pointer to Bitsream buffer    */
                  int BS_BUF_size,                   /* Input, the Bitsream buffer size      */
                  void *pBS_Read);                   /* Input, bitstream buffer read pointer */

/*----------------------------------------------------------------------*/
/* Get the MP3 frame length.                                            */
/*   Return: the frame length (in byte)                                 */
/*----------------------------------------------------------------------*/
unsigned int MP3_GetFrameLengthGeneral(unsigned int header,
                                       unsigned int br_idx);

#ifdef __cplusplus
}
#endif

#endif /*MP3DEC_EXP_H*/
