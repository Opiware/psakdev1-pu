/* Copyright Statement:
 *
 */
#ifndef PPG_CONTROL_MODULE_H
#define PPG_CONTROL_MODULE_H

/** @defgroup ohrm_define Define
  * @{
  */
#define MT2511_PPG_TIA_GAIN_500K 0
#define MT2511_PPG_TIA_GAIN_250K 1
#define MT2511_PPG_TIA_GAIN_100K 2
#define MT2511_PPG_TIA_GAIN_050K 3
#define MT2511_PPG_TIA_GAIN_025K 4
#define MT2511_PPG_TIA_GAIN_010K 5
#define MT2511_PPG_TIA_GAIN_001M 6 
/**
  * @}
  */
  
/** 
 * @brief ppg_noise_level represents the noise amplitude of the PPG signal.
*/
extern const int ppg_noise_level; 

/** 
 * @brief ppg_control_max_tia defines the upper bound of MT2511 TIA setting for automatic adjustment. \n
 *        ppg_control_min_tia defines the lower bound of MT2511 TIA setting for automatic adjustment.
*/
extern const int ppg_control_max_tia;
extern const int ppg_control_min_tia;

/** 
 * @brief ppg_init_ambdac_current defines the initial setting of MT2511 ambdac1 current (0~6uA). \n
 *        ppg_init_led_current defines the initial setting of MT2511 LED current (0~255 code). \n
 *        ppg_init_tia_gain defines the initial setting of MT2511 TIA gain (010K~001M). \n 
*/
extern const int ppg_init_ambdac_current;
extern const int ppg_init_led_current;
extern const int ppg_init_tia_gain;

/** 
 * @brief threshold for watch off to on. 
*/
extern const int ppg_amb_on_threshold;
extern const int ppg_amb_variation_on_threshold;
extern const int ppg_Ipd_led_on_threshold;
/** 
 * @brief threshold for watch on to off. 
*/
extern const int ppg_Ipd_led_off_threshold;
extern const int ppg_Ipd_amb_off_threshold;
extern const int ppg_amb_variation_off_threshold;
extern const int ppg_amb_variation_off_threshold_zero;
extern const int ppg_Ipd_amb_led_off_threshold;
#endif //#ifndef PPG_CONTROL_MODULE_H




