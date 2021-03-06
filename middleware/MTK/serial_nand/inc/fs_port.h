/* Copyright Statement:
 *
 */

#ifndef NAND_FAT_FS_H
#define NAND_FAT_FS_H

#include <assert.h>


#define FS_FMT_SINGLE_FAT       0x00000100L
#define FS_FMT_FORCE_LOW_LEVEL  0x00000200L
#define FS_FMT_NO_LOW_LEVEL     0x00000400L
#define FS_FMT_GET_DATA_SECTOR  0x00000800L
#define FS_FMT_FAT_12           0x00001000L
#define FS_FMT_FAT_16           0x00002000L
#define FS_FMT_FAT_32           0x00004000L
#define FS_FMT_NO_FAT_32        0x00008000L

#define FS_IOCTRL_QUERY_NAND_INFO (0xF)


/* Structure of partition record */
typedef void (* FS_FormatCallback)(const char *DeviceName, int Action, uint32_t Total, uint32_t Completed);

typedef struct {
    uint8_t   BootIndicator; /* 0x80 for bootable, 0 otherwise */
    uint8_t   StartHead;     /* 0 based */
    uint8_t   StartSector;   /* 1 based, bits 0-5 */
    uint8_t   StartTrack;    /* 0 based, bits 0-7, take bits 8,9 from StartSector */
    uint8_t   OSType;        /* FAT-12: 1, FAT-16: 4, 6, 14, FAT-32: 11, 12 */
    uint8_t   EndHead;       /* see StartHead */
    uint8_t   EndSector;     /* see StartSector */
    uint8_t   EndTrack;      /* see StartTrack */

    /*
     * offset to first sector of partition data
     * for primary partitions, this is the absolute
     * LBA of the boot sector
     */
    uint32_t  RelativeSector;
    uint32_t  Sectors;       /* number of sectors in partition */
} FS_PartitionRecord;

typedef struct {
    uint8_t BootCode[512 - 4 * sizeof(FS_PartitionRecord) - sizeof(uint16_t)];
    FS_PartitionRecord PTable[4];
    uint16_t Signature;
} FS_MasterBootRecord;


typedef enum {
    FS_DEVICE_UNKNOWN,
    FS_DEVICE_FLOPPY,
    FS_DEVICE_FDISK
} FS_DRIVER_DEVICE_ENUM;


typedef struct {
    uint8_t     PhysicalDiskNumber;
    uint8_t     CurrentHead;
    uint8_t     Signature;
    uint32_t    SerialNumber;
    uint8_t     Label[11];
    char       SystemID[8];
} FS_ExtendedBIOSParameter;


typedef struct {
    char         OEMName[8];
    uint16_t     BytesPerSector;
    uint8_t      SectorsPerCluster;
    uint16_t     ReservedSectors;
    uint8_t      NumberOfFATs;
    uint16_t     DirEntries;
    uint16_t     SectorsOnDisk;
    uint8_t      MediaDescriptor;
    uint16_t     SectorsPerFAT;
    uint16_t     SectorsPerTrack;
    uint16_t     NumberOfHeads;
    uint32_t     NumberOfHiddenSectors;
    uint32_t     TotalSectors;
    union {
        struct {
            FS_ExtendedBIOSParameter BPB;
        } _16;
        struct {
            uint32_t     SectorsPerFAT;
            uint16_t     Flags;
            uint16_t     Version;
            uint32_t     RootDirCluster;
            uint16_t     FSInfoSector;
            uint16_t     BackupBootSector;
            uint8_t     Reserved[12];
            FS_ExtendedBIOSParameter BPB;
        } _32;
    } E;
} FS_BIOSParameter;

typedef struct {
    uint8_t NearJump[3];
    FS_BIOSParameter BP;
    uint8_t BootCode[512 - 3 - sizeof(FS_BIOSParameter) - sizeof(uint16_t)];
    uint16_t Signature;
} FS_BootRecord;


typedef struct __fsdriver {
    int  (* MountDevice)    (void *DriveData, int DeviceNumber, int DeviceType, uint32_t Flags);
    int  (* ShutDown)       (void *DriveData);
    int  (* ReadSectors)    (void *DriveData, uint32_t Sector, uint32_t Sectors, void *Buffer);
    int  (* WriteSectors)   (void *DriveData, uint32_t Sector, uint32_t Sectors, void *Buffer);
    int  (* MediaChanged)   (void *DriveData);
    int  (* DiscardSectors) (void *DriveData, uint32_t Sector, uint32_t Sectors);
    int  (* GetDiskGeometry)(void *DriveData, FS_PartitionRecord *DiskGeometry, uint8_t *MediaDescriptor);
    int  (* LowLevelFormat) (void *DriveData, const char *DeviceName, FS_FormatCallback Progress, uint32_t Flags);
    int  (* NonBlockWriteSectors)   (void *DriveData, uint32_t Sector, uint32_t Sectors, void *Buffer);
    int  (* RecoverableWriteSectors)(void *DriveData, uint32_t Sector, uint32_t Sectors, void *Buffer);
    int  (* ResumeSectorStates)     (void   *DriveData);
    int  (* HighLevelFormat)(void *DriveData, uint32_t BaseSector);
    int  (* RecoverDisk)    (void *DriveData);
    int  (* MessageAck)     (void *DriveData, int AckType);
    int  (* CopySectors)    (void *DriveData, uint32_t SrcSector, uint32_t DstSector, uint32_t Sectors);
    int  (* OTPAccess)      (void *DriveData, int type, uint32_t Offset, void *BufferPtr, uint32_t Length);
    int  (* OTPQueryLength) (void *DriveData, uint32_t *Length);
    int  (* IOCtrl)         (void *DriveData, uint32_t CtrlAction, void *CtrlData);   // For device IO control
} FS_Driver;


//#define  ASSERT     {while(1);}

#define ASSERT(expr)\
   do{\
         if(!(expr))\
         {\
            assert(0);\
            return;\
         }\
     }while(0);
#define ASSERT_RET(expr, ret)\
   do{\
         if(!(expr))\
         {\
            assert(0);\
            return ret;\
         }\
     }while(0);


#endif
