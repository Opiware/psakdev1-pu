/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* device.h includes */
#include "mt7687.h"
#include "system_mt7687.h"

#include "sys_init.h"

/* Include this file for CLI engine prototypes definition. */
#include "cli.h"

/* Include this file for I/O interface API default implementation */
#include "io_def.h"

/*	getchar, putchar declaration  */
GETCHAR_PROTOTYPE;
PUTCHAR_PROTOTYPE;

#define HISTORY_LINE_MAX    (128)
#define HISTORY_LINES       (20)

static char s_history_lines[ HISTORY_LINES ][ HISTORY_LINE_MAX ];
static char *s_history_ptrs[ HISTORY_LINES ];

static char s_history_input[ HISTORY_LINE_MAX ];
static char s_history_parse_token[ HISTORY_LINE_MAX ];


/* Example of user custom CLI command, note that the prototype matches cli_cmd_handler_t */
static uint8_t cli_helloworld(uint8_t argc, char *argv[])
{
    printf("Hello world Keil\r\n");
    return 0;
}

/* CLI Command list
   Format:
   {<Command name>, <Command help message>, <Command function>, <Sub command (cmd_t)>}\

   NOTE:
   The last one must be {NULL, NULL, NULL, NULL}
*/
static cmd_t  _cmds_normal[] = {
    { "hello", "hello world", cli_helloworld, NULL },
    /*	Add your custom command here */
    { NULL, NULL, NULL, NULL }
};

/* CLI control block */
static cli_t _cli_cb = {
    .state  = 1,
    .echo   = 0,
    .get    = __io_getchar,
    .put    = __io_putchar,
    .cmd	= &_cmds_normal[0]
};

/* CLI 's FreeRTOS task */
static void cli_def_task(void *param)
{
    for (;;) {
        cli_task();
    }
}

int main(void)
{
    system_init();
    /**
     *  Setup CLI history
     */
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

    /**
     *  Init CLI control block
     */
    cli_init(&_cli_cb);

    /**
     *  Create CLI Task
     */
    xTaskCreate(cli_def_task,
                "cli",
                1024,
                NULL,
                4,
                NULL);
    
 
    

    /* Call this function to indicate the system initialize done. */
    SysInitStatus_Set();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for (;;);
}

