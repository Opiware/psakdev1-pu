/* Copyright Statement:
 *
 */

#include "hal_pmu.h"
#include "hal_pmu_wrap_interface.h"
#ifdef HAL_PMU_MODULE_ENABLED

static hal_pmu_wrap_struct hal_pmu_struct_t = {
        pmu_init_mt7686,
        pmu_init_power_mode_mt7686,
        pmu_set_vcore_voltage_mt7686,
        pmu_enter_sleep_mode_mt7686,
        pmu_enter_retention_mode_mt7686,
        pmu_resume_to_normal_mt7686,
        pmu_set_cldo_voltage_mt7686,
        pmu_set_mldo_voltage_mt7686,
        pmu_retention_ldo_control_mt7686,
        pmu_sram_power_switch_control_mt7686,
        pmu_set_retention_ldo_mt7686
};
void hal_pmu_init(){
    hal_pmu_struct_t.init();
}

void hal_pmu_init_power_mode(){
    hal_pmu_struct_t.init_power_mode();
}

void hal_pmu_set_vcore_voltage(hal_pmu_stage mode,pmu_vcore_vosel_t vol){
    hal_pmu_struct_t.set_vcore_voltage(mode,vol);
}

void hal_pmu_enter_sleep_mode(){
    hal_pmu_struct_t.enter_sleep_mode();
}

void hal_pmu_enter_retention_mode(pmu_retention_status_t status){
    hal_pmu_struct_t.enter_retention_mode(status);
}

void hal_pmu_resume_to_normal(hal_pmu_stage_flow mode){
    hal_pmu_struct_t.resume_to_normal(mode);
}

void hal_pmu_set_cldo_voltage(int index){
    hal_pmu_struct_t.set_cldo_voltage(index);
}
void hal_pmu_set_mldo_voltage(int adjust_value){
    hal_pmu_struct_t.set_mldo_voltage(adjust_value);
}

void hal_pmu_retention_ldo_control(pmu_control_t status){
    hal_pmu_struct_t.control_retention_lod(status);
}

void hal_pmu_sram_power_switch_control(pmu_control_t status){
    hal_pmu_struct_t.sram_power_switch_control(status);
}

void hal_pmu_set_retention_ldo_voltage(int adjust_value){
    hal_pmu_struct_t.set_retention_ldo(adjust_value);
}
#endif /* HAL_PMU_MODULE_ENABLED */
