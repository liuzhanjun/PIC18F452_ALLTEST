//
// Created by YH31 on 2020/5/27.
//

#include "eeprom_ext.h"

void write_eeprom(uint16_t addr, unsigned char data) {

    unsigned char addr_h = ((addr >> 8) & 0x01);//获取十位地址的高2位
    unsigned char addr_l = (addr & 0xFF);


    i2c_start();
    if (addr_h) {
        //发送 包含内存地址最高位的eeprom总线地址
        i2c_sendByte(0xA2);
    } else {
        //如果要写入的内存地址长度小于等于8位，那么久直接发送总线地址
        i2c_sendByte(0xA0);
    }

    i2c_sendByte(addr_l); //发送内存地址
    i2c_sendByte(data); //发送数据
    i2c_stop();
}

unsigned char read_eeprom(uint16_t addr) {
    char result = 0;
    char ah = (addr & 0x0100) >> 8;

    char ack = 0;
    i2c_start();//发送启动信号
    i2c_sendByte(0xA0);

    
}
