/* Copyright Statement:
 *
 */

/**
 * This file contains the root of all CLI commands. They are divided into
 * three modes: NORMAL, TEST, EXAMPLE.
 *
 * Normal and test are enabled by default. TEST mode commands can be turned
 * off by setting MTK_CLI_TEST_MODE_ENABLE to 'n' in feature.mk. Example
 * mode CLI commands can be included by setting MTK_CLI_EXAMPLE_MODE_ENABLE
 * to 'y' in feature.mk. */

/****************************************************************************
 *
 * Header files.
 *
 ****************************************************************************/

#if defined(MTK_MINICLI_ENABLE)


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Kernel includes. */
#include <FreeRTOS.h>
#include <task.h>

#include "cli.h"
#include "cli_def.h"
#include "task_def.h"

#include <toi.h>
#include <type_def.h>
#include <os.h>
#include <os_util.h>

#include "io_def.h"

#include "cli_cmds.h"


GETCHAR_PROTOTYPE;
PUTCHAR_PROTOTYPE;


static cli_t _cli_cb = {
    .state  = 1,
    .echo   = 0,
    .get    = __io_getchar,
    .put    = __io_putchar,
};


/****************************************************************************
 * Private Functions
 ****************************************************************************/


#if !defined(CLI_DISABLE_LINE_EDIT) && !defined(CLI_DISABLE_HISTORY)
#define HISTORY_LINE_MAX    (128)
#define HISTORY_LINES       (5)
#endif /* !CLI_DISABLE_LINE_EDIT && !CLI_DISABLE_HISTORY */


#if !defined(CLI_DISABLE_LINE_EDIT) && !defined(CLI_DISABLE_HISTORY)

static char s_history_lines[ HISTORY_LINES ][ HISTORY_LINE_MAX ];
static char *s_history_ptrs[ HISTORY_LINES ];

static char s_history_input[ HISTORY_LINE_MAX ];
static char s_history_parse_token[ HISTORY_LINE_MAX ];

#endif /* !CLI_DISABLE_LINE_EDIT && !CLI_DISABLE_HISTORY */


/****************************************************************************
 * Public Functions
 ****************************************************************************/


void cli_def_create(void)
{
#if !defined(CLI_DISABLE_LINE_EDIT) && !defined(CLI_DISABLE_HISTORY)
    cli_history_t *hist = &_cli_cb.history;
    int i;

    for (i = 0; i < HISTORY_LINES; i++) {
        s_history_ptrs[i] = s_history_lines[i];
    }
    hist->history           = &s_history_ptrs[0];

    hist->input             = s_history_input;
    hist->parse_token       = s_history_parse_token;
    hist->history_max       = HISTORY_LINES;
    hist->line_max          = HISTORY_LINE_MAX;
    hist->index             = 0;
    hist->position          = 0;
    hist->full              = 0;
#endif /* !CLI_DISABLE_LINE_EDIT && !CLI_DISABLE_HISTORY */

    cli_cmds_init(&_cli_cb);
    cli_init(&_cli_cb);
}


void cli_def_task(void *param)
{
    while (1) {
        cli_task();
    }
}


int cli_task_create(void)
{
    if (xTaskCreate(cli_def_task,
                    MINICLI_TASK_NAME,
                    MINICLI_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
                    NULL,
                    MINICLI_TASK_PRIO,
                    NULL) != pdPASS)
    {
        LOG_E(common, "xTaskCreate fail");
        return -1;
    }

    return 0;
}


#endif /* #if defined(MTK_MINICLI_ENABLE) */

