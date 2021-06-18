/* Copyright Statement:
 *
 */

#ifndef _MTK_HEAPSIZEGUARD_HEADER_
#define _MTK_HEAPSIZEGUARD_HEADER_



/**
 * Register heap size guard 
**/
extern BaseType_t xHeapSizeGuard_Register(TaskHandle_t xTaskHandle);

/**
 * Start heap size guard
 * note1: history statistic data will be cleard 
 * note2: if input NULL,  all tasks heap size guard are started
**/
extern BaseType_t xHeapSizeGuard_Restart(TaskHandle_t xTaskHandle);


/**
 * Stop heap size guard
 * note1: if input NULL, all tasks heap size guard are stoped
**/
extern BaseType_t xHeapSizeGuard_Stop(TaskHandle_t xTaskHandle);


/**
 * Dump heap size guard statistic information
 * note1: if input NULL, all tasks heap size guard statistic info are dumped
**/
extern void vHeapSizeGuard_DumpInfo(TaskHandle_t xTaskHandle);

/**
 * Dump system initialization stage heap size usage information
**/
extern void vHeapSizeGuard_DumpSysInitInfo(void);


#endif /*_MTK_HEAPSIZEGUARD_HEADER_*/
