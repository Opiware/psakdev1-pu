/* Copyright Statement:
 *
 */

#include "hal_audio_ext.h"

#if defined(HAL_I2S_MODULE_ENABLED)
#include "hal_audio_internal_afe.h"
#include "hal_i2s_internal.h"
#include "hal_log.h"
/**
  * @ Control the extended audio output device
  * @ device: output device
  */
hal_audio_status_t hal_audio_set_extended_out_device(hal_audio_ext_device_t device)
{
    afe_audio_set_ext_output_device(device);
    if (afe_is_audio_enable()) {
        afe_switch_tx_signal_path(true);
    }
    return HAL_AUDIO_STATUS_OK;
}

#ifdef HAL_I2S_DSP_DECODE_CONCURRENT_ENABLED
void hal_i2s_dsp_decode_enable(bool enable)
{
    hal_i2s.dsp_decode_concurrency = enable;
}
#endif /* HAL_I2S_DSP_DECODE_CONCURRENT_ENABLED */

#endif  /* defined(HAL_AUDIO_MODULE_ENABLED) */
