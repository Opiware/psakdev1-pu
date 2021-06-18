/* Copyright Statement:
 *
 */
#ifndef __WIFI_FIRMWARE_CLI_H__
#define __WIFI_FIRMWARE_CLI_H__

#ifdef __cplusplus
extern "C" {
#endif


#define WIFI_FW_CLI_ENABLE

#ifdef WIFI_FW_CLI_ENABLE

extern uint8_t mlme_cli(uint8_t len, char *param[]);
#define MLME_CLI_ENTRY     { "fw",   "fw function", mlme_cli },

#else 
#define MLME_CLI_ENTRY
#endif


#ifdef __cplusplus
}
#endif

#endif /* __WIFI_FIRMWARE_CLI_H__ */