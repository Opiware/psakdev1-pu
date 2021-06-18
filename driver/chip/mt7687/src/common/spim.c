/* Copyright Statement:
 *
 */

#include "hal_spi_master.h"
#ifdef HAL_SPI_MASTER_MODULE_ENABLED

#include "stdio.h"
#include "hal_spim.h"
#include "spim.h"
#include "type_def.h"
#include "hal_pinmux.h"
#include "low_hal_gpio.h"

#define MAX_WRITE_BUF_HALF_DUPLEX 36

#define MAX_READ_BUF_HALF_DUPLEX  32

#define MAX_DATA_BUF_HALF_DUPLEX  32

volatile static int32_t spi_ok_cnt = 0;
static uint32_t quotient = 0;

void spim_Lisr(void)
{
    spi_ok_cnt++;
    if (spi_ok_cnt == (quotient + 1)) {
        hal_gpio_set_output(g_spi_master_cs_n, HAL_GPIO_DATA_HIGH);
        spi_ok_cnt = 0;
    }
}

int32_t spim_init(uint32_t setting, uint32_t clock)
{
    INT32 ret = 0;

    spim_isr_Register(spim_Lisr);

    hal_gpio_set_direction(g_spi_master_cs_n, HAL_GPIO_DIRECTION_OUTPUT);
    setting = setting | SPI_MASTER_BIDIR_MODE_DISABLE | SPI_MASTER_SERIAL_MODE_STANDARD | SPI_MASTER_MB_MODE_ENABLE;
    ret = halSpim_init(setting, clock);
    hal_gpio_set_output(g_spi_master_cs_n, HAL_GPIO_DATA_HIGH);
    return (int32_t)ret;
}

static uint32_t spim_fill_in_data(uint8_t *buf, uint32_t write_buf_cnt, uint32_t regVal, uint32_t remainder)
{
    uint32_t op_addr = 0;
    if (regVal == SPI_MASTER_MB_MSB_FIRST) {
        if (remainder == 1) {
            op_addr = (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 0) << 0);
        } else if (remainder == 2) {
            op_addr = (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 0) << 8) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 1) << 0);
        } else if (remainder == 3) {
            op_addr = (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 0) << 16) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 1) << 8) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 2) << 0);
        } else if (remainder == 4) {
            op_addr = (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 0) << 24) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 1) << 16) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 2) << 8) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 3) << 0);
        }
    } else {
        if (remainder == 1) {
            op_addr = (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 0) << 0);
        } else if (remainder == 2) {
            op_addr = (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 0) << 0) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 1) << 8);
        } else if (remainder == 3) {
            op_addr = (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 0) << 0) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 1) << 8) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 2) << 16);
        } else if (remainder == 4) {
            op_addr = (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 0) << 0) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 1) << 8) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 2) << 16) | (*(buf + write_buf_cnt * MAX_WRITE_BUF_HALF_DUPLEX + 3) << 24);
        }
    }
    return op_addr;
}

int32_t spim_write(uint8_t *buf, const uint32_t buf_cnt)
{
    INT32 ret = 0;
    uint32_t op_addr = 0;
    uint32_t n_cmd_byte = 4;
    uint32_t i = 0;
    static uint32_t remainder, regVal;
    quotient = buf_cnt / MAX_WRITE_BUF_HALF_DUPLEX;
    remainder   = buf_cnt % MAX_WRITE_BUF_HALF_DUPLEX;

    regVal = DRV_Reg32(SPI_REG_MASTER);
    regVal &= (1 << 3);

    if (buf_cnt < 1) {
        return -1;
    }

    if (buf_cnt <= n_cmd_byte) {
        op_addr = spim_fill_in_data(buf, i, regVal, remainder);
        ret = spim_more_buf_trans_gpio(op_addr, buf_cnt, NULL, 0, 0);
        return ret;
    } else {
        /*Handle the quotient*/
        for (i = 0; i < quotient; i++) {
            op_addr = spim_fill_in_data(buf, i, regVal, 4);
            ret = spim_more_buf_trans_gpio(op_addr, n_cmd_byte, (buf + i * MAX_WRITE_BUF_HALF_DUPLEX + 4), MAX_DATA_BUF_HALF_DUPLEX, SPI_WRITE);
        }
        /*Handle the remainder*/
        if (remainder <= n_cmd_byte) {
            if (remainder == 0) {
                return ret;
            }
            op_addr = spim_fill_in_data(buf, i, regVal, remainder);
            ret = spim_more_buf_trans_gpio(op_addr, remainder, NULL, 0, 0);
            return ret;
        } else {
            op_addr = spim_fill_in_data(buf, i, regVal, 4);
            ret = spim_more_buf_trans_gpio(op_addr, n_cmd_byte, (buf + quotient * MAX_WRITE_BUF_HALF_DUPLEX + n_cmd_byte), remainder - n_cmd_byte, SPI_WRITE);
            return ret;
        }
    }
}

int32_t spim_read(const uint32_t cmd, const uint32_t n_cmd_byte, uint8_t *buf, const uint32_t buf_cnt)
{
    INT32 ret = 0;
    uint32_t fake_op = 0;
    uint32_t fake_cmd_byte = 0;
    uint32_t i;
    static uint32_t remainder;

    quotient = buf_cnt / MAX_READ_BUF_HALF_DUPLEX;
    remainder   = buf_cnt % MAX_READ_BUF_HALF_DUPLEX;

    if (quotient == 0) {
        ret = spim_more_buf_trans_gpio(cmd, n_cmd_byte, buf, buf_cnt, SPI_READ);
        return ret;
    } else {
        i = 0;
        spim_more_buf_trans_gpio(cmd, n_cmd_byte, (buf + i * MAX_READ_BUF_HALF_DUPLEX), MAX_DATA_BUF_HALF_DUPLEX, SPI_READ);
        for (i = 1; i < quotient; i++) {
            ret = spim_more_buf_trans_gpio(fake_op, fake_cmd_byte, (buf + i * MAX_READ_BUF_HALF_DUPLEX), MAX_DATA_BUF_HALF_DUPLEX, SPI_READ);
        }
        if (remainder != 0) {
            ret = spim_more_buf_trans_gpio(fake_op, fake_cmd_byte, (buf + quotient * MAX_READ_BUF_HALF_DUPLEX), remainder, SPI_READ);
        }
        return ret;
    }
}

#endif /* HAL_SPI_MASTER_MODULE_ENABLED */
