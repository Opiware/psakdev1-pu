/* Copyright Statement:
 *
 */

#ifndef __SIE_H__
#define __SIE_H__

#include <stdint.h>

/** @file sie.h contains the API prototype declaration for Secure IE. */

typedef enum {
    SIE_VALIDATE_SUCCESS,
    SIE_VALIDATE_FAILURE
} sie_validate_t;


typedef struct sie_request_s {
    uint8_t nonce[4];
} sie_request_t;


typedef struct sie_respone_s {
    uint8_t     nonce[4];
    uint16_t    payload_len;
    uint8_t     payload[0];
} sie_response_t;


/**
 * Create one SecureIE request payload.
 *
 * @return The pointer of the allocated SecureIE request payload. NULL if
 *         memory allocation failed. */
sie_request_t *sie_request_init(void);


/**
 * Destroy one SecureIE request payload.
 *
 * @param request   The pointer to a SecureIE payload previously allocated
 *                  by sie_request_init(). */
void sie_request_deinit(sie_request_t *request);


/**
 * Create one SecureIE response payload.
 *
 * During the creation of the SecureIE response payload, the nonce from
 * request is used.
 *
 * @return The pointer of the allocated SecureIE response payload. NULL if
 *         memory allocation failed.
 *
 * @note The returned response payload is encrypted. */
sie_response_t *sie_response_init(sie_request_t   *request,
                                  uint8_t         *payload,
                                  uint16_t        payload_len);


/**
 * Destroy one SecureIE response payload.
 *
 * @param response      The pointer to a SecureIE payload previously
 *                      allocated by sie_response_init().
 * @param response_len The length of response. */
void sie_response_deinit(sie_response_t *response,
                         uint16_t       response_len);


/**
 * Decrypt and validate a SecureIE response payload.
 *
 * @param response      The pointer to a SecureIE payload previously
 *                      allocated by sie_response_init().
 * @param response_len  The length of response.
 * @param request       The pointer to a SecureIE request payload to be
 *                      used to validate response.
 *
 * @retval SIE_VALIDATE_SUCCESS The decryption and validation succeeded.
 * @retval SIE_VALIDATE_FAILURE The decryption and validation failed. */
sie_validate_t sie_response_decrypt(sie_response_t  *response,
                                    uint16_t        reponse_len,
                                    sie_request_t   *request);

#endif /* __SIE_H__ */
