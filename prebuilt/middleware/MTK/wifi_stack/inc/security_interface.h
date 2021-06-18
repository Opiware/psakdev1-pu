/* Copyright Statement:
 *
 */

#ifndef __SECURITY_INTERFACE_H__
#define __SECURITY_INTERFACE_H__

typedef void  (*HMAC_MD5_CB)(
    unsigned char Key[],
    unsigned int KeyLen,
    unsigned char Message[],
    unsigned int MessageLen,
    unsigned char MAC[],
    unsigned int MACLen);

typedef void  (* HMAC_SHA1_CB) (
    unsigned char Key[],
    unsigned int KeyLen,
    unsigned char Message[],
    unsigned int MessageLen,
    unsigned char MAC[],
    unsigned int MACLen);

typedef int  (*AES_KEY_WRAP_CB)(
    unsigned char    *PlainText,
    unsigned int     PlainTextLen,
    unsigned char    *Key,
    unsigned int      KeyLen,
    unsigned char   *CipherText,
    unsigned int    *CipherTextLen);

typedef int	 (*AES_KEY_UNWRAP_CB)(
    unsigned char CipherText[],
    unsigned int  CipherTextLength,
    unsigned char Key[],
    unsigned int  KeyLength,
    unsigned char PlainText[],
    unsigned int *PlainTextLength);

typedef int   (* AES_CMAC_CB) (
    unsigned char  PlainText[],
    unsigned int  PlainTextLength,
    unsigned char  Key[],
    unsigned int KeyLength,
    unsigned char  MACText[],
    unsigned int *MACTextLength);
    
typedef struct _SECURITY_INTERFACE
{
    HMAC_MD5_CB   pfHmacMd5;
    HMAC_SHA1_CB  pfHmacSha1;
    AES_KEY_WRAP_CB pfAesKeyWrap;
    AES_KEY_UNWRAP_CB pfAesKeyUnwrap;
    AES_CMAC_CB   pfAesCmac;
}SECURITY_INTERFACE_T;

void RegisterSecurityInterface(SECURITY_INTERFACE_T * ptInterface);

int  CalculatePmk(char *password, unsigned char *ssid, int ssidlength, unsigned char *output) ;

void RT_AES_Decrypt (
    unsigned char *CipherBlock,
    unsigned int CipherBlockSize,
    unsigned char *Key,
    unsigned int KeyLength,
    unsigned char *PlainBlock,
    unsigned int *PlainBlockSize);
#endif /* __SECURITY_INTERFACE_H__ */

