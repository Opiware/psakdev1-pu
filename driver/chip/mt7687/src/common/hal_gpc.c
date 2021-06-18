/* Copyright Statement:
 *
 */

#include "hal_gpc.h"

#ifdef HAL_GPC_MODULE_ENABLED
#include <stdbool.h>
#include "type_def.h"
#include "stddef.h"
#include "hal_gpc.h"
#include "hal_pcnt.h"
#include "hal_log.h"

static hal_pcnt_edge_t pcnt_edge;
static bool pcnt_state_work;
static bool hal_gpc_has_initilized;

hal_gpc_status_t hal_gpc_init(hal_gpc_port_t gpc_port, const hal_gpc_config_t *gpc_config)
{
    if ((hal_gpc_has_initilized != false) || (pcnt_state_work == true)) {
        log_hal_error("Port:%d is running\r\n", gpc_port);
        return HAL_GPC_STATUS_ERROR;
    }
    if (gpc_port >= HAL_GPC_MAX_PORT) {
        return HAL_GPC_STATUS_ERROR_PORT;
    }

    if (gpc_config->edge == HAL_GPC_EDGE_RAISING) {
        pcnt_edge = HAL_PCNT_EDGE_RAISING;
    } else {
        pcnt_edge = HAL_PCNT_EDGE_FALLING;
    }

    pcnt_state_work = FALSE;
    hal_gpc_has_initilized = true;

    return HAL_GPC_STATUS_OK;
}

hal_gpc_status_t hal_gpc_deinit(hal_gpc_port_t gpc_port)
{

    if (gpc_port >= HAL_GPC_MAX_PORT) {
        return HAL_GPC_STATUS_ERROR_PORT;
    }

    if (pcnt_state_work != false) {
        return HAL_GPC_STATUS_ERROR;
    }
    pcnt_edge = HAL_PCNT_EDGE_RAISING;
    pcnt_state_work = FALSE;
    hal_gpc_has_initilized = false;
    return HAL_GPC_STATUS_OK;
}

hal_gpc_status_t hal_gpc_get_running_status(hal_gpc_port_t gpc_port, hal_gpc_running_status_t *running_state)
{
    if (gpc_port >= HAL_GPC_MAX_PORT) {
        return HAL_GPC_STATUS_ERROR_PORT;
    }

    if (pcnt_state_work == FALSE) {
        *running_state = HAL_GPC_STATUS_IDLE;
    } else {
        *running_state = HAL_GPC_STATUS_BUSY;
    }

    return HAL_GPC_STATUS_OK;

}

hal_gpc_status_t hal_gpc_enable(hal_gpc_port_t gpc_port)
{
    if (hal_gpc_has_initilized != true) {
        return HAL_GPC_STATUS_ERROR;
    }
    if (gpc_port >= HAL_GPC_MAX_PORT) {
        return HAL_GPC_STATUS_ERROR_PORT;
    }

    hal_pcnt_config(TRUE, pcnt_edge);
    pcnt_state_work = TRUE;

    return HAL_GPC_STATUS_OK;
}

hal_gpc_status_t hal_gpc_disable(hal_gpc_port_t gpc_port)
{
    if (hal_gpc_has_initilized != true) {
        return HAL_GPC_STATUS_ERROR;
    }

    if (gpc_port >= HAL_GPC_MAX_PORT) {
        return HAL_GPC_STATUS_ERROR_PORT;
    }

    hal_pcnt_config(FALSE, pcnt_edge);
    pcnt_state_work = FALSE;

    return HAL_GPC_STATUS_OK;
}

hal_gpc_status_t hal_gpc_get_and_clear_count(hal_gpc_port_t gpc_port, uint32_t *count)
{
    if (hal_gpc_has_initilized != true) {
        return HAL_GPC_STATUS_ERROR;
    }
    if (gpc_port >= HAL_GPC_MAX_PORT) {
        return HAL_GPC_STATUS_ERROR_PORT;
    }

    *count = hal_pcnt_read_and_clear();

    return HAL_GPC_STATUS_OK;
}

#endif

