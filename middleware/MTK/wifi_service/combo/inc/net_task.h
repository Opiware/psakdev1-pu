/* Copyright Statement:
 *
 */

/**
 * Net task API. */
#ifndef __NET_TASK_H__
#define __NET_TASK_H__

#include <stdint.h>

#if defined(__CC_ARM) || defined(__ICCARM__)
#include "type_def.h"
#endif
#include "wifi_freertos_adapter.h"


typedef void (*PNETFUNC)(uint32_t, uint32_t, uint32_t);
typedef void (*PREFFUNC)(void *pkt);

/**
 * @file NetTask API header file.
 *
 * This file declares the callback function types for users hooking their
 * jobs in and let NetTask handling them sequentially. */

/**
 * Net task callback function type.
 *
 * The parameters will be brought back to the function for further process. */
typedef void (net_task_cbk_func_t)(uint32_t, uint32_t, uint32_t);


/**
 * Packet receive callback function handler type declaraion.
 *
 * @retval 1 if packet is handled (consumed)
 * @retval 0 if not handled (not consumed). */
typedef int (net_rx_filter_t)(uint8_t *payload, ssize_t len);


/**
 * Hook a one time callback to NetTask.
 *
 * @param   func    The function to be called by NetTask.
 * @param   arg1    Argument 1 to be passed to func when NetTask calls back.
 * @param   arg2    Argument 2 to be passed to func when NetTask calls back.
 * @param   arg3    Argument 3 to be passed to func when NetTask calls back.
 *
 * @retval  0       The task is scheduled to be executed or has been done.
 * @retval  -1      There is no space to take this task.
 * @retval  -2
 *
 * @note    This function is available only for non-ISR calling.
 * @todo    Provide an ISR version. */
int8_t net_task_add_job(net_task_cbk_func_t *func, uint32_t arg1, uint32_t arg2, uint32_t arg3);


/**
 * Creates NetTask job queue and NetTask itself.
 *
 * Creates NetTask job queue and task. Both were created only once if this
 * function is called more than once.
 *
 * @retval  0   if job queue and task were both created.
 * @retval  -1  if anything goes wrong. */
int8_t net_task_init(void);


/**
 * Set the callback function of raw packets.
 *
 * Set the callback function of raw packets. The raw packets will be forwarded
 * from network-co-processor to the callback 'func' if the indication is turned
 * on using wifi_conf_set_raw_pkt_indication().
 *
 * @param func  The function pointer to be called back. */
void net_task_set_raw_pkt_receiver(net_rx_filter_t *func);


/**
 * Send raw packet to network-co-processor.
 *
 * @param buf [IN] the pointer to the raw packet.
 * @param len [IN] the length of the packet.
 *
 * @retval 0    the raw packet has been queued successfully.
 * @retval -1   buffer allocation failed.
 * @retval -2   if other error occurs. */
int net_task_send_raw_pkt(uint8_t *buf, uint16_t len);


/**
 * Rx EAPOL packet simulation interface (debug and development).
 *
 * This function adds a net task job to simluate a packet rx from network
 * processor.
 *
 * @param connsys_port The port to simulate.
 * @param pkt       The packet content.
 * @param len       Length of pkt. */
void net_task_set_rx_sim(uint8_t connsys_port, uint8_t *pkt, uint16_t len);

os_port_base_type NetTaskInit(void);
os_port_base_type NetJobAddFromTASK(PNETFUNC function, uint32_t arg1, uint32_t arg2);
os_port_base_type NetJobAddFromISR(PNETFUNC function, uint32_t arg1, uint32_t arg2);
unsigned int NetJobGetTaskId(void);

#endif /* __NET_TASK_H__ */
