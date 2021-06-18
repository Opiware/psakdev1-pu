/* Copyright Statement:
 *
 */

#ifndef __VSM_SENSOR_SUBSYS_ADAPTOR_H_
#define __VSM_SENSOR_SUBSYS_ADAPTOR_H_
 
#include <stdint.h>
#include "hal_i2c_master.h"
#include "vsm_driver.h"

#ifdef __cplusplus
extern "C" {
#endif
 
int32_t vsm_ppg1_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

int32_t vsm_ppg2_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

int32_t vsm_bisi_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

int32_t vsm_ekg_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

int32_t vsm_eeg_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

int32_t vsm_emg_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

int32_t vsm_gsr_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

int32_t vsm_ppg1_512hz_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                    void *buff_in, int32_t size_in);

void vsm_eint_set(uint32_t eint_num);

void vsm_eint_handler(void *parameter);
                    
vsm_status_t vsm_driver_sensor_subsys_init(void);

int32_t vsm_check_trigger_signal(uint32_t *signal, uint32_t *intr_ctrl);
int32_t vsm_reenable_irq(uint32_t intr_ctrl);

#ifdef __cplusplus
}
#endif

#endif /* __VSM_SENSOR_SUBSYS_ADAPTOR_H_ */

