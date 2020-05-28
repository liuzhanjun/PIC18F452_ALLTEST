//
// Created by YH31 on 2020/5/27.
//

#include "eeprom_ext.h"



void write_eeprom(uint16_t addr, unsigned char data) {

    i2c_start();
    //连接设备
    conn_eeprom_w(addr);
    //获取A7-A0
    i2c_sendByte((addr&0x0F)); //发送内存地址
    i2c_sendByte(data); //发送数据
    i2c_stop();
}

unsigned char read_eeprom(uint16_t addr) {

    unsigned char result=0xFF;
    i2c_start();
    conn_eeprom_w(addr);//写入连接
    i2c_sendByte((addr&0x0F)); //发送内存地址

    i2c_start();
    conn_eeprom_r(addr);//读取连接
    result=i2c_readByte(1);
    i2c_stop();
    return result;

}

void conn_eeprom_w(uint16_t addr) {
    //获取A8
    unsigned char addr_h = ((addr >> 8) & 0x01);
    if (addr_h) {
        //发送 包含内存地址最高位的eeprom总线地址
        i2c_sendByte(0xA2);
    } else {
        //如果要写入的内存地址长度小于等于8位，那么久直接发送总线地址
        i2c_sendByte(0xA0);
    }
}

void conn_eeprom_r(uint16_t addr) {
//获取A8
    unsigned char addr_h = ((addr >> 8) & 0x01);
    if (addr_h) {
        //发送 包含内存地址最高位的eeprom总线地址
        i2c_sendByte(0xA3);
    } else {
        //如果要写入的内存地址长度小于等于8位，那么久直接发送总线地址
        i2c_sendByte(0xA1);
    }
}
