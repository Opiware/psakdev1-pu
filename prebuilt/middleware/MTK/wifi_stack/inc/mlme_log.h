/* Copyright Statement:
 *
 */


#ifndef __MLME_LOG_H_
#define __MLME_LOG_H_

/* MLME_DBG_ON  this is controled by each c file which wanted to print the log

    #define LOG_PRE_FIX   "[module name]"
    #define MLME_DBG_INFO_ON 1
    #define MLME_DBG_API_ON 1
    #define MLME_DBG_ERR_ON 1
    #include "mlme_log.h"
    
*/

#define useSYSLOG

#ifdef useSYSLOG

#ifndef LOG_PRE_FIX
#define  LOG_PRE_FIX "[MLME]"
#endif

#if(MLME_DBG_INFO_ON == 1) 
    #define MLME_DBG_INFO(_fmt,...)    LOG_I(fw_interface,LOG_PRE_FIX""_fmt,##__VA_ARGS__)
#else
    #define MLME_DBG_INFO(_fmt,...)
#endif

#if(MLME_DBG_API_ON == 1) 
    #define MLME_DBG_API(_fmt,...)     LOG_I(fw_interface,LOG_PRE_FIX""_fmt,##__VA_ARGS__)
#else
    #define MLME_DBG_API(_fmt,...)
#endif

#if(MLME_DBG_ERR_ON == 1) 
    #define MLME_DBG_ERR(_fmt,...)     LOG_E(fw_interface,LOG_PRE_FIX""_fmt,##__VA_ARGS__)
#else
    #define MLME_DBG_ERR(_fmt,...)
#endif


#if(MLME_RAW_DBG_ON == 1) 
    #define MLME_RAW_DBG(_fmt,...)     printf(_fmt,##__VA_ARGS__)
#else
    #define MLME_RAW_DBG(_fmt,...)
#endif

#else


extern int g_mlme_current_dbg_level;

#ifndef LOG_PRE_FIX
#define  LOG_PRE_FIX "[MLME]"
#endif

#define MLME_DBG_LEVEL_API   1
#define MLME_DBG_LEVEL_INFO  2
#define MLME_DBG_LEVEL_ERR   3
#define MLME_DBG_LEVEL_NONE  4

#if(MLME_DBG_INFO_ON == 1) 
    #define MLME_DBG_INFO(_fmt,...)     MLME_DBG_LEVEL_INFO < g_mlme_current_dbg_level? 0 : printf(LOG_PRE_FIX"%s,%d [INFO] "_fmt,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
    #define MLME_DBG_INFO(_fmt,...)
#endif

#if(MLME_DBG_API_ON == 1) 
    #define MLME_DBG_API(_fmt,...)     MLME_DBG_LEVEL_API < g_mlme_current_dbg_level? 0 : printf(LOG_PRE_FIX"%s,%d [API] "_fmt,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
    #define MLME_DBG_API(_fmt,...)
#endif

#if(MLME_DBG_ERR_ON == 1) 
    #define MLME_DBG_ERR(_fmt,...)     MLME_DBG_LEVEL_ERR < g_mlme_current_dbg_level? 0 : printf(LOG_PRE_FIX"%s,%d [ERROR!!!] "_fmt,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
    #define MLME_DBG_ERR(_fmt,...)
#endif
#endif //ifdef useSYSLOG
#endif
