/* Copyright Statement:
 *
 */

#ifndef __BL_UART_SW_H__
#define __BL_UART_SW_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BL_SYS_CLK_13MHZ 13000000 /* 13*1000*1000 */
#define BL_SYS_CLK_24MHZ 24000000 /* 24*1000*1000 */
#define BL_SYS_CLK_26MHZ 26000000 /* 26*1000*1000 */

#ifdef __FPGA_TARGET__
#define BL_SYSTEM_CLK_FREQ BL_SYS_CLK_13MHZ
#else
#define BL_SYSTEM_CLK_FREQ BL_SYS_CLK_26MHZ
#endif

void bl_uart_init(uint32_t uart_clk);
void bl_uart_put_byte(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* __BL_UART_SW_H__ */
