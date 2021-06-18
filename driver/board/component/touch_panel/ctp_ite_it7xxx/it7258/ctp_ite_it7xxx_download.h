
/*
 * */
#ifndef __CTP_ITE_IT7XXX_DOWNLOAD_H__
#define __CTP_ITE_IT7XXX_DOWNLOAD_H__

#ifdef MTK_CTP_ENABLE

#include "touch_panel_custom_config.h"
#ifdef CTP_IT7258_SUPPORTED

bool fnFirmwareDownload(void) ;
bool fnDownloadFirmware(uint32_t unFirmwareLength, void *pFirmware) ;
bool fnVerifyFirmware(uint32_t unFirmwareLength, void *pFirmware) ;
bool fnDownloadConfig(uint32_t unConfigLength, void *pConfig) ;
bool fnVerifyConfig(uint16_t unConfigLength, void *pConfig) ;
bool fnEnterFirmwareUpgradeMode(void) ;
bool fnExitFirmwareUpgradeMode(void) ;
bool fnGetFlashSize(uint16_t *pwFlashSize) ;
bool fnSetStartOffset(uint16_t wOffset) ;
bool fnFirmwareReinitialize(void) ;
bool fnWriteFlash(uint32_t unLength, void *pData) ;
bool fnAdvanceWriteFlash(uint32_t unLength, void *pData) ;
bool fnReadFlash(uint32_t unLength, uint32_t unOffset, void *pData) ;
bool fnAdvanceReadFlash(uint32_t unLength, uint32_t unStartOffset, void *pData) ;
bool fnWriteBuffer(uint8_t ucBuffeIndex, uint32_t unLength, void *pData) ;
bool fnReadBuffer(uint8_t ucBuffeIndex, uint32_t unLength, void *pData) ;
bool fnCompareResult(uint32_t unFileLength, uint32_t unStartOffset, void *pFile);

#endif /*CTP_IT7258_SUPPORTED*/
#endif /*MTK_CTP_ENABLE*/

#endif

