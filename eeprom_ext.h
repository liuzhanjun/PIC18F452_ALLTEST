//
// Created by YH31 on 2020/5/27.
//

#ifndef PIC18F452_ALLTEST_EEPROM_EXT_H
#define PIC18F452_ALLTEST_EEPROM_EXT_H

#include <xc.h>
#include "i2c.h"
#include <stdint.h>

unsigned char read_eeprom(uint16_t addr);
void conn_eeprom_w(uint16_t addr);
void conn_eeprom_r(uint16_t addr);
void write_eeprom(uint16_t addr, unsigned char data);
#endif //PIC18F452_ALLTEST_EEPROM_EXT_H
