/* Copyright Statement:
 *
 */

#include "hal_audio_fw_interface.h"
#include "hal_audio_fw_library.h"

/*******************************************************************************\
| Re-Entry Counter                                                              |
\*******************************************************************************/
static uint32_t dynamic_download_entry_counter = 0;

/*******************************************************************************\
| ID Address Table                                                              |
\*******************************************************************************/

/* DDID_AUDIO_HEADER */
static const dsp_audio_fw_type_address_entry_t audio_fw_ddl_pcm_table[DDL_PCM_TAB_LEN] = {
#if defined(MTK_AUDIO_IIR_FILTER_ENABLE)
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_PCM_SD_PLAYBACK},
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_IIR},
#endif
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_Header_Kernel},
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_Audio_Header}
};

#if defined(HAL_I2S_MODULE_ENABLED)
/* DDID_I2S */
static const dsp_audio_fw_type_address_entry_t audio_fw_ddl_i2s_table[DDL_I2S_TAB_LEN] = {
#if defined(MTK_AUDIO_IIR_FILTER_ENABLE)
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_IIR},
#endif
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_Header_Kernel},
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_Audio_Header},
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_I2S}
};
#endif

#if defined(MTK_BT_A2DP_AAC_ENABLE)
/* DDID_AAC */
static const dsp_audio_fw_type_address_entry_t audio_fw_ddl_aac_table[DDL_AAC_TAB_LEN] = {
#if defined(MTK_AUDIO_IIR_FILTER_ENABLE)
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_IIR},
#endif
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_Header_Kernel},
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_Audio_Header},
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_AAC},
    {DDL_PM_TYPE, DDL_PM_PAGE, &pmdll_AAC},
    {DDL_DM_TYPE, DDL_DM_PAGE, &dmdll_AAC}
};
#endif

/* DDID_SBC_DECODE */
static const dsp_audio_fw_type_address_entry_t audio_fw_ddl_sbc_dec_table[DDL_SBC_DEC_TAB_LEN] = {
#if defined(MTK_AUDIO_IIR_FILTER_ENABLE)
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_IIR},
#endif
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_Header_Kernel},
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_Audio_Header},
    {DDL_CM_TYPE, DDL_CM_PAGE, &cmdll_SBC_DEC},
    {DDL_PM_TYPE, DDL_PM_PAGE, &pmdll_SBC_DEC}
};

/* DDID_SPH_ENH */
static const dsp_audio_fw_type_address_entry_t audio_fw_ddl_sph_enh_table[DDL_SPH_ENH_TAB_LEN] = {
    {DDL_CM_TYPE, DDL_CM_PAGE,  &cmdll_Header_Kernel},
    {DDL_CM_TYPE, DDL_CM_PAGE,  &cmdll_TCH},
    {DDL_CM_TYPE, DDL_CM2_PAGE, &cmdll_TCH2},
    {DDL_PM_TYPE, DDL_PM_PAGE,  &pmdll_AECS}
};

static const dsp_audio_fw_id_address_entry_t audio_fw_id_address_table[DDL_ID_ADDR_TAB_LEN] = {
    {DDID_AUDIO_HEADER, DDL_PCM_TAB_LEN,        audio_fw_ddl_pcm_table},
#if defined(HAL_I2S_MODULE_ENABLED)
    {DDID_I2S,          DDL_I2S_TAB_LEN,        audio_fw_ddl_i2s_table},
#endif
#if defined(MTK_BT_A2DP_AAC_ENABLE)
    {DDID_AAC,          DDL_AAC_TAB_LEN,        audio_fw_ddl_aac_table},
#endif
    {DDID_SBC_DECODE,   DDL_SBC_DEC_TAB_LEN,    audio_fw_ddl_sbc_dec_table},
    {DDID_SPH_ENH,      DDL_SPH_ENH_TAB_LEN,    audio_fw_ddl_sph_enh_table}
};

/*******************************************************************************\
| Public Functions                                                              |
\*******************************************************************************/

void dsp_audio_fw_reboot(void)
{
    dynamic_download_entry_counter = 0;
    dsp_audio_fw_lib_reboot();
    return;
}

void dsp_audio_fw_init(void)
{
    dynamic_download_entry_counter = 0;
    dsp_audio_fw_lib_init();
    return;
}

int32_t dsp_audio_fw_dynamic_download(uint32_t fw_id)
{
    int32_t result = -1;
    if (dynamic_download_entry_counter == 0) {
        dynamic_download_entry_counter++;
        {   /* Start dynamic download */
            int32_t id_idx;
            for (id_idx = 0; id_idx < DDL_ID_ADDR_TAB_LEN; id_idx++) {
                const dsp_audio_fw_id_address_entry_t *p_tab = &audio_fw_id_address_table[id_idx];
                if (fw_id == p_tab->fw_id) {
                    result = dsp_audio_fw_lib_dynamic_download(p_tab->count, p_tab->table);
                    break;
                }
            }
        }
        dynamic_download_entry_counter--;
    }
    return result;
}
