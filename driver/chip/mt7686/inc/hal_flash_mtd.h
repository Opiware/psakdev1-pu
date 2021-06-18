/* Copyright Statement:
 *
 */

#ifndef FLASH_MTD_H
#define FLASH_MTD_H

#ifdef __NORFLASH_DEBUGMODE__
#define DEBUG
#endif


/********************************************************/
/*                  Include Header Files                */
/********************************************************/

/********************************************************/
/*         Parameter and Function Decleration           */
/********************************************************/
#define DriverName NORFlashMtd

/*-------------------------------------------------------
 * Enhanced single bank specific
 *-------------------------------------------------------*/
/* Following functions are assumed to be atomic */
void                    Flash_ReturnReady(void);
#endif /* FLASH_MTD_H */

