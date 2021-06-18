/* Copyright Statement:
 *
 */

#ifndef __FOTA_DOWNLOAD_INTERFACE_H__
#define __FOTA_DOWNLOAD_INTERFACE_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "type_def.h"

/**
 * Download fota update package by http client. If success, then reboot device and trigger update process. */
extern int8_t fota_download_by_http(char *param);

extern ssize_t fota_download_by_tftp(char *address, char *filename, bool writing,
                              uint32_t partition);


#endif /* __FOTA_DOWNLOAD_INTERFACE_H__ */
