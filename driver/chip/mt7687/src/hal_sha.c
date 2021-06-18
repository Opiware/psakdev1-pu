/* Copyright Statement:
 *
 */

#include "hal_sha.h"

#ifdef HAL_SHA_MODULE_ENABLED

#include "stddef.h"
#include "crypt_sha.h"
#include "hal_log.h"
#include "hal_crypt_internal.h"

hal_sha_status_t hal_sha1_init(hal_sha1_context_t *context)
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA1);
    hal_crypt_lock_give();

    return status;
}

hal_sha_status_t hal_sha1_append(hal_sha1_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_error("context is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_error("message is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }

    hal_crypt_lock_take();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA1_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA1);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA1_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA1);
            break;
        }
    }

    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}

hal_sha_status_t hal_sha1_end(hal_sha1_context_t *context, uint8_t digest_message[HAL_SHA1_DIGEST_SIZE])
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_end((SHA1_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA1);
    hal_crypt_lock_give();
    return status;
}

hal_sha_status_t hal_sha224_init(hal_sha224_context_t *context)
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA224);
    hal_crypt_lock_give();

    return status;

}

hal_sha_status_t hal_sha224_append(hal_sha224_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_error("context is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_error("message is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }

    hal_crypt_lock_take();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA224_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA224);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA224_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA224);
            break;
        }
    }

    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}

hal_sha_status_t hal_sha224_end(hal_sha224_context_t *context, uint8_t digest_message[HAL_SHA224_DIGEST_SIZE])
{
    hal_sha_status_t status;
    hal_crypt_lock_take();

    status = crypt_sha_end((SHA224_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA224);

    hal_crypt_lock_give();
    return status;
}

hal_sha_status_t hal_sha256_init(hal_sha256_context_t *context)
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA256);
    hal_crypt_lock_give();

    return status;
}

hal_sha_status_t hal_sha256_append(hal_sha256_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_error("context is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_error("message is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }

    hal_crypt_lock_take();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA256_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA256);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA256_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA256);
            break;
        }
    }

    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}

hal_sha_status_t hal_sha256_end(hal_sha256_context_t *context, uint8_t digest_message[HAL_SHA256_DIGEST_SIZE])
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_end((SHA256_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA256);
    hal_crypt_lock_give();

    return status;
}

hal_sha_status_t hal_sha384_init(hal_sha384_context_t *context)
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA384);
    hal_crypt_lock_give();

    return status;
}

hal_sha_status_t hal_sha384_append(hal_sha384_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_error("context is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_error("message is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }

    hal_crypt_lock_take();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA384_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA384);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA384_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA384);
            break;
        }
    }

    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}

hal_sha_status_t hal_sha384_end(hal_sha384_context_t *context, uint8_t digest_message[HAL_SHA384_DIGEST_SIZE])
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_end((SHA384_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA384);
    hal_crypt_lock_give();

    return status;
}

hal_sha_status_t hal_sha512_init(hal_sha512_context_t *context)
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA512);
    hal_crypt_lock_give();

    return status;
}

hal_sha_status_t hal_sha512_append(hal_sha512_context_t *context, uint8_t *message, uint32_t length)
{

    if (NULL == context) {
        log_hal_error("context is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_error("message is NULL.");
        return HAL_SHA_STATUS_ERROR;
    }

    hal_crypt_lock_take();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA512_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA512);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA512_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA512);
            break;
        }
    }

    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}

hal_sha_status_t hal_sha512_end(hal_sha512_context_t *context, uint8_t digest_message[HAL_SHA512_DIGEST_SIZE])
{
    hal_sha_status_t status;

    hal_crypt_lock_take();
    status = crypt_sha_end((SHA512_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA512);
    hal_crypt_lock_give();

    return status;
}

#endif /* HAL_SHA_MODULE_ENABLED */

