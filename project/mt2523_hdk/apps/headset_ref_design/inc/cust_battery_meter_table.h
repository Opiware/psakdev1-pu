/* Copyright Statement:
 *
 */

#ifndef __CUST_BATTERY_METER_TABLE_H__
#define __CUST_BATTERY_METER_TABLE_H__

#include "battery_meter.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  BATTERY_CAPACITY_LEVEL_5   80
#define  BATTERY_CAPACITY_LEVEL_4   60
#define  BATTERY_CAPACITY_LEVEL_3   45
#define  BATTERY_CAPACITY_LEVEL_2   30
#define  BATTERY_CAPACITY_LEVEL_1   10


/* T0 -10C */
const BATTERY_PROFILE_STRUC battery_profile_t0[51] = {
    {0    , 4202},
    {2    , 4174},
    {4    , 4150},
    {6    , 4136},
    {8    , 4116},
    {10   , 4095},
    {12   , 4084},
    {14   , 4060},
    {16   , 4046},
    {18   , 4028},
    {20   , 4009},
    {22   , 3998},
    {24   , 3983},
    {26   , 3973},
    {28   , 3958},
    {30   , 3949},
    {32   , 3934},
    {34   , 3919},
    {36   , 3908},
    {38   , 3896},
    {40   , 3884},
    {42   , 3872},
    {44   , 3860},
    {46   , 3853},
    {48   , 3844},
    {50   , 3835},
    {52   , 3830},
    {54   , 3819},
    {56   , 3815},
    {58   , 3808},
    {60   , 3802},
    {62   , 3798},
    {64   , 3794},
    {66   , 3790},
    {68   , 3788},
    {70   , 3785},
    {72   , 3783},
    {74   , 3780},
    {76   , 3778},
    {78   , 3775},
    {80   , 3773},
    {82   , 3768},
    {84   , 3763},
    {86   , 3760},
    {88   , 3752},
    {90   , 3745},
    {92   , 3737},
    {94   , 3728},
    {96   , 3722},
    {98   , 3711},
    {100  , 3700}
};

/* T1 0C */
const BATTERY_PROFILE_STRUC battery_profile_t1[51] = {
    {0    , 4203},
    {2    , 4179},
    {4    , 4158},
    {6    , 4139},
    {8    , 4121},
    {10   , 4103},
    {12   , 4085},
    {14   , 4069},
    {16   , 4053},
    {18   , 4036},
    {20   , 4020},
    {22   , 4004},
    {24   , 3990},
    {26   , 3976},
    {28   , 3962},
    {30   , 3953},
    {32   , 3935},
    {34   , 3915},
    {36   , 3906},
    {38   , 3894},
    {40   , 3880},
    {42   , 3873},
    {44   , 3858},
    {46   , 3847},
    {48   , 3842},
    {50   , 3833},
    {52   , 3825},
    {54   , 3820},
    {56   , 3811},
    {58   , 3805},
    {60   , 3802},
    {62   , 3796},
    {64   , 3791},
    {66   , 3790},
    {68   , 3783},
    {70   , 3780},
    {72   , 3777},
    {74   , 3775},
    {76   , 3771},
    {78   , 3766},
    {80   , 3759},
    {82   , 3754},
    {84   , 3747},
    {86   , 3738},
    {88   , 3728},
    {90   , 3721},
    {92   , 3706},
    {94   , 3695},
    {96   , 3683},
    {98   , 3665},
    {100  , 3647}
};

/* T2 25C */
const BATTERY_PROFILE_STRUC battery_profile_t2[51] = {
    {0    , 4201},
    {2    , 4188},
    {4    , 4164},
    {6    , 4142},
    {8    , 4130},
    {10   , 4108},
    {12   , 4092},
    {14   , 4075},
    {16   , 4055},
    {18   , 4046},
    {20   , 4030},
    {22   , 4017},
    {24   , 3999},
    {26   , 3989},
    {28   , 3972},
    {30   , 3959},
    {32   , 3945},
    {34   , 3927},
    {36   , 3916},
    {38   , 3897},
    {40   , 3888},
    {42   , 3870},
    {44   , 3861},
    {46   , 3851},
    {48   , 3842},
    {50   , 3836},
    {52   , 3827},
    {54   , 3820},
    {56   , 3813},
    {58   , 3810},
    {60   , 3803},
    {62   , 3797},
    {64   , 3792},
    {66   , 3784},
    {68   , 3782},
    {70   , 3770},
    {72   , 3762},
    {74   , 3755},
    {76   , 3750},
    {78   , 3742},
    {80   , 3736},
    {82   , 3725},
    {84   , 3713},
    {86   , 3707},
    {88   , 3691},
    {90   , 3686},
    {92   , 3681},
    {94   , 3673},
    {96   , 3641},
    {98   , 3529},
    {100  , 3443}
};

