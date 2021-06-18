/* Copyright Statement:
 *
 */

#ifndef _INBAND_FUNCTIONS_PATCH_H
#define _INBAND_FUNCTIONS_PATCH_H

#define WRITE	0
#define READ	1


#define ERP_PROTECTION_MASK (0x1f << 24)
#define ERP_PROTECTION(p)	(((p) & 0x1f) << 24)


#define RTS_THRESHOLD_MASK			(0xfffff)
#define RTS_THRESHOLD(_p)			(((_p) & 0xfffff))
#define RTS_PKT_NUM_THRESHOLD_MASK	(0x7f << 25)
#define RTS_PKT_NUM_THRESHOLD(_p)	(((_p) & 0x7f) << 25)
#define MM_PROTECTION		(1 << 16)
#define GF_PROTECTION		(1 << 17)
#define PROTECTION_MODE 	(1 << 19)
#define BW40_PROTECTION		(1 << 20)

#define RIFS_PROTECTION		(1 << 21)
#define BW80_PROTECTION		(1 << 22)
#define BW160_PROTECTION	(1 << 23)

#define ERP_PROTECTION_MASK (0x1f << 24)
#define ERP_PROTECTION(p)	(((p) & 0x1f) << 24)

#endif /* _INBAND_FUNCTIONS_PATCH_H */