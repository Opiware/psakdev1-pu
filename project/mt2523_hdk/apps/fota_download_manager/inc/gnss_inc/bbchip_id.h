/* Copyright Statement:
 *
 */

/*******************************************************************************
 * Filename:
 * ---------
 *  bbchip_id.h
 *
 * Project:
 * --------
 *  Flash Download/Format Library.
 *
 * Description:
 * ------------
 *  Baseband Chip ID module.
 *
 *******************************************************************************/
#ifndef  _ROM_ID_H_
#define  _ROM_ID_H_

//-----------------------------------------------------------------------------
// FAT info
//-----------------------------------------------------------------------------
typedef struct FlashDeviceKey {
    unsigned short m_ManufactureId;
    unsigned short m_DeviceCode;
    unsigned short m_ExtDeviceCode1;
    unsigned short m_ExtDeviceCode2;
} s_FlashDeviceKey;

#endif
