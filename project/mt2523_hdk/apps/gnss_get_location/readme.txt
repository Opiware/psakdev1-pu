/* Copyright Statement:
 *
 */

/**
 * @addtogroup mt2523_hdk mt2523_hdk
 * @{
 * @addtogroup mt2523_hdk_apps apps
 * @{
 * @addtogroup mt2523_hdk_apps_gnss_get_location gnss_get_location
 * @{

@par Overview
  - Application description
    - This is a reference example to design a location based application.
  - Application features
    - This example demonstrates how to use GNSS interface. Note: Since GNSS
      middleware interface only supports single instance, GNSS app task will
      help to forward GNSS commands to the GNSS chip for all other
      applications, such as GNSS bridge task.
    - Things to learn with this application:
      - How to download EPO data through Bluetooth and use this data to
        shorten the time to get the position.
      - How to pass GNSS log to PC through UART interface.
      - How to handle a periodic position update with different time
        durations.
      - For more information, please refer to LinkIt Development
        Platform for RTOS GNSS Developer's Guide.

@par Hardware and software environment
  - Supported platform
    - LinkIt 2523G HDK.
    - Android smartphone (Android OS version 4.0+) for EPO download.
  - Test environment
    - Ensure to run the example in an open area where the line of sight GNSS
      signal can be received. Otherwise, the device will fail to determine
      accurate location information.
  - Environment configuration
    - A serial tool is required, such as Tera terminal, for UART logging.
    - COM port settings. baudrate: 115200, databits: 8, stop bit: 1, parity:
      none and flow control: off.
  - Macro
    - \b MTK_GNSS_ENABLE:  This macro enables the middleware interface usage.
    - \b MTK_GNSS_SUPPORT_EPO_DOWNLOAD_BY_BT:
                           This macro enables EPO feature in this example
                           project.
    - \b GNSS_SUPPORT_TOOL_BRIDGE:
                           Enable this macro to bypass GNSS NMEA log and debug
                           log to UART2 and receive GNSS command from UART.

@par Directory contents
  - Source and header files
    - \b src/epo_demo.c:          Parse EPO data and send related data to GNSS
                                  module.
    - \b src/epo_download.c:      Download EPO data from smartphone via
                                  Bluetooth.
    - \b src/ept_eint_var.c:      EINT configuration generated by EPT tool.
    - \b src/ept_gpio_var.c:      GPIO configuration generated by EPT tool.
    - \b src/gnss_app.c:          Main task for GNSS example.
    - \b src/gnss_bridge_task.c:  The task that communicates with PC to output
                                  logs and receive commands.
    - \b src/gnss_ring_buffer.c:  Ring buffer used to catch debug data.
    - \b src/gnss_timer.c:        Wrapper for freeRTOS timer.
    - \b src/gnss_uart_bridge.c:  Wrapper for UART2 to connect to the PC, used
                                  by GNSS bridge task.
    - \b src/main.c:              Entry function for this example project.
    - \b src/system_mt2523.c:     MT2523x system clock configuration file.
    - \b inc/FreeRTOSConfig.h:    Kernel configuration file.
  - Project configuration files using GCC.
    - \b GCC/Makefile:          Makefile.
    - \b GCC/feature.mk:        Feature configuration.
    - \b GCC/flash.ld:          Linker script.
    - \b GCC/startup_mt2523.s:  Startup file.
    - \b GCC/syscalls.c:        Syscalls for GCC.
  - Project configuration files using Keil.
    - \b MDK-ARM/gnss_get_location.uvprojx:
                             uVision5 project File. Contains the project
                             structure in XML format.
    - \b MDK-ARM/gnss_get_location.uvoptx:
                             uVision5 project options. Contains the settings
                             for the debugger, trace configuration,
                             breakpoints, currently open files, etc.
    - \b MDK-ARM/flash.sct:  Linker script.

@par Run the example
  - Build the example project with the command "./build.sh mt2523_hdk
    gnss_get_location bl" from the SDK root folder and download the binary
    file to LinkIt 2523G HDK.
  - Connect the board to the PC with serial port cable.
  - Run the example. The board starts to search for position.
  - Check the positioning result through system log.
  - Install smart device application on an Android smartphone. The smart
    device application is available at
    [sdk_root]/tools/smart_device/MediaTek_SmartDevice.apk.
  - Make sure Bluetooth is on and the network is available, then launch smart
    device application and connect to LinkIt 2523G HDK.
  - EPO file will be downloaded to LinkIt 2523G HDK automatically.
 * @}
 * @}
 * @}
**/


