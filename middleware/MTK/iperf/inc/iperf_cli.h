/* Copyright Statement:
 *
 */

#ifndef __IPERF_CLI_H__
#define __IPERF_CLI_H__

#include <cli.h>


#ifdef __cplusplus
extern "C" {
#endif


#if defined(MTK_MINICLI_ENABLE) && defined(MTK_IPERF_ENABLE)
extern cmd_t iperf_cli[];
#define IPERF_CLI_ENTRY { "iperf", "iperf", NULL, iperf_cli },
#else
#define IPERF_CLI_ENTRY
#endif


#ifdef __cplusplus
}
#endif

#endif /* __IPERF_CLI_H__ */

