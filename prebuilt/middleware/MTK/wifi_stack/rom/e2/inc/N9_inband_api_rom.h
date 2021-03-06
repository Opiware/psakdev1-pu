/* Copyright Statement:
 *
 */

#include "rt_config.h"
#include "rom/patch_config.h"


#define WIFI_TX_PATHS               (1)     /* MT7686 - 1x1 */


/**
 * Convert 0.5 Decibel format to 8-bit integer format.
 *
 * The format of DELTA byte is a VALID bit with 7 bits 2's complement:
 *
 *      bits 7   - valid if 1, otherwise ignore the reset bits.
 *      bits 6   - sign bit, 1 if the remaining 6 bits are positive.
 *      bits 5-0 - value bits. */
#define _db_to_int8(_b)         ((int8_t)((_b) & 0x80 ? ((_b) & 0x40 ? (_b) : (_b) & 0x7f) : 0))


/**
 * Convert 8-bit integer format to 0.5 Decibel format. */
#define _int8_to_db(_b)         ((uint8_t)(((_b) & 0x7f) | 0x40))


/**
 * make a setting a valid one. */
#define _setting_valid(_b)      ((_b) | 0x80)


/**
 * WIFI_TX_POWER_CONFIG_INIT applies default setting to wifi_tx_power_config_t.
 *
 * When a variable typed wifi_tx_power_config_t is used and needs to be
 * initialized, always use WIFI_TX_POWER_CONFIG_INIT to initialize it before
 * start to apply settings to it. Or, use memset to clear it up to ensure it
 * is empty before start to apply settings to it.
 *
 * @note the default setting in WIFI_TX_POWER_CONFIG_INIT may change in the
 *       future. */
#define WIFI_TX_POWER_CONFIG_INIT(_c)   \
    do {                                \
        rom_memset( _c, 0, sizeof(*(_c)) ); \
        (_c)->tssi_disable         = _setting_valid(1); \
        (_c)->dpd_disable          = _setting_valid(1); \
        (_c)->rate_offset_disable  = _setting_valid(0); \
    } while (0)


/**
 * WIFI_TX_RATE_DB_CONFIG_INIT applies default setting to
 * wifi_tx_rate_db_config_t.
 *
 * When a variable typed wifi_tx_rate_db_config_t is used and needs to be
 * initialized, always use WIFI_TX_RATE_DB_CONFIG_INIT to initialize it before
 * start to apply settings to it. Or, use memset to clear it up to ensure it
 * is empty before start to apply settings to it.
 *
 * @note the default setting in WIFI_TX_RATE_DB_CONFIG_INIT may change in the
 *       future. */
#define WIFI_TX_RATE_DB_CONFIG_INIT(_c) \
    do {                                \
        rom_memset( _c, 0, sizeof(*(_c)) ); \
    } while (0)


#define WIFI_TX_CONFIG_INIT(_c)                         \
    do {                                                \
        WIFI_TX_POWER_CONFIG_INIT(&((_c)->tx_cfg));     \
        WIFI_TX_RATE_DB_CONFIG_INIT(&((_c)->rate_tbl)); \
    } while (0)


/*******************************************************************************
 *                             D A T A   T Y P E S
 *******************************************************************************/


/**
 * The TX settings.
 *
 * When a variable, say cfg,  of wifi_tx_power_config_t is to be used, always
 * use WIFI_TX_POWER_DEFAULT to initialize it before start to modify its
 * setting.
 *
 *      wifi_tx_power_config_t  cfg;
 *      WIFI_TX_POWER_CONFIG_INIT(&cfg);
 *
 * the values in the power config have the following DELTA format:
 *
 * bit7:    1 = valid.
 *          0 = invalid, ignore the remaining bits.
 * bit6:    1 = negative
 *          0 = positive
 * bit5-0:  value
 *
 * When 0 is supplied to some fields, it is not taken by the F/W. Instead, the
 * original setting is preserved. */
