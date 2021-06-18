/* Copyright Statement:
 *
 */

#include "hal_md5.h"

#ifdef HAL_MD5_MODULE_ENABLED

#include "stddef.h"
#include "crypt_md5.h"
#include "hal_log.h"
#include "hal_crypt_internal.h"

hal_md5_status_t hal_md5_init(hal_md5_context_t *context)
{
    if (NULL == context) {
        log_hal_error("context is NULL.");
        return HAL_MD5_STATUS_ERROR;
    }

    hal_crypt_lock_take();

    crypt_md5_init((MD5_CTX_STRUC *)context);

    hal_crypt_lock_give();
    return HAL_MD5_STATUS_OK;
}

hal_md5_status_t hal_md5_append(hal_md5_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_error("context is NULL.");
        return HAL_MD5_STATUS_ERROR;
    }

    hal_crypt_lock_take();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_md5_append((MD5_CTX_STRUC *)context, message, MAX_APPEND_LENGTH);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_md5_append((MD5_CTX_STRUC *)context, message, length);
            break;
        }
    }

    hal_crypt_lock_give();
    return HAL_MD5_STATUS_OK;
}

hal_md5_status_t hal_md5_end(hal_md5_context_t *context, uint8_t digest_message[HAL_MD5_DIGEST_SIZE])
{
    if (NULL == context) {
        log_hal_error("context is NULL.");
        return HAL_MD5_STATUS_ERROR;
    }
    if (NULL == digest_message) {
        log_hal_error("digest_message is NULL.");
        return HAL_MD5_STATUS_ERROR;
    }

    hal_crypt_lock_take();

    crypt_md5_end((MD5_CTX_STRUC *)context, digest_message);

    hal_crypt_lock_give();
    return HAL_MD5_STATUS_OK;
}

#endif /* HAL_MD5_MODULE_ENABLED */

