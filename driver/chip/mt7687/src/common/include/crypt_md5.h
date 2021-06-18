/* Copyright Statement:
 *
 */

/**
 * @file crypt_md5.h
 *
 * This file contains the MD5 message-digest algorithm implementation API. */

#ifndef __CRYPT_MD5_H__
#define __CRYPT_MD5_H__

#include "stdint.h"


#ifdef __cplusplus
extern "C" {
#endif

#define MD5_BLOCK_SIZE    64 /**< 512 bits = 64 bytes */
#define MD5_DIGEST_SIZE   16 /**< 128 bits = 16 bytes */

#define MAX_APPEND_LENGTH (256)

extern void delay_time(uint32_t count);

typedef struct {
    uint32_t HashValue[4];
    uint64_t MessageLen;
    uint8_t  *Block;
    uint8_t  Buff[MD5_BLOCK_SIZE];
    uint32_t   BlockLen;
} MD5_CTX_STRUC, *PMD5_CTX_STRUC;


/**
 * @brief  Initial MD5 software structure and hardware setting.
 *
 * @param  [OUT] pMD5_CTX Initial table of MD5 software architecture. */
void crypt_md5_init(MD5_CTX_STRUC *pMD5_CTX);


/**
 * @brief  MD5 Engine.
 *
 * @param  [IN] pMD5_CTX MD5 software architecture. */
void crypt_md5_hash(MD5_CTX_STRUC *pMD5_CTX);


/**
 * @brief The message is appended to block. If block size > 64 bytes, the
 *        MD5_Hash will be called.
 *
 * @param  [IN] pMD5_CTX MD5 software architecture for Hash information.
 * @param  [IN] Message Message context
 * @param  [IN] MessageLen The length of message in bytes */
void crypt_md5_append(MD5_CTX_STRUC     *pMD5_CTX,
                      uint8_t           Message[],
                      uint32_t          MessageLen);


/**
 * @brief  1. Append bit 1 to end of the message.
 *         2. Append the length of message in rightmost 64 bits.
 *         3. Transform the Hash Value to digest message.
 *
 * @param  [IN]  pMD5_CTX MD5 software architecture for Hash information.
 * @param  [OUT] Digest message */
void crypt_md5_end(MD5_CTX_STRUC     *pMD5_CTX,
                   uint8_t           DigestMessage[]);


/**
 * @brief  MD5 entry function
 *
 * @param  [IN] Message         The Message to be hashed.
 * @param  [IN] MessageLen      The length of Message.
 * @param  [OUT] DigestMessage  The Digest of Message. */
int32_t crypt_md5(uint8_t      Message[],
                  uint32_t     MessageLen,
                  uint8_t      DigestMessage[]);


#ifdef __cplusplus
}
#endif

#endif /* __CRYPT_MD5_H__ */
