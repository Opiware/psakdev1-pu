/* Copyright Statement:
 *
 */


#ifndef NAND_MTD_H
#define NAND_MTD_H


/*******************************************************************************
 * Include Header Files
 *******************************************************************************/
// RHR Remove #include "reg_base.h"
// RHR Remove #include "config_hw.h"
// RHR Remove #include "drvpdn.h"
//#include "fota_error.h"
//#include "nfi_hw_info.h"
// Add for RHR
// RHR Remove     #include "dma_hw.h"
// RHR Remove     #include "kal_non_specific_general_types.h"
// RHR Remove     #include "kal_release.h"
// Add for RHR
#if 0
#define MAX_NAND_DATA_SIZE            		(NFI_MAX_DATA_SIZE_PER_PAGE)	// Max NAND page size used for MMU.
#define MAX_NAND_SPARE_SIZE             (NFI_MAX_SPARE_SIZE_PER_PAGE)
/*******************************************************************************
 *  Operation error code for NFB functions
 *******************************************************************************/
#define ERROR_NFB_SUCCESS             (ERROR_FOTA_SUCCESS)
#define ERROR_NFB_MAPPING_TBL_CHANGED (ERROR_FOTA_MAPPING_TBL_CHANGED)
#define ERROR_NFB_READ                (ERROR_FOTA_READ)
#define ERROR_NFB_PROGRAM             (ERROR_FOTA_PROGRAM)
#define ERROR_NFB_ERASE               (ERROR_FOTA_ERASE)
#define ERROR_NFB_BAD_BLOCK           (ERROR_FOTA_BAD_BLOCK)
#define ERROR_NFB_CHECKSUM            (ERROR_FOTA_NFB_CHECKSUM)
#define ERROR_NFB_ECC_CORRECTED       (ERROR_FOTA_ECC_CORRECTED)
#endif

#endif


