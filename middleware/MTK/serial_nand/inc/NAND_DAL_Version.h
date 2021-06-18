/* Copyright Statement:
 *
 */

#ifndef NAND_DAL_VERSION_H
#define NAND_DAL_VERSION_H

// Define Max satck size for demand paging
#define MAX_DEMAND_STACK_USED_BY_NAND_DRIVER		500


#if 0
#if defined __NAND_FDM_50__

#define FDM_MARK 'F'
/* FDM version information */
#if defined(__NANDFDM_MULTI_INSTANCE__)
#if defined(__NANDFDM_TOTAL_BBM__)
#define FDM_VERSION     0x52
#define FDM_MAJOR_VER   (5)
#define FDM_MINOR_VER1  (2)
#define FDM_MINOR_VER2  (0)
#else
#define FDM_VERSION     0x51
#define FDM_MAJOR_VER   (5)
#define FDM_MINOR_VER1  (1)
#define FDM_MINOR_VER2  (0)
#endif //defined(__NANDFDM_TOTAL_BBM__)
#else
#define FDM_VERSION     0x50
#define FDM_MAJOR_VER   (5)
#define FDM_MINOR_VER1  (0)
#define FDM_MINOR_VER2  (0)
#define FDM_MINOR_VER2_EN_REPLACECNT (1)
#endif // defined(__NANDFDM_MULTI_INSTANCE__)
#define DAL_MARK 'D'
#if defined(__NFI_VERSION3_1__)
#define DAL_MAJOR_VER   (0)
#define DAL_MINOR_VER1  (0)
#if defined(MT6256)
#define DAL_VERISON     0x03	// ECC 12 bits
#define DAL_MINOR_VER2  (3)
#elif defined(MT6255)
#define DAL_VERISON     0x05	// ECC 8 bits
#define DAL_MINOR_VER2  (5)
#else
#define DAL_VERISON     0x02  // ECC 4 bit for MT6276
#define DAL_MINOR_VER2  (2)
#endif
#else
#define DAL_VERISON     0x01
#define DAL_MAJOR_VER   (0)
#define DAL_MINOR_VER1  (0)
#define DAL_MINOR_VER2  (1)
#endif


#endif /*__NAND_FDM_50__*/
#endif
#define FDM_MARK 'F'

#define FDM_VERSION     0x50
#define FDM_MAJOR_VER   (5)
#define FDM_MINOR_VER1  (0)
#define FDM_MINOR_VER2  (0)
#define FDM_MINOR_VER2_EN_REPLACECNT (1)

#define DAL_MARK 'D'

#define DAL_VERISON     0x01
#define DAL_MAJOR_VER   (0)
#define DAL_MINOR_VER1  (0)
#define DAL_MINOR_VER2  (1)

#endif /*NAND_DAL_VERSION_H*/

