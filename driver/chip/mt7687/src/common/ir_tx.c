/* Copyright Statement:
 *
 */

/****************************************************************************
    Module Name:
    IR TX

    Abstract:
    IR Tx supports NEC, RC5, RC6 protocol.
    And software-pulse-width mode is provided to support user defined waveform which is indicated by high/low width in time unit.
    Interrupt is raised to indicate Tx done.

    Revision History:
    Who         When            What
    --------    ----------      ------------------------------------------
***************************************************************************/

#include "hal_platform.h"

#ifdef HAL_IRTX_MODULE_ENABLED

#include "type_def.h"
#include "mt7687.h"

#include "ir_tx.h"
#include "low_hal_irtx.h"


static UINT8 g_irtx_mode = 0;

int32_t ir_tx_configure(uint8_t mode)
{
    if (IR_TX_PROTOCOL_NUM <= mode) {
        return -1;
    }

    halIrTxInit(1, 0, 1);

    if (IR_TX_RC6 == mode) {
        // RC6 logical 0/1 is inverted with RC5(design default).
        if (halIrTxConfig((ENUM_IR_PROTOCOL)mode, 1, 0, 0, 0, 0, 0, 0, 0)) {
            return -1;
        }
    } else {
        if (halIrTxConfig((ENUM_IR_PROTOCOL)mode, 0, 0, 0, 0, 0, 0, 0, 0)) {
            return -1;
        }
    }

    g_irtx_mode = mode;

    return 0;
}

int32_t ir_tx_send(uint32_t data0, uint32_t data1, uint32_t data2, uint8_t bit_length, uint8_t repeat_code)
{
    if (IR_TX_NEC == g_irtx_mode) {
        bit_length = bit_length + 1; // add 1 for "NEC leading signal"
    } else if (IR_TX_RC6 == g_irtx_mode) {
        // Data inverse setted in ir_tx_configure not affect "Field (3bits) and Toggle (1bit)".
        // Inverse first 4 bits.
        data0 = ((data0 & (~(BITS(0, 3)))) | ((~data0) & BITS(0, 3)));
    }

    if (halIrTxSend(data0, data1, data2, bit_length, repeat_code)) {
        return -1;
    }

    return 0;
}

int32_t ir_tx_pulse_width_configure(uint16_t frequency, uint8_t duty_cycle)
{
    halIrTxInit(1, 0, 0); // RegOrder and BitOrder are meaningless for pulse_width mode.
    if (halIrTxConfig(IR_SW_PULSE_WIDTH, 0, 0, 0, 0, 0, 0, frequency, duty_cycle)) {
        return -1;
    }
    return 0;
}

int32_t ir_tx_pulse_width_send(uint8_t data_length, uint8_t *data, uint8_t base_period_us)
{
    if (halIrTxPWSend(data_length, data, base_period_us)) {
        return -1;
    }
    return 0;
}

int32_t ir_tx_interrupt_clear()
{
    halIrTxClearInterrupt();
    return 0;
}

#endif

