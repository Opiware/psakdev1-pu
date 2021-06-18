/* Copyright Statement:
 *
 */

#ifndef __BL_COMMON_H__
#define __BL_COMMON_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BL_SLIM_UDIV_R(N, D, R) (((R)=(N)%(D)), ((N)/(D)))
#define BL_SLIM_UDIV(N, D) ((N)/(D))
#define BL_SLIM_UMOD(N, D) ((N)%(D))

typedef enum {
    BL_BOOTUP_FAIL_REASON_NONE = 0,
    BL_BOOTUP_FAIL_IN_HW_INIT,
    BL_BOOTUP_FAIL_IN_FOTA_UA
} bl_bootup_status_t;

#define BL_PRINT(x, fmt, arg...)    printf(fmt, ##arg)


typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_CRIT,
    LOG_NONE,
} bl_log_level_t;


void bl_set_debug_level(bl_log_level_t level);
void bl_print(bl_log_level_t level, char *fmt, ...);
void bl_dbg_print(char *fmt, ...);
uint32_t bl_custom_ram_baseaddr(void);
uint32_t bl_custom_rom_baseaddr(void);
uint32_t bl_custom_os_start_address(void);
uint32_t bl_custom_fota_start_address(void);
uint32_t bl_custom_fota_size(void);

extern void JumpCmd(int);/* from startup_bootloader.s */
extern int custom_setSFIExt(void);

#ifdef __cplusplus
}
#endif

#endif /* __BL_COMMON_H__ */
