//
// Created by YH31 on 2020/5/26.
//

#ifndef PIC18F452_ALLTEST_I2C_H
#define PIC18F452_ALLTEST_I2C_H

#include <xc.h>
#include "delay.h"
#define SCL_PIN PORTCbits.RC3
#define SDA_PIN PORTCbits.RC4

#define SCL_TRIS TRISCbits.TRISC3
#define SDA_TRIS TRISCbits.TRISC4

void i2c_init();
void i2c_start();
void i2c_stop();

unsigned char i2c_readByte(char ack);
unsigned char i2c_sendByte(char data);
#endif //PIC18F452_ALLTEST_I2C_H
