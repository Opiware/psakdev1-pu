/* Copyright Statement:
 *
 */

/****************************************************************************
    Module Name:
    I2C

    Abstract:
    Two I2C master modules and 7-bit address is supported.

    Revision History:
    Who         When            What
    --------    ----------      ------------------------------------------
***************************************************************************/
#include "hal_i2c_master.h"
#if defined(HAL_I2C_MASTER_MODULE_ENABLED)
#include <stdio.h>
#include <string.h>
#include "type_def.h"
#include "mt7687.h"
#include "i2c.h"
#include "hal_I2C.h"
#include "dma_sw.h"
#include "hal_log.h"

static UINT8 gucI2C1Enable = 0;
static UINT8 gucI2C2Enable = 0;
static UINT8 gucI2C1RxGDMAIdx = 0;
static UINT8 gucI2C1TxGDMAIdx = 0;
static UINT8 gucI2C2RxGDMAIdx = 0;
static UINT8 gucI2C2TxGDMAIdx = 0;

int32_t i2c_configure(uint8_t index, uint8_t frequency)
{
    INT32 ret = 0;
    ENUM_HAL_RET_T hal_ret = HAL_RET_FAIL;

    if (index & (~(BIT(0)))) {
        // only support index 0:I2C1, 1:I2C2
        return -1;
    }

    hal_ret = halI2CInit(index, 0, 0, 0, 3);
    if (HAL_RET_FAIL == hal_ret) {
        return -1;
    }

    hal_ret = halI2CMasterCtrl(index, (ENUM_I2C_CLK_T)frequency);
    if (HAL_RET_FAIL == hal_ret) {
        return -2;
    }

    return ret;
}

int32_t i2c_write(uint8_t index, uint8_t slave_address, const uint8_t *data, uint16_t length)
{
    INT32 ret = 0;
    UINT8 ucTxGDMAIdx = 0;
    ENUM_HAL_RET_T hal_ret = HAL_RET_FAIL;

    if (index & (~(BIT(0)))) {
        // only support index 0:I2C1, 1:I2C2

        log_hal_error("[I2C][i2c_write] error i2c number.\r\n");
        return -1;
    }

    if (0 == index) {
        ucTxGDMAIdx = gucI2C1TxGDMAIdx;
    } else {
        ucTxGDMAIdx = gucI2C2TxGDMAIdx;
    }
    hal_ret = halI2CGDMANormalWrite(index, ucTxGDMAIdx, slave_address, data, length);

    if (HAL_RET_FAIL == hal_ret) {
        return -2;
    }

    return ret;
}

int32_t i2c_write_via_mcu(uint8_t index, uint8_t slave_address, const uint8_t *data, uint16_t length)
{
    INT32 ret = 0;
    ENUM_HAL_RET_T hal_ret = HAL_RET_FAIL;

    if (index & (~(BIT(0)))) {
        log_hal_error("[I2C][i2c_write_via_mcu] error i2c number.\r\n");
        // only support index 0:I2C1, 1:I2C2
        return -1;
    }

    hal_ret = halI2CNormalWrite(index, slave_address, data, length);

    if (HAL_RET_FAIL == hal_ret) {
        return -2;
    }

    return ret;
}

int32_t i2c_read(uint8_t index, uint8_t slave_address, uint8_t *data, uint16_t length)
{
    INT32 ret = 0;
    UINT8 ucRxGDMAIdx = 0;
    ENUM_HAL_RET_T hal_ret = HAL_RET_FAIL;

    if (index & (~(BIT(0)))) {
        // only support index 0:I2C1, 1:I2C2
        log_hal_error("[I2C][i2c_read] error i2c number.\r\n");
        return -1;
    }

    if (0 == index) {
        ucRxGDMAIdx = gucI2C1RxGDMAIdx;
    } else {
        ucRxGDMAIdx = gucI2C2RxGDMAIdx;
    }
    hal_ret = halI2CGDMANormalRead(index, ucRxGDMAIdx, slave_address, data, length);

    if (HAL_RET_FAIL == hal_ret) {
        return -2;
    }

    return ret;
}

int32_t i2c_read_via_mcu(uint8_t index, uint8_t slave_address, uint8_t *data, uint16_t length)
{
    INT32 ret = 0;
    ENUM_HAL_RET_T hal_ret = HAL_RET_FAIL;

    if (index & (~(BIT(0)))) {
        // only support index 0:I2C1, 1:I2C2
        log_hal_error("[I2C][i2c_read_via_mcu] error i2c number.\r\n");
        return -1;
    }

    hal_ret = halI2CNormalRead(index, slave_address, data, length);

    if (HAL_RET_FAIL == hal_ret) {
        return -2;
    }

    return ret;
}

