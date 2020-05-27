//
// Created by YH31 on 2020/5/27.
//

#ifndef PIC18F452_ALLTEST_EEPROM_2_H
#define PIC18F452_ALLTEST_EEPROM_2_H
#include <xc.h>

unsigned char e2pext_r(unsigned int addr);
void e2pext_w(unsigned int addr, unsigned char val);
#endif //PIC18F452_ALLTEST_EEPROM_2_H
