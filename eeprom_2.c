//
// Created by YH31 on 2020/5/27.
//

#include "eeprom_2.h"
#include "i2c_temp.h"

unsigned char e2pext_r(unsigned int addr) {
    unsigned char ret;
    unsigned char ah;
    unsigned char al;

    ah = (addr & 0x0100) >> 8;
    al = addr & 0x00FF;

    i2c_temp_start();
    if (ah) {
        i2c_temp_wb(0xA2);
    } else {
        i2c_temp_wb(0xA0);
    }
    i2c_temp_wb(al);

    i2c_temp_start();
    if (ah) {
        i2c_temp_wb(0xA3);
    } else {
        i2c_temp_wb(0xA1);
    }
    ret = i2c_rb(1);
    i2c_temp_stop();

    return ret;
}


void e2pext_w(unsigned int addr, unsigned char val) {
    unsigned int tmp;
    unsigned char ah;
    unsigned char al;
    unsigned char nt;

    tmp = val;
    ah = (addr & 0x0100) >> 8;
    al = addr & 0x00FF;
    nt = 0;

    do {
        i2c_temp_start();
        if (ah) {
            i2c_temp_wb(0xA2);
        } else {
            i2c_temp_wb(0xA0);
        }
        i2c_temp_wb(al);
        i2c_temp_wb(tmp);
        i2c_temp_stop();
        i2c_temp_stop();

        nt++;
    } while ((tmp != e2pext_r(addr)) && (nt < 10));
}