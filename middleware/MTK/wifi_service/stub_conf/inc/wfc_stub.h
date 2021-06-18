/* Copyright Statement:
 *
 */

#ifndef __WFC_STUB_CONF_H__
#define __WFC_STUB_CONF_H__

#include <stdint.h>

#if (MTK_WIFI_STUB_CONF_SPIM_ENABLE || MTK_WIFI_STUB_CONF_SDIO_MSDC_ENABLE)
#include "wifi_host_api.h"
#else
#include "wifi_api.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#define WFC_HRX_POLLING           true
#define WFC_INVALID_OPCODE        0xFFFF
#define WFC_MEMQ_INVALID          0xFFFF
#define WFC_MAGIC_NUM             0x21436587
#define WFC_MAGIC_LEN             4

typedef enum E_WFC_SIM_MODE
{
    WFC_MODE_HIP_SIP  = 1,    //Host Lwip   <--> Slave Lwip
    WFC_MODE_HIP_SWIFI,       //Host Lwip   <--> Slave WIFI
    WFC_MODE_HIP_SBUF,        //Host Lwip   <--> Slave Buffer
    WFC_MODE_HBU_SBUF,        //Host Buffer <--> Slave Buffer            
} T_WFC_SIM_MODE;

//#define WFC_SIM_MODE  WFC_MODE_HIP_SIP
#define WFC_SIM_MODE  WFC_MODE_HIP_SWIFI

typedef enum E_MEMQ_CTRL
{
    MEMQ_CTRL_CMD  = 1,
    MEMQ_CTRL_HOST_TX,
    MEMQ_CTRL_HOST_RX,
    MEMQ_CTRL_SLAVE_EVT,
    MEMQ_CTRL_MAX_NUM
} T_MEMQ_CTRL;

typedef enum E_WFC_CMD_TYPE
{
    WFC_CT_SYSTEM,
    WFC_CT_USER
} T_WFC_CMD_TYPE;


enum E_WFC_CMD
{
    WFC_CMD_WFC_READY,
    WFC_CMD_IP_READY,
    WFC_CMD_OPMODE,
    WFC_CMD_STA_SSID,
    WFC_CMD_STA_PASSWD,
    WFC_CMD_RELOAD,
    WFC_CMD_DTW_DATA,
    WFC_CMD_DTH_READY,
    WFC_CMD_AT,
    WFC_CMD_API,
    WFC_CMD_EVT,
    WFC_CMD_OS_INFO    = 99,
    WFC_CMD_REMOTE_IPERF = 100,
    WFC_CMD_REMOTE_IPERF_CLIENT= 101,
    WFC_CMD_MAX_SUPPORT = 0xFFFF
};


enum E_WFC_EVT
{
    WFC_EVT_WIFI_CONNECTED  = 0x01,
    WFC_EVT_WIFI_DISCONNECT,
    WFC_EVT_IP_READY,
    WFC_EVT_SCAN_RESULTS,
};


enum E_WFC_OPCODE
{        
    WFC_OP_HOST_CMD,
    WFC_OP_DTH_SET,
    WFC_OP_DTH_DATA,
};

/*
enum E_WFC_OPCODE
{
    WFC_OP_WIFI_READY,
    WFC_OP_IP_READY,
    WFC_OP_OPMODE,
    WFC_OP_STA_SSID,
    WFC_OP_STA_PASSWD,
    WFC_OP_RELOAD,
    WFC_OP_STANDBY,
    //WFC_OP_TIMEOUT,
    WFC_OP_DTW_CMD,
    WFC_OP_DTW_DATA,
    WFC_OP_DTH_SET,
    WFC_OP_DTH_READY,
    WFC_OP_DTH_DATA,
    //...............
    WFC_OP_OS_INFO    = 99,
    WFC_OP_REMOTE_IPERF = 100,
    WFC_OP_MAX_SUPPORT = 0xffff,
};
*/

enum E_WFC_RSPCODE
{
    WFC_RSP_OK             = 1,
    WFC_RSP_NO_HRX,    
    WFC_RSP_INVALID_OPCODE,
    WFC_RSP_QUEUE_ERR,
    WFC_RSP_TIMEOUT,
    WFC_RSP_DTH_SET,
    //WFC_RSP_DTH_DATA,
    WFC_RSP_NULL_OS_BUF,
    WFC_RSP_PARAM_ERR,
    WFC_RSP_UNKNOWN_ERR,
    WFC_RSP_DTH_DATA  = 0x8000,
    //......
};

typedef struct S_WFC_QBUF    
{
    uint32_t   ctrl;
    uint32_t   qidx;
    uint32_t   size;   
    uint8_t   *ptr;
    struct S_WFC_QBUF *next; 
} T_WFC_QBUF;


typedef struct S_WFC_CONFIG
{
    uint8_t         type;
    uint16_t        op;
    uint8_t         auto_rsp;
} T_WFC_CONFIG;


typedef struct S_WFC_OPCODE
{
    uint16_t  opcode;
    uint16_t  opcmd;    
    uint16_t *rspcode;
    uint8_t  *txptr;
    uint32_t  txsize;
    uint8_t  *rxptr;
    uint32_t  rxsize;
    uint32_t *rspsize;
    
    T_WFC_CONFIG *pwfg;
    T_WFC_QBUF   qbuf;  
} T_WFC_OPCODE;


typedef struct S_WFC_EVT
{
    uint16_t  eid;
    uint8_t  *param;
    uint32_t  size;
} T_WFC_EVT;

typedef struct S_WFC_IP_OP
{
    uint16_t  opcode;
    uint8_t  *ptr;
    uint32_t  size;     
} T_WFC_IP_OP;


void wfc_stub_init(void);

uint16_t wfcm_to_slave(uint16_t op, uint8_t *ptr, uint32_t ptrSize, uint8_t *rsp, uint32_t *rspSize, uint8_t fromISR);


#ifdef __cplusplus
}
#endif


#endif  /* __WIFI_H__ */
