/* Copyright Statement:
 *
 */

#include "hal_platform.h"
#include "hal_cm4_topsm.h"
#ifdef HAL_SLEEP_MANAGER_ENABLED

#ifdef HAL_SD_MODULE_ENABLED
extern void sd_backup_all(void);
extern void sd_restore_all(void);
#endif

#ifdef HAL_SDIO_MODULE_ENABLED
extern void sdio_backup_all(void);
extern void sdio_restore_all(void);
#endif


#ifdef HAL_PWM_MODULE_ENABLED
extern void pwm_backup_register_call_back(void);
extern void pwm_restore_register_call_back(void);
#endif

#ifdef HAL_SPI_MASTER_MODULE_ENABLED
extern void spim_backup_register_callback(void);
extern void spim_restore_register_callback(void);
#endif

#ifdef HAL_SPI_SLAVE_MODULE_ENABLED
extern void spi_slave_backup_all_register(void);
extern void spi_slave_restore_all_register(void);
#endif

#ifdef  HAL_I2C_MASTER_MODULE_ENABLED
extern void hal_i2c_backup_all_register(void);
extern void hal_i2c_restore_all_register(void);
#endif

void hal_module_sleep_register_callback(void)
{
//Example
//   hal_cm4_topsm_register_suspend_cb(i2c_sleep_cb, "i2c_xxx");
//   hal_cm4_topsm_register_resume_cb(i2c_wakeup_cb, "i2c_xxx");

    /*register pwm callback*/
#ifdef HAL_PWM_MODULE_ENABLED
    hal_cm4_topsm_register_suspend_cb((cm4_topsm_cb)pwm_backup_register_call_back, NULL);
    hal_cm4_topsm_register_resume_cb((cm4_topsm_cb)pwm_restore_register_call_back, NULL);
#endif

    /*register spi callback*/
#ifdef HAL_SPI_MASTER_MODULE_ENABLED
    hal_cm4_topsm_register_suspend_cb((cm4_topsm_cb)spim_backup_register_callback, NULL);
    hal_cm4_topsm_register_resume_cb((cm4_topsm_cb)spim_restore_register_callback, NULL);
#endif

    /*register spi slave callback*/
#ifdef HAL_SPI_SLAVE_MODULE_ENABLED
    hal_cm4_topsm_register_suspend_cb((cm4_topsm_cb)spi_slave_backup_all_register, NULL);
    hal_cm4_topsm_register_resume_cb((cm4_topsm_cb)spi_slave_restore_all_register, NULL);
#endif

    /*register i2c callback*/
#ifdef  HAL_I2C_MASTER_MODULE_ENABLED
    hal_cm4_topsm_register_suspend_cb((cm4_topsm_cb)hal_i2c_backup_all_register, NULL);
    hal_cm4_topsm_register_resume_cb((cm4_topsm_cb)hal_i2c_restore_all_register, NULL);
#endif

    /*register sd callback*/
#ifdef HAL_SD_MODULE_ENABLED
    hal_cm4_topsm_register_suspend_cb((cm4_topsm_cb)sd_backup_all, NULL);
    hal_cm4_topsm_register_resume_cb((cm4_topsm_cb)sd_restore_all, NULL);
#endif

    /*register sdio callback*/
#ifdef HAL_SDIO_MODULE_ENABLED
    hal_cm4_topsm_register_suspend_cb((cm4_topsm_cb)sdio_backup_all, NULL);
    hal_cm4_topsm_register_resume_cb((cm4_topsm_cb)sdio_restore_all, NULL);
#endif
}

#endif

