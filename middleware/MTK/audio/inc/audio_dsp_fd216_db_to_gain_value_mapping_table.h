/* Copyright Statement:
 *
 */

#ifndef __AUDIO_DB_TO_GAIN_VALUE_MAPPING_TABLE_H__
#define __AUDIO_DB_TO_GAIN_VALUE_MAPPING_TABLE_H__


#ifdef __cplusplus
extern "C" {
#endif


#define AUDIO_DOWNLINK_AMP_DB_MINIMUM -76
#define AUDIO_DOWNLINK_AMP_DB_MAXIMUM -2
#define ADUIO_DOWNLINK_AMP_DB_STEP 2
#define VOICE_DOWNLINK_AMP_DB_MINIMUM -23
#define VOICE_DOWNLINK_AMP_DB_MAXIMUM 7
#define VOICE_DOWNLINK_AMP_DB_STEP 2
#define VOICE_UPLINK_AMP_DB_MINIMUM 4
#define VOICE_UPLINK_AMP_DB_MAXIMUM 45
#define VOICE_UPLINK_AMP_DB_STEP 1
#define VOICE_UPLINK_DMIC_DB_MINIMUM 4
#define VOICE_UPLINK_DMIC_DB_MAXIMUM 34
#define VOICE_UPLINK_DMIC_DB_STEP 1
#define VOICE_SIDETONE_DB_MINIMUM 0
#define VOICE_SIDETONE_DB_MAXIMUM 31
#define VOICE_SIDETONE_DB_STEP 1


void audio_downlink_amp_db_transfer_to_analog_gain_and_digital_gain(int32_t input_db, int32_t *analog_gain_in_db, int32_t *digital_gain_in_db);
void voice_downlink_amp_db_transfer_to_analog_gain_and_digital_gain(int32_t input_db, int32_t *analog_gain_in_db, int32_t *digital_gain_in_db);
void voice_uplink_amp_db_transfer_to_analog_gain_and_digital_gain(int32_t input_db, int32_t *analog_gain_in_db, int32_t *digital_gain_in_db);
void voice_uplink_dmic_db_transfer_to_analog_gain_and_digital_gain(int32_t input_db, int32_t *analog_gain_in_db, int32_t *digital_gain_in_db);
void voice_sidetone_db_make_sure_in_range(int32_t *input_db);


#ifdef __cplusplus
}
#endif

#endif  /* __AUDIO_DB_TO_GAIN_VALUE_MAPPING_TABLE_H__ */

