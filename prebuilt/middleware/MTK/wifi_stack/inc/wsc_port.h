/* Copyright Statement:
 *
 */


#ifndef	__WSC_PORT_H__
#define	__WSC_PORT_H__

INT  WscPortGetSsid(UCHAR port, UCHAR * ssid, UCHAR* ssidLen);

INT WscPortGetAuthmode(UCHAR port,USHORT * auth );

INT WscPortGetEncrytype(UCHAR port,USHORT * enc);

INT WscPortGetKeyindex(UCHAR port,UCHAR * keyIndex);

INT WscPortGetKey(UCHAR port,UCHAR * key, USHORT * keyLen);

INT WscPortGetMacAddr(UCHAR port, UCHAR *mac);

INT WscPortSha256(UCHAR hval[], UINT size, const UCHAR data[], UINT len);

VOID WscPortHmacSha256 (const UINT8 Key[], UINT KeyLen, const UINT8 Message[], UINT MessageLen, UINT8 MAC[], UINT MACLen);

VOID  WscPortGenerateDHSecreteKey( UCHAR *ran_buf, INT ran_len,
                           UCHAR *peer_dhkey, INT peer_dhkey_len,
                           UCHAR *secrete_dhkey, INT *secrete_dhkey_len);

VOID  WscPortGenerateDHPublicKey(UCHAR *ran_buf, INT ran_len, 
                                            UCHAR *dhkey, INT *dhkey_len);

VOID  WscPortDecryptData(
    UCHAR *cipherText,  INT ctx_len, 
    UCHAR *key,         UCHAR *iv,
    UCHAR *plainText,   INT *ptx_len);

VOID  WscPortEncryptData(
    UCHAR *plainText,   INT ptx_len,
    UCHAR *key,         UCHAR *iv,
    UCHAR *cipherText,  INT *ctx_len);

#endif	/* __WSC_PORT_H__ */

