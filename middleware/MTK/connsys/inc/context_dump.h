/* Copyright Statement:
 *
 */

/**
 * @file context_dump.h
 *
 *  connsys dump related function.
 * */
#ifndef __CONTEXT_DUMP_H__
#define __CONTEXT_DUMP_H__

#include "stdint.h"

#if defined (MTK_SAVE_LOG_AND_CONTEXT_DUMP_ENABLE)

/* dump n9 task definition */
#define DUMP_TASK_NAME             "dump_trigger_task"
#define DUMP_TASK_STACKSIZE        (512*4)
#define DUMP_TASK_PRIORITY         TASK_PRIORITY_NORMAL

#define SHARE_MEM_START_ADDR   (0x2003EC00)
#define SHARE_MEM_LENGTH       (0x1000)

typedef enum {
    DUMP_TRIGGER_SRC_CM4_BT,
    DUMP_TRIGGER_SRC_CM4_WIFI,
    DUMP_TRIGGER_SRC_CM4_N9_HEART,
    DUMP_TRIGGER_SRC_N9_SELFCHECK_CRASH
} dump_para_trigger_source_t;

typedef enum {
    DUMP_PARA_TYPE_MINI,
    DUMP_PARA_TYPE_FULL
} dump_para_type_t;

typedef enum {
    DUMP_PROCESS_FLAG_READY_FOR_WRITE,
    DUMP_PROCESS_FLAG_WRITING,
    DUMP_PROCESS_FLAG_FIN_WRITING
} dump_para_process_flag_t;

typedef struct _connsys_dump_parameters{
    uint8_t trigger_source;           /*BT/WIFI/N9 heart/N9 crash*/
    uint8_t dump_type;                /*mini dump/full dump*/
    uint8_t process_flag;             /*ready for write/finish writing*/
    uint8_t mem_reseted;              /**/
    uint32_t dump_start_addr;         /*N9 use*/
    uint32_t dump_len;                /*N9 use*/
    uint32_t reserved;
} connsys_dump_parameter_t;

/**
 * @brief  dump init.
 *
 * @return 
 * */
void context_dump_init(void);

/**
* @brief process dump interrupt 
*
* @return  >=0 means success, <0 means fail
*/
int32_t context_dump_intr_receive_process(void);

/**
 * @brief  trigger dumop n9 process.
 *
 * @param  *dump_param [IN] dump parameters .
 *
 * @return =0 means successful, <0 means fail.
 * */
int8_t context_dump_trigger(connsys_dump_parameter_t *dump_param);

/**
 * @brief  trigger dumop n9 process use semaphore.
 *
 * @param  *dump_param [IN] dump parameters .
 *
 * @return =0 means successful, <0 means fail.
 * */
int8_t context_dump_trigger_by_sema(connsys_dump_parameter_t *dump_param);

/**
* @brief get dump status
*
* @return  =0 means dumped, 1 means dumping, -1 means no dump cmd
*/
int8_t context_dump_status(void);

/**
 * @brief  dump debug info.
 * *
 * @return 
 * */
void context_dump_n9_debug(void);

/**
 * @brief  set inband cmd no rsp count.
 * *
 * @return 
 * */
void context_dump_set_inband_cmd_no_rsp_cnt( uint8_t rsp_cnt);

/**
 * @brief  get inband cmd no rsp count.
 * *
 * @return inband cmd no rsp count
 * */
uint8_t context_dump_get_inband_cmd_no_rsp_cnt(void);

#endif

#endif
