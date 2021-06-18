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
 * @addtogroup mt2523_hdk_apps_headset_ref_design_ble_bas_app ble_bas_app
 * @{

@par Overview
  - Feature description
    - This feature demonstrates how to use Battery Profile through Bluetooth
      LE to notify the battery status of the device.

@par Hardware and software environment
  - Please refer to mt2523_hdk/apps/headset_ref_design/readme.txt.

@par Directory contents
  - Source and header files
    - \b inc:                           Common header files.
    - \b inc/ble_bas_app:               BAS header files.
    - \b src/bt_app_common.c:           Bluetooth common source code.
    - \b src/ble_bas_app/ble_bas_app.c: BAS source code.

@par Run the feature
  - Build and Download
    - Please refer to mt2523_hdk/apps/headset_ref_design/readme.txt.
  - Install the application "MediaTek_SmartDevice.apk" located under 
    the "sdk_root/tools/smart_device/Android/" folder on an Android smartphone
    and launch the application.
  - Power on the MT2523 HDK.
  - Click "scan" on the smartphone to discover devices with Bluetooth LE
    using GATT profile, then find and connect to the MT2523 HDK.
  - After Bluetooth LE connection is established, the battery status of
    the MT2523 HDK will be shown in the status bar of the smartphone. The
    status updates with a change in the battery level.

*/
/**
 * @}
 * @}
 * @}
 * @} */
