/* Copyright Statement:
 *
 */

/**
 * @addtogroup mt2523_hdk mt2523_hdk
 * @{
 * @addtogroup mt2523_hdk_apps apps
 * @{
 * @addtogroup mt2523_hdk_apps_headset_ref_design headset_ref_design
 * @{
 * @addtogroup mt2523_hdk_apps_headset_ref_design_fota fota
 * @{

@par Overview
  - Feature description
    - This feature demonstrates how to use Bluetooth notification
      services to receive FOTA packages and trigger update on the target board.

@par Hardware and software environment
  - Please refer to mt2523_hdk/apps/headset_ref_design/readme.txt.

@par Directory contents
  - Source and header files
    - \b inc/fota:                 FOTA header files.
    - \b src/fota/fota_main.c:     FOTA download manager source code.
    - \b src/fota/fota_bt_common.c:Bluetooth event handler source code.

@par Run FOTA feature
  - Build and Download
    - Please refer to mt2523_hdk/apps/headset_ref_design/readme.txt.
  - Install the application "MediaTek_SmartDevice.apk" located under
    the "sdk_root/tools/smart_device/Android/" folder on an Android
    smartphone and launch the application.
  - Power on the MT2523 HDK.
  - Click "scan" on the smartphone to discover Bluetooth enabled devices,
    then find and connect to the MT2523 HDK.
  - After Bluetooth connection is established, click "Firmware Update(FBIN)" in
    drop-down menu at the top-right corner of the screen.
  - Select the FOTA package file from the smartphone file system, then the
    application will push the FOTA package to MT2523 HDK and start the FOTA
    update process.
  - The update progress is shown in a trace window, the MT2523 HDK will reboot
    automatically after download is complete, reconnect with the smartphone and
    notify the update status to the application.
*/
/**
 * @}
 * @}
 * @}
 * @} */