/* T3 50C  */
BATTERY_PROFILE_STRUC battery_profile_t3[] = {
    {0   , 4203},
    {2   , 4183},
    {4   , 4165},
    {6   , 4143},
    {8   , 4131},
    {10  , 4114},
    {12  , 4099},
    {14  , 4078},
    {16  , 4063},
    {18  , 4048},
    {20  , 4033},
    {22  , 4018},
    {24  , 4000},
    {26  , 3991},
    {28  , 3974},
    {30  , 3961},
    {32  , 3948},
    {34  , 3935},
    {36  , 3918},
    {38  , 3899},
    {40  , 3888},
    {42  , 3876},
    {44  , 3866},
    {46  , 3852},
    {48  , 3845},
    {50  , 3836},
    {52  , 3831},
    {54  , 3822},
    {56  , 3813},
    {58  , 3809},
    {60  , 3804},
    {62  , 3797},
    {64  , 3790},
    {66  , 3788},
    {68  , 3775},
    {70  , 3763},
    {72  , 3752},
    {74  , 3745},
    {76  , 3735},
    {78  , 3726},
    {80  , 3718},
    {82  , 3710},
    {84  , 3703},
    {86  , 3691},
    {88  , 3675},
    {90  , 3672},
    {92  , 3669},
    {94  , 3663},
    {96  , 3610},
    {98  , 3559},
    {100 , 3400}
};

/* battery profile for actual temperature. The size should be the same as T1, T2 and T3 */
BATTERY_PROFILE_STRUC battery_profile_temperature[51] = {
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 }
};

/*============================================================
* <Rbat, Battery_Voltage> Table
*============================================================ */
/* T0 -10C */
const R_PROFILE_STRUC r_profile_t0[51] = {
    {5160  , 4202},
    {5342  , 4174},
    {5250  , 4150},
    {5317  , 4136},
    {5350  , 4116},
    {5400  , 4095},
    {5167  , 4084},
    {5267  , 4060},
    {5117  , 4046},
    {5192  , 4028},
    {5217  , 4009},
    {5067  , 3998},
    {5134  , 3983},
    {5034  , 3973},
    {5217  , 3958},
    {5150  , 3949},
    {4933  , 3934},
    {5200  , 3919},
    {5017  , 3908},
    {4842  , 3896},
    {5050  , 3884},
    {5167  , 3872},
    {5117  , 3860},
    {5017  , 3853},
    {4950  , 3844},
    {4983  , 3835},
    {5017  , 3830},
    {5100  , 3819},
    {5133  , 3815},
    {5209  , 3808},
    {5283  , 3802},
    {5317  , 3798},
    {5475  , 3794},
    {5700  , 3790},
    {5925  , 3788},
    {6167  , 3785},
    {6133  , 3783},
    {6050  , 3780},
    {6084  , 3778},
    {6483  , 3775},
    {6833  , 3773},
    {7259  , 3768},
    {7317  , 3763},
    {7517  , 3760},
    {8308  , 3752},
    {9150  , 3745},
    {9267  , 3737},
    {10167 , 3728},
    {10850 , 3722},
    {11208 , 3711},
    {11567 , 3700}
};

