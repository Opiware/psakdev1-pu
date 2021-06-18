/* Copyright Statement:
 *
 */

#ifndef __GAUGE_MAX17048_H__
#define __GAUGE_MAX17048_H__

#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

bool max17048_init(void);
bool max17048_verify_model(void);
void max17048_update_temperature(int temperature);
unsigned int max17048_get_soc(void);
unsigned int max17048_get_vcell(void);

#ifdef __cplusplus
}
#endif

#endif
