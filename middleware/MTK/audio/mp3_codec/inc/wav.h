/* Copyright Statement:
 *
 */


#ifndef MP3_WAV_H
#define MP3_WAV_H

#include <stdio.h>  /*for FILE pointer*/


/*********************
     STRUCTURE
*********************/

struct
{
   unsigned char riffheader[4];
   unsigned char WAVElen[4];
   struct
   {
      unsigned char fmtheader[8];
      unsigned char fmtlen[4];
      struct
      {
         unsigned char FormatTag[2];
         unsigned char Channels[2];
         unsigned char SamplesPerSec[4];
         unsigned char AvgBytesPerSec[4];
         unsigned char BlockAlign[2];
         unsigned char BitsPerSample[2]; /* format specific for PCM */
      } fmt;
      struct
      {
         unsigned char dataheader[4];
         unsigned char datalen[4];
         /* from here you insert your PCM data */
      } data;
   } WAVE;
} RIFF =
{  { 'R','I','F','F' } ,{ sizeof(RIFF.WAVE),0,0,0 } ,
   {  { 'W','A','V','E','f','m','t',' ' } , { sizeof(RIFF.WAVE.fmt),0,0,0} ,
      { {1,0} , {0,0},{0,0,0,0},{0,0,0,0},{0,0},{16,0} } ,
      { { 'd','a','t','a' }  , {0,0,0,0} }
   }
};

/*********************
     TABLE
*********************/
static int rates[9] = {
	44100, 48000, 32000,
	22050, 24000, 16000,
	11025, 12000,  8000
};


/*********************
     SUB_FUNCION
*********************/

static void long2littleendian(long inval,unsigned char *outval,int b)
{
  int i;
  for(i=0;i<b;i++) {
    outval[i] = (inval>>(i*8)) & 0xff;
  }
}

int wav_open(int rn, int c, FILE *wavfp)
{
   int bps = 16;

   long2littleendian(c,RIFF.WAVE.fmt.Channels,sizeof(RIFF.WAVE.fmt.Channels));
   long2littleendian(rates[rn],RIFF.WAVE.fmt.SamplesPerSec,sizeof(RIFF.WAVE.fmt.SamplesPerSec));
   long2littleendian((int)(c * rates[rn] * bps)>>3, RIFF.WAVE.fmt.AvgBytesPerSec,sizeof(RIFF.WAVE.fmt.AvgBytesPerSec));
   long2littleendian((int)(c * bps)>>3, RIFF.WAVE.fmt.BlockAlign,sizeof(RIFF.WAVE.fmt.BlockAlign));
   long2littleendian(0,RIFF.WAVE.data.datalen,sizeof(RIFF.WAVE.data.datalen));
   long2littleendian(0+sizeof(RIFF.WAVE),RIFF.WAVElen,sizeof(RIFF.WAVElen));
   fwrite(&RIFF, sizeof(RIFF),1,wavfp);

   return 0;
}

int wav_write(short *buf,int len, FILE *wavfp)
{
   int temp;

   if(!wavfp)
     return 0;

   temp = fwrite(buf, 1, len*2, wavfp);
   if(temp <= 0)
     return 0;

   return temp;
}

int wav_close(FILE *wavfp, int datalen)
{
   if(!wavfp)
      return 0;

   if(fseek(wavfp, 0L, SEEK_SET) >= 0) {
     long2littleendian(datalen,RIFF.WAVE.data.datalen,sizeof(RIFF.WAVE.data.datalen));
     long2littleendian(datalen+sizeof(RIFF.WAVE),RIFF.WAVElen,sizeof(RIFF.WAVElen));
     fwrite(&RIFF, sizeof(RIFF),1,wavfp);
   }
   else {
     fprintf(stderr,"Warning can't rewind WAV file. File-format isn't fully conform now.\n");
   }

   return 0;
}

#endif
