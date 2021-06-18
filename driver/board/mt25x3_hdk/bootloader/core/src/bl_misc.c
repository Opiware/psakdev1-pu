/* Copyright Statement:
 *
 */

#include "bl_misc.h"
#include "bl_mtk_bb_reg.h"

#define BL_CONFG_BASE   (0xA2010000)
#define BL_SYSTEM_INFOD ((BL_P_UINT_32)(BL_CONFG_BASE+0x0224))//(BL_CONFG_BASE+0x0224)
#define BL_HW_MISC3     ((BL_P_UINT_32)(BL_CONFG_BASE+0x0234))//(BL_CONFG_BASE+0x0234)
#define BL_PLL_RSV_CON0 ((BL_P_UINT_32)(0xA2040360))

void bl_bonding_io_reg(void)
{
    unsigned int bond_sta;
    unsigned int hw_misc3;
    unsigned int bond_extsf;
    unsigned int bond_psram;
    unsigned int bond_gnss;
    unsigned int bond_sipsf_18v;

    unsigned int bond_pu = 0xF;
    unsigned int bond_pd = 0x0;

    bond_sta = *BL_SYSTEM_INFOD;//(unsigned int *)(BL_SYSTEM_INFOD);
    hw_misc3 = *BL_HW_MISC3;//(unsigned int *)(BL_HW_MISC3);

    bond_extsf     = (bond_sta >> 10) & 0x1;
    bond_psram     = (bond_sta >> 7) & 0x1;;
    bond_gnss      = (bond_sta >> 3) & 0x1;;
    bond_sipsf_18v = (bond_sta >> 2) & 0x1;;

    if (!bond_psram) {
        bond_pu &= 0x7;
        bond_pd |= 0x8;
    }
    if (!bond_extsf) {
        bond_pu &= 0xB;
        bond_pd |= 0x4;
    }
    if (!bond_gnss) {
        bond_pu &= 0xD;
        bond_pd |= 0x2;
    }
    if (!bond_sipsf_18v) {
        bond_pu &= 0xE;
        bond_pd |= 0x1;
    }

    (*((volatile unsigned int *)(BL_HW_MISC3)) = (unsigned int)(bond_pu << 12) |  (bond_pd << 8) | (hw_misc3 & 0x1));
}

void bl_d2d_io_pull_down(void)
{
    (*((volatile unsigned int *)(BL_PLL_RSV_CON0)) = (unsigned int)(0x11));
}
