/* Copyright Statement:
 *
 */

#ifndef __BSP_FLASH_CONFIG_H__
#define __BSP_FLASH_CONFIG_H__

typedef struct {
    char		*name;                     /* flash name */
    unsigned char	id;                /* Manufacturer ID */  
    unsigned long	jedec_id;          /* Device ID */ 
    unsigned long	page_size;         /* set 512 */
    unsigned int	n_pages;            /* flash size/512  */

    unsigned char	quad_program_cmd;  /* SPIQ write Command */
    unsigned char	quad_read_cmd;     /* SPIQ read Command */
    unsigned char	qpi_read_cmd;      /* not used */
}flash_info_t;

typedef enum {
    EX_SF_UNDEF = 0
    , EX_SPI      = 1
    , EX_SPIQ     = 2
    , EX_QPI      = 3
} FLASH_MODE_Enum;

unsigned char customer_flash_suspend_bit(void);

const unsigned char* customer_switch_spi_mode_command(void);

const unsigned char* customer_switch_spiq_mode_command(void);

unsigned char customer_flash_read_SR2_comand(void);	

/*should call this api first in hal_flash_init to register  flash*/
const flash_info_t* customer_flash_register(void);

#endif
