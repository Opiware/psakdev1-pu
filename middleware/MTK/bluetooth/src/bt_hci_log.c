/* Copyright Statement:
 *
 */

#include <bt_hci_log.h>
#include "hal_uart.h"
//#include "hci_log.h"

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_hci_log_enabled=_default_bt_hci_log_enabled")
#pragma comment(linker, "/alternatename:_hci_log_cmd=_default_hci_log_cmd")
#pragma comment(linker, "/alternatename:_hci_log_event=_default_hci_log_event")
#pragma comment(linker, "/alternatename:_hci_log_acl_out=_default_hci_log_acl_out")
#pragma comment(linker, "/alternatename:_hci_log_acl_in=_default_hci_log_acl_in")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__ARMCC_VERSION) || defined(__CC_ARM)
#pragma weak bt_hci_log_enabled = default_bt_hci_log_enabled
#pragma weak hci_log_cmd = default_hci_log_cmd
#pragma weak hci_log_event = default_hci_log_event
#pragma weak hci_log_acl_out = default_hci_log_acl_out
#pragma weak hci_log_acl_in = default_hci_log_acl_in
#else
#error "Unsupported Platform"
#endif

extern bool bt_hci_log_enabled(void);
extern int32_t hci_log_cmd(unsigned char* buf, int32_t length);
extern int32_t hci_log_event(unsigned char* buf, int32_t length);
extern int32_t hci_log_acl_out(unsigned char* buf, int32_t length);
extern int32_t hci_log_acl_in(unsigned char* buf, int32_t length);

bool default_bt_hci_log_enabled(void)
{
    return FALSE;
}

int32_t default_hci_log_cmd(unsigned char* buf, int32_t length)
{
    return 0;
}

int32_t default_hci_log_event(unsigned char* buf, int32_t length)
{
    return 0;
}

int32_t default_hci_log_acl_out(unsigned char* buf, int32_t length)
{
    return 0;
}

int32_t default_hci_log_acl_in(unsigned char* buf, int32_t length)
{
    return 0;
}

void bt_hci_log(const uint8_t in, const void * data, const uint32_t data_len)
{
    const uint8_t * p = (const uint8_t *)data;

    const uint8_t h4type = *p++;
    uint8_t logtype;
    
    if (!bt_hci_log_enabled()) {
        return;
    }
    if (in == 2) {
        logtype = BT_HCI_LOG_MSG;
        --p;
    } else if (in) {
        if (h4type == 2)        logtype = BT_HCI_LOG_ACL_IN;
        else if (h4type == 3)   logtype = BT_HCI_LOG_SCO_IN;
        else                    logtype = BT_HCI_LOG_EVENT;
    } else {
        if (h4type == 2)        logtype = BT_HCI_LOG_ACL_OUT;
        else if (h4type == 3)   logtype = BT_HCI_LOG_SCO_OUT;
        else                    logtype = BT_HCI_LOG_CMD;
    }
    if (logtype == BT_HCI_LOG_CMD) {
        hci_log_cmd((unsigned char *)p, data_len - 1);
    } 
    else if (logtype == BT_HCI_LOG_EVENT){
        hci_log_event((unsigned char *)p, data_len - 1);
    }
    else if (logtype == BT_HCI_LOG_ACL_OUT){
        hci_log_acl_out((unsigned char *)p, data_len - 1);
    }
    else if (logtype == BT_HCI_LOG_ACL_IN){
        hci_log_acl_in((unsigned char *)p, data_len - 1);
    }  

}

