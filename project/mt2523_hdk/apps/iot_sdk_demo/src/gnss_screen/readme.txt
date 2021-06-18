/* Copyright Statement:
 *
 */

/**
 * @addtogroup mt2523_hdk mt2523_hdk
 * @{
 * @addtogroup mt2523_hdk_apps apps
 * @{
 * @addtogroup mt2523_hdk_apps_iot_sdk_demo iot_sdk_demo
 * @{
 * @addtogroup mt2523_hdk_apps_iot_sdk_demo_gnss_screen gnss_screen
 * @{

@par Overview
  - Application description
    - This is a simple GNSS application with UI display. It demonstrates the
      usage of GNSS module APIs.
  - Application features
    - This application shows how to send commands to GNSS module and recieve
      and parse NMEA data from the module.
    - UI display shows GNSS positioning information, such as longitude,
      latitude, etc.
  - Result
    - Positioning information on UI display.

@par Hardware and software environment
  - Please refer to the readme document on
    project/mt2523_hdk/apps/iot_sdk_demo.

@par Directory contents
  - Source and header files
    - \b src/gnss_screen/epo_demo.c:
      EPO sample code.
    - \b src/gnss_screen/gnss_app.c:
      GNSS app task.
    - \b src/gnss_screen/gnss_demo_screen.c:
      GNSS UI and NMEA data parser.
    - \b src/gnss_screen/gnss_ring_buffer.c:
      Ring buffer for further usage.
    - \b src/gnss_screen/gnss_timer.c:
      RTOS timer wrapper.
  - Project configuration files using GCC
    - \b GCC/gnss_screen.mk:  Makefile.

@par Run the GNSS application
  - Build this application with the command "./build.sh mt2523_hdk
    iot_sdk_demo bl" from the SDK root folder.
  - Download the binary file to LinkIt 2523 HDK.
  - Power on LinkIt 2523 HDK.
  - Press "GNSS demo" menu item to enter GNSS screen.
  - GNSS screen will show "No fix" at the beginning when GNSS receiver just
    starts working.
  - Wait for a few minutes under open sky, the latitude and longitude will be
    shown after the GNSS acquires the positioning information successfully.
  - Press "Exit" button to exit the GNSS Screen.
 * @}
 * @}
 * @}
 * @} */
