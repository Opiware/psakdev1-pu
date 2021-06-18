/* Copyright Statement:
 *
 */

#include <stdio.h>
#include "syslog.h"
#include "audio_nvdm.h"
#include "FreeRTOS.h"
#include "hal_audio_enhancement.h"
#include "audio_middleware_api.h"



log_create_module(audio_middleware_api, PRINT_LEVEL_INFO);

#define LOGE(fmt,arg...)   LOG_E(audio_middleware_api, "[audio_middleware_api]"fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(audio_middleware_api, "[audio_middleware_api]"fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(audio_middleware_api, "[audio_middleware_api]"fmt,##arg)


#define SPEECH_MODE_HEADSET 0


void audio_middleware_set_default_enhancement_parameters()
{
    // set speech headset mode as default enhancement parameters
    LOGI("audio middleware set default enhancement parameters ++\n");

    const audio_eaps_t *eaps;
    eaps = audio_nvdm_get_global_eaps_address();

#if PRODUCT_VERSION != 2533 // TODO: not using this method, we may set default enhancement in spicific file
    speech_update_common(eaps->speech_common_parameter.speech_common_parameter);
    speech_update_nb_fir((int16_t *)eaps->voice_parameter.voice_nb_parameter[SPEECH_MODE_HEADSET].voice_nb_enhancement_parameter.nb_stream_in_fir_coefficient,
                         (int16_t *)eaps->voice_parameter.voice_nb_parameter[SPEECH_MODE_HEADSET].voice_nb_enhancement_parameter.nb_stream_out_fir_coefficient);
    speech_update_nb_param(eaps->voice_parameter.voice_nb_parameter[SPEECH_MODE_HEADSET].voice_nb_enhancement_parameter.nb_mode_parameter);
    speech_update_wb_fir((int16_t *)eaps->voice_parameter.voice_wb_parameter[SPEECH_MODE_HEADSET].voice_wb_enhancement_parameter.wb_stream_in_fir_coefficient,
                         (int16_t *)eaps->voice_parameter.voice_wb_parameter[SPEECH_MODE_HEADSET].voice_wb_enhancement_parameter.wb_stream_out_fir_coefficient);
    speech_update_wb_param(eaps->voice_parameter.voice_wb_parameter[SPEECH_MODE_HEADSET].voice_wb_enhancement_parameter.wb_mode_parameter);
#else
    speech_update_common(eaps->speech_common_parameter.speech_common_parameter);
    speech_update_nb_fir((int16_t *)eaps->voice_parameter.voice_nb_band.voice_nb_parameter[SPEECH_MODE_HEADSET].voice_nb_enhancement_parameter.nb_stream_in_fir_coefficient,
                         (int16_t *)eaps->voice_parameter.voice_nb_band.voice_nb_parameter[SPEECH_MODE_HEADSET].voice_nb_enhancement_parameter.nb_stream_out_fir_coefficient);
    speech_update_nb_param(eaps->voice_parameter.voice_nb_band.voice_nb_parameter[SPEECH_MODE_HEADSET].voice_nb_enhancement_parameter.nb_mode_parameter);
    speech_update_wb_fir((int16_t *)eaps->voice_parameter.voice_wb_band.voice_wb_parameter[SPEECH_MODE_HEADSET].voice_wb_enhancement_parameter.wb_stream_in_fir_coefficient,
                         (int16_t *)eaps->voice_parameter.voice_wb_band.voice_wb_parameter[SPEECH_MODE_HEADSET].voice_wb_enhancement_parameter.wb_stream_out_fir_coefficient);
    speech_update_wb_param(eaps->voice_parameter.voice_wb_band.voice_wb_parameter[SPEECH_MODE_HEADSET].voice_wb_enhancement_parameter.wb_mode_parameter);    
#endif


    LOGI("audio middleware set default enhancement parameters --\n");

}

int audio_middleware_init()
{
    int ret = 0;

    LOGI("audio middleware init ++\n");
    
    audio_nvdm_init();

    audio_middleware_set_default_enhancement_parameters();

    LOGI("audio middleware init --\n");

    return ret;
}

