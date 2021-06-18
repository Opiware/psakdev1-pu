/* Copyright Statement:
 *
 */

#ifdef MTK_NVDM_ENABLE

#include <stdlib.h>
#include <string.h>

#include "nvdm.h"

#include "nvdm_cli.h"

#define READ_HELP "config read <group_name> <data_item_name>"
#define WRITE_HELP "config write <group_name> <data_item_name> <value>"
#define RESET_HELP "config reset <group_name>"
#define SHOW_HELP "config show <group_name>"

extern void user_data_item_reset_to_default(char *group_name);
extern void user_data_item_show_value(char *group_name);


static unsigned char data_item_read(uint8_t len, char *param[])
{
#ifdef MTK_SINGLE_SKU_SUPPORT
    //single_SKU item is large than 798 bytes.
    char tmp[800];
#else
    char tmp[256];
#endif
    int  nvdm_len = sizeof(tmp);
    nvdm_status_t status;

    if (len == 2) {
        status = nvdm_read_data_item((const char *)param[0],
                                     (const char *)param[1],
                                     (uint8_t *)tmp,
                                     (uint32_t *)&nvdm_len);
        if (status == NVDM_STATUS_OK) {
            cli_puts(param[1]);
            cli_puts(" = ");
            cli_puts(tmp);
            cli_putln();
        } else {
            cli_puts("the data item is not exist");
            cli_putln();
        }
    } else {
        cli_puts(READ_HELP);
        cli_putln();
    }

    return 0;
}


static unsigned char data_item_write(uint8_t len, char *param[])
{
    nvdm_status_t status;

    if (len == 3) {
        cli_puts(param[0]);
        cli_puts("-");
        cli_puts(param[1]);
        cli_puts(" = ");
        cli_puts(param[2]);
        cli_putln();
        status = nvdm_write_data_item((const char *)param[0],
                                      (const char *) param[1],
                                      NVDM_DATA_ITEM_TYPE_STRING,
                                      (const uint8_t *)param[2],
                                      (uint32_t)strlen(param[2]));
        if (status != NVDM_STATUS_OK) {
            cli_puts("write data item error");
            cli_putln();
        } else {
            cli_puts("write data item ok");
            cli_putln();
        }
    } else {
        cli_puts(WRITE_HELP);
        cli_putln();
    }

    return 0;
}


static unsigned char data_item_reset(uint8_t len, char *param[])
{
    if (len == 0) {
        cli_puts("reset all group ");
        cli_putln();
        user_data_item_reset_to_default(NULL);
    } else if (len == 1) {
        cli_puts("reset group ");
        cli_puts(param[0]);
        cli_putln();
        user_data_item_reset_to_default(param[0]);
    } else {
        cli_puts(RESET_HELP);
        cli_putln();
    }

    return 0;
}


static unsigned char data_item_show(uint8_t len, char *param[])
{
    if (len == 0) {
        cli_puts("show all group ");
        cli_putln();
        user_data_item_show_value(NULL);
    } else if (len == 1) {
        cli_puts("show group ");
        cli_puts(param[0]);
        cli_putln();
        user_data_item_show_value(param[0]);
    } else {
        cli_puts(RESET_HELP);
        cli_putln();
    }

    return 0;
}


cmd_t nvdm_cli[] = {
    { "read", READ_HELP, data_item_read, NULL },
    { "write", WRITE_HELP, data_item_write, NULL },
    { "reset", RESET_HELP, data_item_reset, NULL },
    { "show", SHOW_HELP, data_item_show, NULL },
    { NULL, NULL, NULL, NULL }
};

#endif

