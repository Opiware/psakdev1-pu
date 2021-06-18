/* Copyright Statement:
 *
 */
#ifndef BP_ALG_H
#define BP_ALG_H 
/**
 * @file    bp_alg.h
 * @brief   Library of blood pressure algorithm
 * @author  MTK
 * @version 1.0.0.1
 * @date    2016.08.04 */
/** 
 * @addtogroup BP_ALG
 * @{
 *
 * @section Terms_Chapter Terms and acronyms
 * 
 * |Terms                   |Details                                                                 |
 * |------------------------|------------------------------------------------------------------------|
 * |\b BP_ALG               | Blood pressure algorithm.                                              |
 * |\b PPG                  | Photoplethysmogram. For more information, please refer to the <a href="https://en.wikipedia.org/wiki/Photoplethysmogram"> PPG in Wikipedia </a>.   |
 * |\b ECG                  | Electrocardiography. For more information, please refer to the <a href="https://en.wikipedia.org/wiki/Electrocardiographym"> ECG in Wikipedia </a>.|
 * |\b PWTT                 | Pulse Wave Transit Time. It is the time difference between R-peak of ECG and wave-peak of PPG of the same heart beat. For more information, please refer to the <a href="http://www.nihonkohden.com/tech/pwtt/how.html"> How it works: PWTT </a>.|
 * |\b SBP                  | Systolic Blood Pressure. For more information, please refer to the <a href="https://en.wikipedia.org/wiki/Blood_pressure"> Systolic blood pressure in Wikipedia </a>.|
 * |\b DBP                  | Diastolic Blood Pressure. For more information, please refer to the <a href="https://en.wikipedia.org/wiki/Blood_pressure"> Diastolic blood pressure in Wikipedia </a>.|
 * |\b BPM                  | Beats Per Minute. The common unit for heart rate value representation.
 *
 *
 * @section BP_ALG_Usage_Chapter How to use this library
 * Step 1: Call #bp_alg_init() to initialize blood pressure algorithm library. \n 
 * Step 2: Call #bp_alg_set_user_info() to set the user information. \n 
 * Step 3: Call #bp_alg_process_data() when the PPG data or ECG data is received. \n 
 * Step 4: Call #bp_alg_get_bp() to get the blood pressure value, after the PPG/ECG data has been processed by #bp_alg_process_data(). \n
 *
 *  - Sample code:
 *    @code 
 *
 * #include "bp_alg.h" 
 * #define BP_DATA_LEN   12800  // The input data length 
 * bp_alg_out_t bp_output; // The output structure for #bp_alg_get_bp().
 * int32_t bp_height;      // The user's height as an input to #bp_alg_set_user_info().
 * int32_t bp_weight;      // The user's weight as an input to #bp_alg_set_user_info(). 
 * int32_t bp_gender;      // The user's gender as an input to #bp_alg_set_user_info(). 
 * int32_t bp_age;         // The user's age as an input to #bp_alg_set_user_info(). 
 * int32_t bp_arm_len;     // The user's arm length as an input to #bp_alg_set_user_info(). 
 * void example(void)
 * {
 *   int32_t i;
 *   // Initialization
 *   bp_alg_init();
 *   // Set the user specific settings.
 *   bp_alg_set_user_info(bp_age, bp_gender, bp_height, bp_weight, bp_arm_len);
 *   for (i=0;i<BP_DATA_LEN;i++)
 *   {
 *     bp_alg_process_data(ecg_data[i], 0); // Input the ECG data for processing. 
 *     bp_alg_process_data(ppg_data[i], 1); // Input the PPG data for processing.
 *   }
 *   // Output blood pressure.
 *   bp_alg_get_bp(&output_data);
 * }
 *    @endcode
 * */

/** @defgroup bp_alg_define Define
  * @{
  */

#define MAX_NUM_PWTT 40    /**< The maximum number of PWTT. */
/**
  * @}
  */

/** @defgroup ohrm_struct Struct
  * @{
  */

/** @struct bp_alg_out_t
* @brief This structure defines output of the blood pressure algorithm.
*/
typedef struct 
{	
  int32_t sbp;      /**< Systolic blood pressure. */
  int32_t dbp;      /**< Diastolic blood pressure. */
  int32_t bpm;	    /**< Beats per minute. */
  int32_t num_pwtt; /**< The number of PWTT. */
  int32_t pwtt[MAX_NUM_PWTT]; /**< An output array for the PWTT data. */
//   int32_t status;
}bp_alg_out_t;

/** 
 * @brief This function initializes the algorithm.
*/
void bp_alg_init(void);

/** 
 * @brief This function sets the user information for the blood pressure algorithm library. Call this function right after initializing the algorithm to include user's setting for all the other calculations.
 * @param[in] age is the user's age.
 * @param[in] gender is the user's gender. If the value is 1, the gender is male, otherwise it is female.
 * @param[in] height is the user's height. The unit of height is centimeters. 
 * @param[in] weight is the user's weight. The unit of weight is kilograms.
 * @param[in] arm_length is the user's arm length. The unit of length is centimeters.
*/
void bp_alg_set_user_info(int32_t age, int32_t gender, int32_t height, int32_t weight, int32_t arm_length);
/** 
 * @brief This function processes the input ECG/PPG data.
 * @param[in] data is the input data.
 * @param[in] type is the type of input data. If the value is 0, the input data is the ECG data point. If the value is 1, the input data is the PPG data point.
*/
void bp_alg_process_data(int32_t data, int32_t type);
/** 
 * @brief This function gets the blood pressure value from the blood pressure algorithm.
 * @param[out] output is the output structure of the blood pressure algorithm.
*/
void bp_alg_get_bp(bp_alg_out_t* output);
/**
* @}
* @}
*/
void bp_alg_set_calibration_data(int32_t* data_in,  int32_t data_in_len);
void bp_alg_get_calibration_data(int32_t* data_out, int32_t data_out_len);
int32_t get_pwtt_variation(bp_alg_out_t* bp_output);
int32_t bp_alg_get_ecg_error(int32_t data_curr);
int32_t bp_alg_get_version(void);

#endif //BP_ALG_H
