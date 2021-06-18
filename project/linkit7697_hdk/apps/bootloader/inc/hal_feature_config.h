/* Copyright Statement:
 *
 */

#ifndef __HAL_FEATURE_CONFIG_H__
#define __HAL_FEATURE_CONFIG_H__


#ifdef __cplusplus
    extern "C" {
#endif


/*****************************************************************************
* module ON or OFF feature option,only option in this temple
*****************************************************************************/

//#define HAL_ACCDET_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_AES_MODULE_ENABLED          
//#define HAL_AUDIO_MODULE_ENABLED     
#define HAL_CACHE_MODULE_ENABLED    
#define HAL_DES_MODULE_ENABLED      
#define HAL_EINT_MODULE_ENABLED        
#define HAL_FLASH_MODULE_ENABLED       
#define HAL_GDMA_MODULE_ENABLED         
#define HAL_GPC_MODULE_ENABLED        
#define HAL_GPIO_MODULE_ENABLED         
#define HAL_GPT_MODULE_ENABLED          
#define HAL_I2C_MASTER_MODULE_ENABLED 
#define HAL_I2S_MODULE_ENABLED
#define HAL_IRRX_MODULE_ENABLED       
#define HAL_IRTX_MODULE_ENABLED
//#define HAL_ISINK_MODULE_ENABLED       
//#define HAL_KEYPAD_MODULE_ENABLED      
#define HAL_MD5_MODULE_ENABLED          
//#define HAL_MPU_MODULE_ENABLED  
#define HAL_NVIC_MODULE_ENABLED
#define HAL_PWM_MODULE_ENABLED         
#define HAL_RTC_MODULE_ENABLED         
//#define HAL_SD_MODULE_ENABLED           
//#define HAL_SDIO_MODULE_ENABLED         
#define HAL_SHA_MODULE_ENABLED         
#define HAL_SPI_MASTER_MODULE_ENABLED   
//#define HAL_SPI_SLAVE_MODULE_ENABLED
#define HAL_TRNG_MODULE_ENABLED 
#define HAL_UART_MODULE_ENABLED        
#define HAL_WDT_MODULE_ENABLED       
#define HAL_DWT_MODULE_ENABLED

#define MTK_HAL_PLAIN_LOG_ENABLE
/*****************************************************************************
* module sub features define
*****************************************************************************/

/*This definition determines whether the demo uses PWM functions, such as LCD backlight or other module  which need change frequency or duty via PWM.*/
#ifdef HAL_PWM_MODULE_ENABLED
    #define HAL_PWM_FEATURE_SINGLE_SOURCE_CLOCK        /*please not to modify*/
#endif	


/*This definition determines whether user can use the RTC mode feature. If it is not defined, then user cannot use the RTC mode feature.*/
#ifdef HAL_RTC_MODULE_ENABLED
    #define HAL_RTC_FEATURE_SLEEP        /*please not to modify*/
#endif	

/*This definition determines whether the demo can use UART module. If it is not defined, then the demo can't use the UART module to communicate with others or for logging and the UART driver will use default timeout value for RX notice mechanism.*/
#ifdef HAL_UART_MODULE_ENABLED
    #define HAL_UART_FEATURE_VFIFO_DMA_TIMEOUT        /*please not to modify*/
#endif

/*This definition determines whether the I2S supports VFIFO function. For MT7687 platform, the user must define this definition to let I2S work normally.*/
#ifdef HAL_I2S_MODULE_ENABLED
    #define HAL_I2S_EXTENDED                        /*please not to modify*/
    #define HAL_I2S_SUPPORT_VFIFO                   /*please not to modify*/
#endif

#ifdef __cplusplus
}
#endif

#endif /* __HAL_FEATURE_CONFIG_H__ */ 

