/* Copyright Statement:
 *
 */

// For Register AT command handler
// System head file
#ifdef MTK_ATCI_CAMERA_ENABLE
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include "at_command.h"
//#include "camera.h"
/*
 * sample code
*/

/*--- Function ---*/
atci_status_t atci_cmd_hdlr_camera(atci_parse_cmd_param_t *parse_cmd);

// AT command handler
atci_status_t atci_cmd_hdlr_camera(atci_parse_cmd_param_t *parse_cmd)
{
}

#endif
