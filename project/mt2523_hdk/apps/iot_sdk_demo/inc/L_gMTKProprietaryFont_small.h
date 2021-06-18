/* Copyright Statement:
 *
 */

const uint8_t AMTK_Proprietary_14_Width[1]= {
0xF ,};

const uint32_t AMTK_Proprietary_14_Offset[2]= {
0x0000,0x001B,};

const uint16_t AMTK_Proprietary_14_RangeOffset[1]= {
0,};

const uint8_t  AMTK_Proprietary_14_Data[27]= {
0x0,0x0,0x0,0x0,0xFE,0x3,0x1,0x81,0x80,0x40,0x40,0x20,0x20,0x10,0x10,0x8,
0x8,0x4,0x4,0x2,0x2,0xFF,0x1,0x0,0x0,0x0,0x0,};

const RangeData AMTK_Proprietary_14_RangeData[1]={
{65515,65515},};

const RangeDetails AMTK_Proprietary_14_RangeInfo={
1,
AMTK_Proprietary_14_RangeData
};

const sCustFontData gMTKProprietaryFont_small = {
14, 14,
11, 3,
0, 27, 500,
(uint8_t*)AMTK_Proprietary_14_Width, (uint8_t*)AMTK_Proprietary_14_Width, (uint32_t*)AMTK_Proprietary_14_Offset, (uint8_t*)AMTK_Proprietary_14_Data, (uint16_t*)AMTK_Proprietary_14_RangeOffset,
&AMTK_Proprietary_14_RangeInfo,
0X00000000,
};

