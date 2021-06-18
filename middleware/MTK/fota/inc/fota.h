/* Copyright Statement:
 *
 */

#ifndef __FOTA_API_H__
#define __FOTA_API_H__
#include "stdint.h"
#ifdef FOTA_FS_ENABLE
#include "bl_fota.h"
#include "stdbool.h"
#endif
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *@addtogroup FOTA
 *@{
 * This section introduces the FOTA interface APIs including terms and acronyms, supported features, software architecture, details on how to use this interface, FOTA function groups, enums, structures and functions.
 * This interface writes into a pre-defined register flag. The bootloader enters the update process based on the value written in the flag. The return error code indicates if the flag is written successfully or not. 
 * After the update is complete, the UA automatically resets the register flag.
 * Note, it is recommended to call the reboot API after calling the FOTA interface, because fota_trigger_update() does not contain reboot functionality.
 * There is no dedicated FOTA read or write SDK API, it is suggested to use HAL flash SDK API to write data to specified address of flash.
 * Regarding to the FOTA update flow & usage, please refer to the Firmware Update Developers Guide located under [sdk_root]/doc folder.
 *
 *
 * @section Terms_Chapter Terms and acronyms
 *
 * |Terms                   |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b FOTA                       | Firmware Over-The-Air (FOTA) is a Mobile Software Management technology in which the operating firmware of a mobile device is wirelessly upgraded and updated by its manufacturer. Please refer to <a href="https://www.techopedia.com/definition/24236/firmware-over-the-air-fota"> FOTA in Techopedia.</a>|
 * |\b UA                         | Update Agent performs the actual FOTA update on devices. It operates as stand-alone application in bootloader and replaces the old firmware with the new one.|
 * |\b TFTP                       | Trivial File Transfer Protocol (TFTP) is a simple, lockstep, File Transfer Protocol which allows a client to get from or put a file onto a remote host. One of its primary uses is in the early stages of nodes booting from a local area network. For an introduction to TFTP, please refer to <a href="https://en.wikipedia.org/wiki/Trivial_File_Transfer_Protocol"> TFTP in Wikipedia.</a>|
 *
 *@} */

#ifdef MTK_FOTA_ON_7687
/**
 * @addtogroup FOTA
 * @{
 * @section FOTA_Architechture_Chapter Software Architecture of FOTA
 * MTK MT7687 provides command line to operate FOTA functionality. It also offers a reference example with details on how to download using Wi-Fi, enable TFTP client on the MT7687 target device and setup a TFTP server to share a FOTA package file. Then MT7687 device completes the downloads with the specified input command.
 * @image html fota_mt7687_arch.png
 *
 *@} */
#else
/**
 * @addtogroup FOTA
 * @{
 * @section FOTA_Architechture_Chapter Software Architecture of FOTA
 * MTK MT2523 provides a reference design using FOTA package downloads. The supporting connectivity between Android application package and MT2523 HDK is Bluetooth. It enables transferring packages from the file system of smartphones over FOTA to the MT2523 HDK. Then MT2523 device writes the data from the file to the specified, pre-defined partition.
 * @image html fota_mt2523_arch.png
 *
 *@} */
#endif

/**
  * @addtogroup FOTA
  * @{
  * @defgroup fota_enum Enums
  * @{
  */

/** @brief
 * FOTA trigger update result definition */
typedef enum
{
    FOTA_TRIGGER_FAIL = -1,      /**< Failed to write the FOTA register flag. */
    FOTA_TRIGGER_SUCCESS = 0     /**< The FOTA register flag is successfully written. */
}fota_ret_t;

/**
  * @}
  */

/**
 * @brief
 * Provide the register flag for the bootloader to check whether to enter FOTA update process or not.
 *
 * @return FOTA_TRIGGER_SUCCESS/FOTA_TRIGGER_FAIL.
 * @note Call the reboot API after using this function.
 * @par
 * @code
 *     //Trigger a FOTA update.
 *     fota_ret_t ret;
 *     ret = fota_trigger_update();
 *     if (ret < FOTA_TRIGGER_SUCCESS)
 *     {
 *         // Failed to write the register flag, error handling.
 *     }
 *     // Call the reboot API, hal_wdt_software_reset().
 * @endcode */
fota_ret_t fota_trigger_update(void);

#ifdef FOTA_FS_ENABLE

/**
 * @brief
 * Get the bootloader FOTA update result information, and clear the update results.
 * @return   whether the update information is successfully got.
 * @input    bl_fota_update_info_t
 * @output   bl_fota_update_info_t */
bool readAndClearBlFotaUpdateInfo(bl_fota_update_info_t* pInfo);

/**
 * @brief
 * check whether the FOTA is executed in bootloader.
 * @return   true: FOTA is executed in bootloader when power up.
 * @input    no
 * @output   no */
bool isFotaExecuted(void);

/**
  * @}
  */
#endif
#ifdef __cplusplus
}
#endif
#endif /* __FOTA_API_H__ */

