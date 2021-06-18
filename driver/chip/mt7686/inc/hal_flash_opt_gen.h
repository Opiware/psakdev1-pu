/* Copyright Statement:
 *
 */

/*
 *******************************************************************************
 PART 1:
   FLASH CONFIG Options Definition here
 *******************************************************************************
*/


#define __PAGE_BUFFER_PROGRAM__
#define __SERIAL_FLASH__
#define SF_DAL_MXIC
#define SF_DAL_WINBOND
#define __NON_INTEL_SIBLEY__


#define __SINGLE_BANK_NOR_DEVICE__


/*
 *******************************************************************************
 PART 2:
   FLASH FDM FEATURE CONFIG PARAMETERS translated from Manual custom_Memorydevice.h
 *******************************************************************************
*/

#define BUFFER_PROGRAM_ITERATION_LENGTH  (64)

/*
 *******************************************************************************
 PART 3:
   FLASH GEOMETRY translated from MEMORY DEVICE DATABASE
 *******************************************************************************
*/

/* NOR flash maximum block size (Byte) in file system region */
#define NOR_BLOCK_SIZE  0x1000
#define NOR_DISK0_BLOCK_SIZE 0x0

/* NAND flash total size (MB). PLEASE configure it as 0 if it is unknown. */
#define NAND_TOTAL_SIZE 0

/* NAND flash block size (KB). PLEASE configure it as 0 if it is unknown. */
#define NAND_BLOCK_SIZE 0

/*
 *******************************************************************************
 PART 4:
   FLASH FAT CONFIG translated from Manual custom_Memorydevice.h
 *******************************************************************************
*/



#define NOR_FLASH_BASE_ADDRESS_DEFAULT     (0x003C0000)
#define NOR_ALLOCATED_FAT_SPACE_DEFAULT    (0x00040000)
#define FOTA_DM_FS_OFFSET 0x0
#define FOTA_DM_FS_SECTOR_OFFSET 0

/*
 *******************************************************************************
 PART 6:
   FOTA UPDATABLE FLASH AREA
 *******************************************************************************
*/

#ifdef __FOTA_DM__
#error "Error! FOTA_ENABLE should not be defined!"
#endif /* __FOTA_DM__ */


#define CONFIG_FOTA_NOR_REGION_DEF \


#define CONFIG_FOTA_NOR_BLOCK_DEF \


#define CONFIG_FOTA_NOR_BANK_DEF \


