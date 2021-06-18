/* Copyright Statement:
 *
 */

/*
 ****************************************************************************
 PART 2:
 Essential Information of NOR Flash Geometry Layout Information
 ****************************************************************************
*/
/*******************************************************************************
   NOTICE: Fill the flash region information table, a region is the memory space
           that contains continuous sectors of equal size. Each region element
           in the table is the format as below:
           {S_sector, N_sector},
           S_sector: the size of sector in the region
           N_sector: the number of sectors in the region
 *******************************************************************************/
#define REGION_INFO_LAYOUT    {0x1000, 64},

#ifndef __NVRAM_BACKUP_PARTITION__
#define DISK0_REGION_INFO_LAYOUT    {0x1000, 64},
#define DISK1_REGION_INFO_LAYOUT    {0x1000, 64},
#endif

#define ENTIRE_DISK_REGION_INFO_LAYOUT    {0x1000, 1024},

/*******************************************************************************
   NOTICE. Modify the value of TOTAL_BLOCKS, which is the sum of the number of
           sectors in all regions.
           Note : The Maximum value of TOTAL_BLOCKS is (127).
 *******************************************************************************/

#ifdef __NVRAM_BACKUP_PARTITION__
#define TOTAL_BLOCKS    (NOR_ALLOCATED_FAT_SPACE/NOR_BLOCK_SIZE)+(((NVRAM_BACKUP_PARTITION_SIZE + NOR_BLOCK_SIZE - 1) & ~(NOR_BLOCK_SIZE - 1))/NOR_DISK0_BLOCK_SIZE)
#else
#define TOTAL_BLOCKS    64
#endif

/*******************************************************************************
   NOTICE. Modify the value of page buffer size in WORD for page buffer program
 *******************************************************************************/
//uint32_t PAGE_BUFFER_SIZE = 64;

#define BANK_INFO_LAYOUT    {0x40000, 1}, \

/*******************************************************************************
   NOTICE. NOR FLASH BLOCKS SIZE LOOKUP TABLE
          Each entry element
          {Offset, Block_Size},
          Offset:     the offset address
          Block_Size: the size of block
 *******************************************************************************/
/*
FLASH_REGIONINFO_VAR_MODIFIER FlashBlockTBL NOTREADYYET[] =
{
    {0x0, 0x1000},
    EndBlockInfo
};
*/



#define NOR_FLASH_SIZE  0x00400000

const char FLASH_ID[] = "{0xC2, 0x28, 0x16}";

/****************************************************
 * This part is for auto-gen validity CHECK *
 * Don't modify any content in this comment section *


 * NOR_FLASH_DENSITY: 0x00400000
 * NOR_FLASH_SIZE(Mb): 32

FLASH_REGIONINFO_VAR_MODIFIER FlashRegionInfo oriRegionInfo[] =
{
   {0x1000, 64},
   EndoriRegionInfo
};


static NORBankInfo oriBankInfo[] =
{
   {0x400000, 1}, \
   EndBankInfo
};

 ****************************************************/