int32_t i2c_read_write(uint8_t index, i2c_package_information_t *package_information)
{
    INT32 ret = 0;
    UINT8 ucRxGDMAIdx = 0;
    UINT8 ucTxGDMAIdx = 0;
    ENUM_HAL_RET_T hal_ret = HAL_RET_FAIL;

    if (index & (~(BIT(0)))) {
        // only support index 0:I2C1, 1:I2C2
        log_hal_error("[I2C][i2c_read] error i2c number.\r\n");
        return -1;
    }

    if (0 == index) {
        ucRxGDMAIdx = gucI2C1RxGDMAIdx;
        ucTxGDMAIdx = gucI2C1TxGDMAIdx;
    } else {
        ucRxGDMAIdx = gucI2C2RxGDMAIdx;
        ucTxGDMAIdx = gucI2C2TxGDMAIdx;
    }

    hal_ret = halI2CGDMAGeneralRW(index,
                                  ucTxGDMAIdx,
                                  ucRxGDMAIdx,
                                  package_information->ucSlaveAddress,
                                  package_information->pucTxData,
                                  package_information->pucRxData,
                                  package_information->ucPktNum,
                                  package_information->ucPkt0RW,
                                  package_information->u2Pkt0Len,
                                  package_information->ucPkt1RW,
                                  package_information->u2Pkt1Len,
                                  package_information->ucPkt2RW,
                                  package_information->u2Pkt2Len);

    if (HAL_RET_FAIL == hal_ret) {
        return -2;
    }

    return ret;
}

int32_t i2c_read_write_via_mcu(uint8_t index, i2c_package_information_t *package_information)
{
    INT32 ret = 0;
    ENUM_HAL_RET_T hal_ret = HAL_RET_FAIL;

    if (index & (~(BIT(0)))) {
        // only support index 0:I2C1, 1:I2C2
        log_hal_error("[I2C][i2c_read_via_mcu] error i2c number.\r\n");
        return -1;
    }

    hal_ret = halI2CGeneralRW(index,
                              package_information->ucSlaveAddress,
                              package_information->pucTxData,
                              package_information->pucRxData,
                              package_information->ucPktNum,
                              package_information->ucPkt0RW,
                              package_information->u2Pkt0Len,
                              package_information->ucPkt1RW,
                              package_information->u2Pkt1Len,
                              package_information->ucPkt2RW,
                              package_information->u2Pkt2Len);

    if (HAL_RET_FAIL == hal_ret) {
        return -2;
    }

    return ret;
}



int32_t i2c_enable(uint8_t index)
{
    INT32 ret = 0;

    if (index & (~(BIT(0)))) {
        // only support index 0:I2C1, 1:I2C2
        return -1;
    }

    if (0 == index) {
        if (0 == gucI2C1Enable) {
            gucI2C1RxGDMAIdx = DMA_GetChannel(DMA_I2C1_RX);
            DMA_Clock_Enable(gucI2C1RxGDMAIdx);

            gucI2C1TxGDMAIdx = DMA_GetChannel(DMA_I2C1_TX);
            DMA_Clock_Enable(gucI2C1TxGDMAIdx);
            gucI2C1Enable = 1;
        }
    } else {
        if (0 == gucI2C2Enable) {
            gucI2C2RxGDMAIdx = DMA_GetChannel(DMA_I2C2_RX);
            DMA_Clock_Enable(gucI2C2RxGDMAIdx);

            gucI2C2TxGDMAIdx = DMA_GetChannel(DMA_I2C2_TX);
            DMA_Clock_Enable(gucI2C2TxGDMAIdx);
            gucI2C2Enable = 1;
        }
    }

    return ret;
}

int32_t i2c_disable(uint8_t index)
{
    INT32 ret = 0;

    if (index & (~(BIT(0)))) {
        // only support index 0:I2C1, 1:I2C2
        return -1;
    }

    if (0 == index) {
        if (1 == gucI2C1Enable) {
            DMA_FreeChannel(gucI2C1RxGDMAIdx);
            DMA_Clock_Disable(gucI2C1RxGDMAIdx);

            DMA_FreeChannel(gucI2C1TxGDMAIdx);
            DMA_Clock_Disable(gucI2C1TxGDMAIdx);
            gucI2C1Enable = 0;
        }
    } else {
        if (1 == gucI2C2Enable) {
            DMA_FreeChannel(gucI2C2RxGDMAIdx);
            DMA_Clock_Disable(gucI2C2RxGDMAIdx);

            DMA_FreeChannel(gucI2C2TxGDMAIdx);
            DMA_Clock_Disable(gucI2C2TxGDMAIdx);
            gucI2C2Enable = 0;
        }
    }

    return ret;
}

#endif
