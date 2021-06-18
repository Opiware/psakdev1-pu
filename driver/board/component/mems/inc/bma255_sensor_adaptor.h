/* Copyright Statement:
 *
 */

#ifndef __BMA255_SENSOR_ADAPTOR_H_
#define __BMA255_SENSOR_ADAPTOR_H_

#include <stdint.h>
#include "bma2x2.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t bma_acc_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

BMA2x2_RETURN_FUNCTION_TYPE bma255_sensor_subsys_init(void);

void bma255_eint_set(uint32_t eint_num);
void bma255_eint_handler(void *parameter);



#ifdef __cplusplus
}
#endif

#endif /* __BMA255_SENSOR_ADAPTOR_H_ */
