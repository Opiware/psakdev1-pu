/* Copyright Statement:
 *
 */

#ifndef	__WEB_CONFIG_H__
#define __WEB_CONFIG_H__
//==============================================================================
//                                INCLUDE FILES
//==============================================================================

//==============================================================================
//                                    MACROS
//==============================================================================

//==============================================================================
//                               TYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                               LOCAL VARIABLES
//==============================================================================
/* specify default page */
//char default_page[]="index.htm";

/* prcoess command page */
char cmd_page[]="do_cmd.htm";

char restart_msg[]=	"<html><script>\nfunction to(){\n"\
					"window.location='/'}\n"\
					"</script>\n<body OnLoad=\"setTimeout('to()',9000)\">System Restart .."\
					"</body></html>\n";

/* customize desired error pages */
err_page error_files[]={
	{403,"duplicate_login.htm"},
	{0, NULL},
};

//==============================================================================
//                          LOCAL FUNCTION PROTOTYPES
//==============================================================================

//==============================================================================
//                              EXTERNAL FUNCTIONS
//==============================================================================

#endif //__WEB_CONFIG_H__


