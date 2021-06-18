/* Copyright Statement:
 *
 */

//==============================================================================
//                                INCLUDE FILES
//==============================================================================
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//MT7687
#include <hal_rtc.h>

// HTTPD
#include "os_port.h"
#include "axhttp.h"
#include "cgi.h"

// FreeRTOS
#include "hal_sys.h"

//==============================================================================
//                                    MACROS
//==============================================================================

//==============================================================================
//                               TYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                               Porting from APSoC
//==============================================================================


//==============================================================================
//                               LOCAL VARIABLES
//==============================================================================

//==============================================================================
//                          LOCAL FUNCTION PROTOTYPES
//==============================================================================
static int apConfig(struct cgi_para *para);
static int test2(struct cgi_para *para);

const struct cgi cgi_cmds[]=
{
	{"/apConfig.cgi", &apConfig},
	{"/Test2.cgi", &test2},
};

//==============================================================================
//                              EXTERNAL FUNCTIONS
//==============================================================================
CGI_FUNC cgi_filename_match(char *path_info)
{
    int i;

    HTTPD_DEBUGF((httpd, "[HTTPD] cgi_filename_match() - path_info = %s\n", path_info));

    for (i=0; i< (sizeof(cgi_cmds)/sizeof(struct cgi)) ; i++)
    {
        if (!strcmp(cgi_cmds[i].name, path_info))
        {
            return cgi_cmds[i].func;
        }
    }

    return NULL;
}

static int apConfig(struct cgi_para *para)
{
    char buf[MAXREQUESTLENGTH];

    HTTPD_DEBUGF((httpd, "[HTTPD] apConfig() - sd = %d, cmd = %s, cmd_len = %d\n", para->sd, para->cmd, para->cmd_len));

    snprintf(buf, sizeof(buf),
        "<html><body><h1>apConfig.cgi http response</h1><table><tr><td>cmd = %s</td></tr><tr><td>cmd_len = %d</td></tr></table></body></html>\n",
        para->cmd, para->cmd_len);

    para->func(para->sd, buf, strlen(buf));

    return 0;
}

static int test2(struct cgi_para *para)
{
    char buf[MAXREQUESTLENGTH];
    struct tm gt;
    hal_rtc_time_t r_time;
    char currentTime[32] = "\0";
    const char * format = "%a, %d %b %Y %H:%M:%S GMT";

    HTTPD_DEBUGF((httpd, "[HTTPD] test2() - sd = %d, cmd = %s, cmd_len = %d\n", para->sd, para->cmd, para->cmd_len));

    memset(&gt, 0, sizeof(struct tm));
    if(HAL_RTC_STATUS_OK == hal_rtc_get_time(&r_time))
    {
        gt.tm_year = r_time.rtc_year; // ?
        gt.tm_mon = r_time.rtc_mon; // ?
        gt.tm_mday = r_time.rtc_day;
        gt.tm_wday = r_time.rtc_week;
        gt.tm_hour = r_time.rtc_hour;
        gt.tm_min = r_time.rtc_min;
        gt.tm_sec = r_time.rtc_sec;
        strftime(currentTime, sizeof(currentTime), format, &gt);
    }

    snprintf(buf, sizeof(buf),
        "<html><head></head><body>"
        "<h1>Welcome to Test2.cgi</h1>"
        "<h1>Current system time: %s</h1>"
        "<form id=\"Test\" action=\"Test.html\" method=\"get\"><input type=\"submit\" value=\"Back\" /></form>"
        "</body></html>\n",currentTime
        );

    para->func(para->sd, buf, strlen(buf));

    return 0;
}


