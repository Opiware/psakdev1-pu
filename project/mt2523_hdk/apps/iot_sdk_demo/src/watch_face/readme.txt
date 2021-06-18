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
 * @addtogroup mt2523_hdk_apps_iot_sdk_demo_watch_face watch_face
 * @{

@par Overview
  - Application description
    - The application implements a watch screen that updates the time in low
      power mode. The time update happens every second by RTC notification.
      The LCM partially updates the time context part. Between the interval
      of the time update, the system enters the low power mode. The system
      wakes up by the RTC notification to enter the normal mode. After
      updating the current time, system enters the low power mode again.

@par Hardware and software environment
  - Supported platform
    - LinkIt 2523 HDK

@par Directory contents
  - Source and header files
    - src/watch_face/watch_face_app.c     Main program
    - src/watch_face/wf_image.c           Digital image arrays of index color
    - inc/watch_face/wf_image.h           Main program header file

@par Run the application
  - Touch "Watch Face" on LCM screen.
  - The power can be measured on this screen.
 * @}
 * @}
 * @}
 * @} */
