/* Copyright Statement:
 *
 */

#include "bt_type.h"
#include "bt_debug.h"
#include "syslog.h"

#ifdef __BT_DEBUG__
log_create_module(BT, PRINT_LEVEL_INFO);
log_create_module(BTMM, PRINT_LEVEL_INFO);
log_create_module(BTHCI, PRINT_LEVEL_INFO);
log_create_module(BTL2CAP, PRINT_LEVEL_INFO);
log_create_module(BTRFCOMM, PRINT_LEVEL_INFO);
log_create_module(BTSPP, PRINT_LEVEL_INFO);
//log_create_module(BTIF, PRINT_LEVEL_INFO);
log_control_block_t log_control_block_BTIF={
	"BTIF",
	(DEBUG_LOG_OFF),
	(PRINT_LEVEL_INFO),
	print_module_log,
	dump_module_buffer
};

//#define BT_DEBUG_NO_BTIF
#define BT_DEBUG_BUFF_SIZE  150
static char bt_debug_buff[BT_DEBUG_BUFF_SIZE];
void bt_debug_log(const char *format, ...)
{
    va_list arg;

    if ( 0
#ifdef BT_DEBUG_NO_MM
        || strstr(format, "[MM]")
#endif
#ifdef BT_DEBUG_NO_TIMER
        || strstr(format, "[TIMER]")
#endif
#ifdef BT_DEBUG_NO_HCI
        || strstr(format, "[HCI]")
#endif
#ifdef BT_DEBUG_NO_BTIF
        || strstr(format, "BTIF")
#endif
#ifdef BT_DEBUG_NO_GAP
        || strstr(format, "[GAP]")
#endif
#ifdef BT_DEBUG_NO_A2DP
        || strstr(format, "[A2DP]")
#endif
#ifdef BT_DEBUG_NO_AVDTP
        || strstr(format, "[AVDTP]")
#endif

#ifdef BT_DEBUG_NO_I
        || strstr(format, "[I]")
#endif
#ifdef BT_DEBUG_NO_D
        || strstr(format, "[D]")
#endif
        ) {
        return;
    }

    va_start(arg, format);
    vsnprintf(bt_debug_buff, 150, format, arg);
    va_end(arg);
    if (strstr(bt_debug_buff, "[MM]")) {
        LOG_I(BTMM, "%s", bt_debug_buff);
    } else if (strstr(bt_debug_buff, "[RFCOMM]")) {
        LOG_I(BTRFCOMM, "%s", bt_debug_buff);
    } else if (strstr(bt_debug_buff, "[SPP]")) {
        LOG_I(BTSPP, "%s", bt_debug_buff);
    } else if (strstr(bt_debug_buff, "[L2CAP]")) {
        LOG_I(BTL2CAP, "%s", bt_debug_buff);
    } else if (strstr(bt_debug_buff, "[HCI]")) {
        LOG_I(BTHCI, "%s", bt_debug_buff);
    }  else if (strstr(bt_debug_buff, "[BTIF]")) {
        LOG_I(BTIF, "%s", bt_debug_buff);
    } 
    else {
        LOG_I(BT, "%s", bt_debug_buff);
    }
}

const char *bt_debug_bd_addr2str(const bt_bd_addr_t addr)
{
    snprintf(bt_debug_buff, BT_DEBUG_BUFF_SIZE, "%02x-%02x-%02x-%02x-%02x-%02x",
            addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]);
    return bt_debug_buff;
}

const char *bt_debug_bd_addr2str2(const bt_bd_addr_t addr)
{
    snprintf(bt_debug_buff, BT_DEBUG_BUFF_SIZE, "LAP: %02x-%02x-%02x, UAP: %02x, NAP: %02x-%02x",
            addr[2], addr[1], addr[0], addr[3], addr[5], addr[4]);
    return bt_debug_buff;
}

const char *bt_debug_addr2str(const bt_addr_t *p)
{
    bt_bd_addr_ptr_t addr = p->addr;
    snprintf(bt_debug_buff, BT_DEBUG_BUFF_SIZE, "[%s%s] %02x-%02x-%02x-%02x-%02x-%02x",
            (p->type & 0x01) == BT_ADDR_PUBLIC ? "PUBLIC" : "RANDOM",
             p->type >=2 ?"_IDENTITY":"",
            addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]);
    return bt_debug_buff;
}

const char *bt_debug_addr2str2(const bt_addr_t *p)
{
    bt_bd_addr_ptr_t addr = p->addr;
    snprintf(bt_debug_buff, BT_DEBUG_BUFF_SIZE, "[%s%s] LAP: %02x-%02x-%02x, UAP: %02x, NAP: %02x-%02x",
            (p->type & 0x01) == BT_ADDR_PUBLIC ? "PUBLIC" : "RANDOM",
             p->type >=2 ?"_IDENTITY":"",
            addr[2], addr[1], addr[0], addr[3], addr[5], addr[4]);
    return bt_debug_buff;
}

#endif /* BT_DEBUG */

