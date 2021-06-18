/* Copyright Statement:
 *
 */
#include "ppg_control_module.h"

/** 
 * @brief ppg_noise_level represents the noise amplitude of the PPG signal.
*/
const int ppg_noise_level = 40;

/** 
 * @brief ppg_control_max_tia defines the upper bound of MT2511 TIA setting for automatic adjustment. \n
 *        ppg_control_min_tia defines the lower bound of MT2511 TIA setting for automatic adjustment.
*/
const int ppg_control_max_tia = MT2511_PPG_TIA_GAIN_500K;
const int ppg_control_min_tia = MT2511_PPG_TIA_GAIN_010K; 

/** 
 * @brief ppg_init_ambdac_current defines the initial setting of MT2511 ambdac1 current (0~6uA). \n
 *        ppg_init_led_current defines the initial setting of MT2511 LED current (0~255 code). \n
 *        ppg_init_tia_gain defines the initial setting of MT2511 TIA gain (010K~001M). \n 
*/
const int ppg_init_ambdac_current = 3;
const int ppg_init_led_current = 192;
const int ppg_init_tia_gain = MT2511_PPG_TIA_GAIN_100K; 

/** 
 * @brief threshold for watch off to on. 
*/
const int ppg_amb_on_threshold = 10000;
const int ppg_amb_variation_on_threshold = 1000;
const int ppg_Ipd_led_on_threshold = 1370;

/** 
 * @brief threshold for watch on to off. 
*/
const int ppg_Ipd_led_off_threshold = 1370;
const int ppg_Ipd_amb_off_threshold = 102050;
const int ppg_amb_variation_off_threshold = 1000;
const int ppg_amb_variation_off_threshold_zero = 15000;
const int ppg_Ipd_amb_led_off_threshold = 130000;   



