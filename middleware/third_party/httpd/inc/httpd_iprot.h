/* Copyright Statement:
 *
 */

#ifndef __HTTPD_IPROT_H__
#define __HTTPD_IPROT_H__

// LIB
#include <stdio.h>

// MT7687
#include "task.h"

// HTTPD
#include "httpd.h"

// interal API
void httpd_set_status(HTTPD_STATUS status);
void httpd_start_handle(void);
void httpd_stop_handle(HTTPD_STOP_REASON reason);
int httpd_fb_status(HTTPD_STATUS status, HTTPD_STOP_REASON reason);

#endif /* __HTTPD_IPROT_H__ */
