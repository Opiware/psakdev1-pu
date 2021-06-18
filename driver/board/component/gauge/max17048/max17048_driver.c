/* Copyright Statement:
 *
 */

#include "max17048_driver.h"
#include "max17048_common.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_i2c_pmic.h"
#include "hal_i2c_master.h"
#include "hal_i2c_master_internal.h"
#include "hal.h"

/*internal use*/
static unsigned char max17048_i2c_read_word(unsigned char i2c_address, unsigned char *ptr_send, unsigned char *ptr_read)
{
    pmic_i2c_send_to_receive_config_t config;
    unsigned char retry_cnt = 0, result_read;

    config.slave_address      = i2c_address;
    config.send_data          = ptr_send;
    config.send_length        = 1;
    config.receive_buffer     = ptr_read;
    config.receive_length     = 2;

    do {
        result_read = pmic_i2c_send_to_receive_polling(PMIC_I2C_MASTER, &config);
        retry_cnt++;
    } while ((result_read != 0) && (retry_cnt <= 10));

    retry_cnt--;
    return (retry_cnt);
}

/*internal use*/
static unsigned char max17048_i2c_write_word(unsigned char i2c_address, unsigned char *ptr_send)
{
    unsigned char retry_cnt = 0, result_read;

    do {
        result_read = pmic_i2c_send_polling(PMIC_I2C_MASTER, i2c_address, ptr_send, 3);
        retry_cnt++;
    } while ((result_read != 0) && (retry_cnt <= 10));

    retry_cnt--;
    return (retry_cnt);
}

void max17048_i2c_init(void)
{
    pmic_i2c_config_t config;
    config.transfer_frequency = 400;
    pmic_i2c_init(PMIC_I2C_MASTER, &config);
}

bool max17048_read_word(unsigned char i2c_address, unsigned char address, unsigned char *msb, unsigned char *lsb)
{
    unsigned char send_buffer[1], receive_buffer[2];
    unsigned int mask_pri;

    send_buffer[0] = address;

    mask_pri = save_and_set_interrupt_mask();

    if (max17048_i2c_read_word(i2c_address, send_buffer, receive_buffer) == 0) {
        restore_interrupt_mask(mask_pri);
        *msb = receive_buffer[0];
        *lsb = receive_buffer[1];
        return true;
    } else {
        restore_interrupt_mask(mask_pri);
        return false;
    }
}

bool max17048_write_word(unsigned char i2c_address, unsigned char address, unsigned char msb, unsigned char lsb)
{
    unsigned char send_buffer[3];
    unsigned int mask_pri;

    send_buffer[0] = address;
    send_buffer[1] = msb;
    send_buffer[2] = lsb;

    mask_pri = save_and_set_interrupt_mask();

    if (max17048_i2c_write_word(i2c_address, send_buffer) == 0) {
        restore_interrupt_mask(mask_pri);
        return true;
    } else {
        restore_interrupt_mask(mask_pri);
        return false;
    }
}

bool max17048_set_register_value(unsigned char i2c_address, unsigned char address, unsigned char mask, unsigned char shift, unsigned char value)
{
    unsigned char send_buffer[3], receive_buffer[2];
    unsigned int mask_pri;

    send_buffer[0] = address & 0xFE;

    mask_pri = save_and_set_interrupt_mask();

    max17048_i2c_read_word(i2c_address, send_buffer, receive_buffer);

    if (address & 0x01) {
        send_buffer[1] = receive_buffer[0];
        send_buffer[2] = (receive_buffer[1] & (~(mask << shift))) | (value << shift); //data value
    } else {
        send_buffer[1] = (receive_buffer[0] & (~(mask << shift))) | (value << shift); //data value
        send_buffer[2] = receive_buffer[1];
    }

    if (max17048_i2c_write_word(i2c_address, send_buffer) == 0) {
        restore_interrupt_mask(mask_pri);
        return true;
    } else {
        restore_interrupt_mask(mask_pri);
        return false;
    }
}

unsigned char max17048_get_register_value(unsigned char i2c_address, unsigned char address, unsigned char mask, unsigned char shift)
{
    unsigned char send_buffer[1], receive_buffer[2];
    unsigned int mask_pri;

    send_buffer[0] = address & 0xFE;

    mask_pri = save_and_set_interrupt_mask();
    max17048_i2c_read_word(i2c_address, send_buffer, receive_buffer);
    restore_interrupt_mask(mask_pri);
    if (address & 0x01) {
        return ((receive_buffer[1] >> shift)&mask);
    } else {
        return ((receive_buffer[0] >> shift)&mask);
    }
}