typedef struct wifi_tx_power_config_s
{
    uint8_t     target_power;           ///< target power in 0.5 dBm unit.

    uint8_t     low_ch_power_offset;    ///< used when channel is  1 -  5.
    uint8_t     mid_ch_power_offset;    ///< used when channel is  6 - 10.
    uint8_t     high_ch_power_offset;   ///< used when channel is 11 - 14.

    uint8_t     reserved0;              ///< reserved for 20/40 BW TX Power Delta for 2.4G
    uint8_t     tssi_disable;           ///< disable TSSI if 0x81.
                                        ///< enable TSSi if 0x80.
                                        ///< other values are ignored.
    uint8_t     dpd_disable;            ///< disable DPD if 0x81.
                                        ///< enable DPD if 0x80.
                                        ///< other values are ignored.
    uint8_t     rate_offset_disable;    ///< disable rate offset table if 0x81.
                                        ///< enable rate offset table if 0x80.
                                        ///< other values are ignored.

} wifi_tx_power_config_t;


/**
 * the values in the rate power config tables have the following DELTA format:
 *
 * bit7:    1 = valid.
 *          0 = invalid, ignore the remaining bits.
 * bit6:    1 = negative
 *          0 = positive
 * bit5-0:  value
 *
 * When 0 is supplied to some fields, it is not taken by the F/W. Instead, the
 * original setting is preserved. */
typedef struct wifi_tx_rate_offset_config_s
{
    uint8_t     cck_1m2m;               ///< 802.11b CCK BPSK
    uint8_t     cck_55m_11m;            ///< 802.11b DSSS QPSK

    uint8_t     ofdm_6m_9m;             ///< 802.11g CCK BPSK
    uint8_t     ofdm_12m_18m;           ///< 802.11g DSSS QPSK
    uint8_t     ofdm_24m_36m;           ///< 802.11g 16-QAM
    uint8_t     ofdm_48m;               ///< 802.11g 64-QAM
    uint8_t     ofdm_54m;               ///< 802.11g CCK BPSK

    uint8_t     ht20_mcs_0;             ///< 802.11n CCK BPSK
    uint8_t     ht20_mcs_1_2;           ///< 802.11n DSSS QPSK
    uint8_t     ht20_mcs_3_4;           ///< 802.11n 16-QAM
    uint8_t     ht20_mcs_5;             ///< 802.11n 64-QAM
    uint8_t     ht20_mcs_6;             ///< 802.11n 64-QAM
    uint8_t     ht20_mcs_7;             ///< 802.11n 64-QAM

    uint8_t     ht40_mcs_0;             ///< 802.11n CCK BPSK
    uint8_t     ht40_mcs_1_2;           ///< 802.11n DSSS QPSK
    uint8_t     ht40_mcs_3_4;           ///< 802.11n 16-QAM
    uint8_t     ht40_mcs_5;             ///< 802.11n 64-QAM
    uint8_t     ht40_mcs_6;             ///< 802.11n 64-QAM
    uint8_t     ht40_mcs_7;             ///< 802.11n 64-QAM
    uint8_t     ht40_mcs_32;            ///< 802.11n BPSK

} wifi_tx_rate_db_config_t;


typedef struct _EXT_CMD_TX_POWER_CTRL_T
{
    wifi_tx_power_config_t      tx_cfg; //< Includes the setting of
                                        //< target_power, channel-based
                                        //< power offsets, and the toggle
                                        //< switches of TSSI, DPD, and
                                        //< rate-based power offsets.

    wifi_tx_rate_db_config_t    rate_tbl; //< The list of rate-based power
                                          //< offsets.

} EXT_CMD_TX_POWER_CTRL_T;

typedef struct _EXT_CMD_TX_CHAN_SWITCH_T
{
    uint8_t             control_ch;         ///< Control channel
    uint8_t             central_ch;         ///< Central channel
    uint8_t             bandwidth;          ///< Not used, set to 0.
    uint8_t             ucTxStreamNum;      ///< Not used, set to 0.

    uint8_t             ucRxStreamNum;      ///< Not used, set to 0.
    uint8_t             aucReserve0[7];     ///< Reserved for 32bit alignment.
    uint8_t             aucTxPowerSKU[21];  ///< Not used.
    uint8_t             aucReserve1[3];     ///< Reserved for 32bit alignment.

} EXT_CMD_TX_CHAN_SWITCH_T;


#define EXT_CMD_ID_CHANNEL_SWITCH			0x08
#define EXT_CMD_ID_SET_TX_POWER_CONTROL 	0x11




