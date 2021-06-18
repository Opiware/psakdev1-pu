/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_LOW_POWER_H__
#define __HAL_AUDIO_LOW_POWER_H__

#include "hal_audio.h"

#if defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED)

#include "hal_audio_fw_sherif.h"
#include "hal_audio_internal_service.h"
#include "hal_dsp_topsm.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct audlp2_hdl {
    bool             audio_lowpower_enable;
    bool             clock_switch_26m;
} hal_audio_lowpower_struct_t;

//typedef volatile unsigned long  *APBADDR32;

/* #define MODEM2G_TOPSM_BASE   0x83010000 */
/* #define MDCONFIG_BASE        0x83000000*/
#define MODEM2G_TOPSM_SW_CLK_FORCE_ON_SET        ((volatile unsigned long  *)(MODEM2G_TOPSM_BASE+0x0A04))  //32bit
#define MODEM2G_TOPSM_SW_CLK_FORCE_ON_CLR        ((volatile unsigned long  *)(MODEM2G_TOPSM_BASE+0x0A08))  //32bit
#define MODEM_ALLOW_26M_CLKSW                    ((volatile unsigned long  *)(MDCONFIG_BASE+0x0508))       //32bit

void audio_lowpower_init(void);
void audio_lowpower_set_mode(bool enable);
void audio_lowpower_set_clock_mode(bool flag);
void audio_lowpower_sw_trigger_event_set(bool flag);
void audio_lowpower_set_26mclock(bool flag);
bool audio_lowpower_check_status(void);

#ifdef __cplusplus
}
#endif

#endif  /* defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED) */

#endif /* __HAL_AUDIO_LOW_POWER_H__ */
