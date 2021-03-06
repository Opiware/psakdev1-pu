/* Copyright Statement:
 *
 */

#ifndef __HAL_DVFS_H__
#define __HAL_DVFS_H__

#include "hal_platform.h"

#ifdef HAL_DVFS_MODULE_ENABLED

/**
 * @addtogroup HAL
 * @{
 * @addtogroup DVFS
 * @{
 * This section introduces the DVFS driver APIs including terms and acronyms,
 * supported features, details on how to use this driver, DVFS function groups, enums, structures and functions.
 *
 * @section HAL_DVFS_Terms_Chapter Terms and acronyms
 *
 * The following provides descriptions of the terms commonly used in the DVFS driver and how to use its various functions.
 *
 * |Terms               |Details                                                                 |
 * |--------------------|------------------------------------------------------------------------|
 * |\b DVFS             | Dynamic Voltage and Frequency Scaling. |
 * |\b OPP              | Operating Performance Point, a tuple of frequency and voltage. For more details, please refer to the section "Power modes" in MTK MT2523 datasheet.\n @image html hal_dvfs_opp.png|
 *
 * @section HAL_DVFS_Driver_Usage_Chapter How to use the driver
 * - The DVFS framework adjusts to the ideal CPU frequency at a suitable voltage level.
 *   - Step1: Call #hal_dvfs_init() to initialize the DVFS module only once at system initialization.
 *   - Step2: Call #hal_dvfs_get_cpu_frequency() to get the current CPU frequency.
 *   - Step3: Call #hal_dvfs_get_cpu_frequency_list() to get the supported CPU frequencies.
 *   - Step4: Call #hal_dvfs_target_cpu_frequency() to change the current CPU frequency.
 *   - Step5: Call #hal_dvfs_get_cpu_frequency() to get the current CPU frequency.
 *   - Step6: Print out the frequencies obtained from Step2 and Step5 to identify the difference.
 *   - Sample code:
 *   @code
 *
 *       uint32_t old_freq, cur_freq, list_num;
 *       const uint32_t *cpu_freq_list;
 *
 *       hal_dvfs_init();
 *       old_freq = hal_dvfs_get_cpu_frequency();
 *       hal_dvfs_get_cpu_frequency_list(&cpu_freq_list, &list_num);
 *       hal_dvfs_target_cpu_frequency(cpu_freq_list[0], HAL_DVFS_FREQ_RELATION_L); // cpu_freq_list[0] is the highest and cpu_freq_list[list_num-1] is the lowest frequency.
 *       cur_freq = hal_dvfs_get_cpu_frequency();
 *       log_hal_info("old_freq=%d, cur_freq=%d\n", old_freq, cur_freq);
 *
 *   @endcode
 * */

/*****************************************************************************
* Enum
*****************************************************************************/
/** @defgroup hal_dvfs_enum Enum
  * @{
  */
/** @brief This enum defines return status of certain DVFS HAL APIs. User should check return value after calling these APIs. */
typedef enum {
    HAL_DVFS_STATUS_NOT_PERMITTED  = -5,      /**< The operation is not permitted. */
    HAL_DVFS_STATUS_BUSY           = -4,      /**< Device or resource is busy. */
    HAL_DVFS_STATUS_UNINITIALIZED  = -3,      /**< Non-initialized. */
    HAL_DVFS_STATUS_INVALID_PARAM  = -2,      /**< Invalid parameter value. */
    HAL_DVFS_STATUS_ERROR          = -1,      /**< The DVFS function detected a common error. */
    HAL_DVFS_STATUS_OK             =  0       /**< The DVFS function executed successfully. */
} hal_dvfs_status_t;

/** @brief This enum defines the relationship between the target frequency and the final frequency. */
typedef enum {
    HAL_DVFS_FREQ_RELATION_L = 0,             /**< The lowest frequency at or above the target level. */
    HAL_DVFS_FREQ_RELATION_H = 1              /**< The highest frequency below or at the target level. */
} hal_dvfs_freq_relation_t;

/**
  * @}
  */

/*****************************************************************************
* extern global function
*****************************************************************************/
/**
 * @brief       The function initializes the DVFS framework.
 * @return      #HAL_DVFS_STATUS_OK, if the initialization completed successfully.\n
 *              #HAL_DVFS_STATUS_ERROR, if an error occurred during the initialization.\n */
hal_dvfs_status_t hal_dvfs_init(void);

/**
 * @brief       This function adjusts the CPU frequency to a suitable target frequency according to the passed-in relation.
 * @param[in]   target_freq    is the target frequency in kHz.
 * @param[in]   relation       is the relationship between the target frequency and the final frequency.
 *              #HAL_DVFS_FREQ_RELATION_L, the lowest frequency at or above the target level.\n
 *              #HAL_DVFS_FREQ_RELATION_H, the highest frequency below or at the target level.\n
 *              Example 1.\n
 *              #hal_dvfs_target_cpu_frequency(103000, #HAL_DVFS_FREQ_RELATION_L). The final CPU frequency is equal to or greater than 103MHz.\n
 * @image html hal_dvfs_example1.png
 *              Example 2.\n
 *              #hal_dvfs_target_cpu_frequency(103000, #HAL_DVFS_FREQ_RELATION_H). The final CPU frequency is equal to or less than 103MHz.\n
 * @image html hal_dvfs_example2.png
 * @return      #HAL_DVFS_STATUS_OK, if OK.\n
 *              #HAL_DVFS_STATUS_INVALID_PARAM, if the parameter value is invalid.\n
 *              #HAL_DVFS_STATUS_ERROR, if an error occurred.\n */
hal_dvfs_status_t hal_dvfs_target_cpu_frequency(uint32_t target_freq, hal_dvfs_freq_relation_t relation);

/**
 * @brief       This function gets the current CPU frequency.
 * @return      The current CPU frequency is in kHz. */
uint32_t hal_dvfs_get_cpu_frequency(void);

/**
 * @brief       This function gets all adjustable CPU frequencies listed in the OPP table.
 * @param[out]   list          is a double pointer to the frequency table.
 * @param[out]   list_num      is a pointer to the number of the entries in the frequency table.
 * @return      #HAL_DVFS_STATUS_OK, if the operation completed successfully.\n
 *              #HAL_DVFS_STATUS_ERROR, if an error occurred during the operation..\n */
hal_dvfs_status_t hal_dvfs_get_cpu_frequency_list(const uint32_t **list, uint32_t *list_num);

/**
* @}
* @}
*/

#endif /* HAL_DVFS_MODULE_ENABLED */

#endif /* __HAL_DVFS_H__ */