/* T1 0C */
const R_PROFILE_STRUC r_profile_t1[51] = {
    {3100  , 4203},
    {3167  , 4179},
    {3233  , 4158},
    {3233  , 4139},
    {3233  , 4121},
    {3242  , 4103},
    {3233  , 4085},
    {3233  , 4069},
    {3233  , 4053},
    {3217  , 4036},
    {3217  , 4020},
    {3192  , 4004},
    {3167  , 3990},
    {3159  , 3976},
    {3133  , 3962},
    {3133  , 3953},
    {3133  , 3935},
    {3017  , 3915},
    {3033  , 3906},
    {3017  , 3894},
    {2950  , 3880},
    {2983  , 3873},
    {2967  , 3858},
    {3000  , 3847},
    {3000  , 3842},
    {3017  , 3833},
    {3033  , 3825},
    {3050  , 3820},
    {3083  , 3811},
    {3183  , 3805},
    {3217  , 3802},
    {3225  , 3796},
    {3283  , 3791},
    {3317  , 3790},
    {3367  , 3783},
    {3450  , 3780},
    {3483  , 3777},
    {3567  , 3775},
    {3633  , 3771},
    {3683  , 3766},
    {3833  , 3759},
    {3975  , 3754},
    {4167  , 3747},
    {4384  , 3738},
    {4617  , 3728},
    {4867  , 3721},
    {5500  , 3706},
    {6434  , 3695},
    {7367  , 3683},
    {8817  , 3665},
    {10267 , 3647}
};

/* T2 25C */
const R_PROFILE_STRUC r_profile_t2[51] = {
    {800  , 4201},
    {767  , 4188},
    {800  , 4164},
    {817  , 4142},
    {783  , 4130},
    {767  , 4108},
    {800  , 4092},
    {783  , 4075},
    {783  , 4055},
    {867  , 4046},
    {850  , 4030},
    {883  , 4017},
    {900  , 3999},
    {933  , 3989},
    {950  , 3972},
    {950  , 3959},
    {950  , 3945},
    {933  , 3927},
    {900  , 3916},
    {867  , 3897},
    {850  , 3888},
    {767  , 3870},
    {800  , 3861},
    {750  , 3851},
    {783  , 3842},
    {767  , 3836},
    {800  , 3827},
    {800  , 3820},
    {800  , 3813},
    {833  , 3810},
    {817  , 3803},
    {850  , 3797},
    {850  , 3792},
    {833  , 3784},
    {867  , 3782},
    {833  , 3770},
    {809  , 3762},
    {833  , 3755},
    {850  , 3750},
    {850  , 3742},
    {883  , 3736},
    {850  , 3725},
    {867  , 3713},
    {900  , 3707},
    {883  , 3691},
    {909  , 3686},
    {950  , 3681},
    {1092 , 3673},
    {1100 , 3641},
    {1100 , 3529},
    {1217 , 3443}
};

/* T3 50C */
const R_PROFILE_STRUC r_profile_t3[51] = {
    {400 , 4203},
    {409 , 4183},
    {417 , 4165},
    {417 , 4143},
    {417 , 4131},
    {417 , 4114},
    {433 , 4099},
    {450 , 4078},
    {467 , 4063},
    {500 , 4048},
    {500 , 4033},
    {483 , 4018},
    {500 , 4000},
    {517 , 3991},
    {550 , 3974},
    {550 , 3961},
    {567 , 3948},
    {559 , 3935},
    {500 , 3918},
    {500 , 3899},
    {467 , 3888},
    {442 , 3876},
    {450 , 3866},
    {417 , 3852},
    {450 , 3845},
    {450 , 3836},
    {467 , 3831},
    {467 , 3822},
    {467 , 3813},
    {500 , 3809},
    {509 , 3804},
    {483 , 3797},
    {517 , 3790},
    {550 , 3788},
    {500 , 3775},
    {459 , 3763},
    {467 , 3752},
    {500 , 3745},
    {467 , 3735},
    {483 , 3726},
    {475 , 3718},
    {467 , 3710},
    {467 , 3703},
    {517 , 3691},
    {450 , 3675},
    {467 , 3672},
    {517 , 3669},
    {583 , 3663},
    {533 , 3610},
    {550 , 3559},
    {667 , 3400}
};

/* r-table profile for actual temperature. The size should be the same as T1, T2 and T3 */
R_PROFILE_STRUC r_profile_temperature[51] = {
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 },
    {0  , 0 }
};

#ifdef __cplusplus
}
#endif

#endif /*__CUST_BATTERY_METER_TABLE_H__*/

