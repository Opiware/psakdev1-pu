/* Copyright Statement:
 *
 */

#ifndef __SYSLOG_CLI_H__
#define __SYSLOG_CLI_H__


#include <stdint.h>

#include "syslog.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(MTK_MINICLI_ENABLE)
#include "cli.h"
extern cmd_t syslog_cli[];
#endif

#if defined(MTK_SAVE_LOG_AND_CONTEXT_DUMP_ENABLE)

/**
 * @brief     This function switch syslog from uart mode to flash mode
 * @param[in] len  the char num ,default should be 1.
 * @param[in] param[]  the paremeter array, the paramter is that on or off.
 * @return    default success 0
 * @par       Example
 * Sample code, swith to flash mode syslog_switch(1,"on"); */

extern void syslog_switch_cmds(uint8_t len, char *param[]);
#endif

uint8_t syslog_cli_set_filter  (uint8_t len, char *param[]);
uint8_t syslog_cli_show_config (uint8_t len, char *param[]);


#define SYSLOG_CLI_ENTRY    { "log", "log control",     syslog_cli_show_config, syslog_cli },


#ifdef __cplusplus
}
#endif


#endif /* __SYSLOG_CLI_H__ */

