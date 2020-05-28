//
// Created by YH31 on 2020/5/28.
//

#ifndef PIC18F452_ALLTEST_MSSP_I2C_MASTER_H
#define PIC18F452_ALLTEST_MSSP_I2C_MASTER_H
#include <xc.h>
#include <stdint.h>
#include "i2c.h"
void mssp_i2c_init();
void mssp_i2c_start();

char mssp_i2c_write(uint8_t data);
void mssp_i2c_stop();
char mssp_i2c_read(char ack);
void close_mssp();
#endif //PIC18F452_ALLTEST_MSSP_I2C_MASTER_H
