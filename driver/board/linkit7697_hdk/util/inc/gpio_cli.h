/* Copyright Statement:
 *
 */

#ifndef __GPIO_CLI_H__
#define __GPIO_CLI_H__


#include "cli.h"


#ifdef __cplusplus
extern "C" {
#endif


extern cmd_t gpio_cli_cmds[];


#define GPIO_CLI_ENTRY      {"gpio_cli", "gpio get and set", NULL, gpio_cli_cmds},


#ifdef __cplusplus
}
#endif


#endif /* __GPIO_CLI_H__ */

