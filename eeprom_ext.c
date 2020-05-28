//
// Created by YH31 on 2020/5/27.
//

#include "eeprom_ext.h"

void write_eeprom(uint16_t addr, unsigned char data) {

    i2c_start();
    //连接设备
    conn_eeprom_w(addr);
    //获取A7-A0
    i2c_sendByte((addr & 0xFF)); //发送内存地址
    i2c_sendByte(data); //发送数据
    i2c_stop();
}

unsigned char read_eeprom(uint16_t addr) {

    unsigned char result = 0xFF;
    i2c_start();
    conn_eeprom_w(addr); //写入连接
    i2c_sendByte((addr & 0xFF)); //发送内存地址

    i2c_start();
    conn_eeprom_r(addr); //读取连接
    result = i2c_readByte(1);
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

char mssp_write_eeprom(int16_t addr, int8_t data) {
    mssp_i2c_start();
    unsigned char addr_h = ((addr >> 8) & 0x01);
    if (addr_h) {
        mssp_i2c_write(0xA2);
    } else {
        mssp_i2c_write(0xA0);
    }
    mssp_i2c_write((addr & 0x0FF));
    mssp_i2c_write(data);
    mssp_i2c_stop();
}

char mssp_read_eeprom(int16_t addr) {
    char result = 0;
    char ah = (addr & 0x0100) >> 8;


    mssp_i2c_start(); //发送启动信号
    //发送 eeprom总线地址,
    //这部分可以宏观的认为是与挂载器件建立连接，并且是写状态
    //发送 eeprom总线地址，24C04的总线地址是1010ABC+W/R;,  w=0
    //因为当前EEPROM的最大内存地址为0x01FF;
    //也就是说有些地址超过了一个字节，要分两次传输
    //我们把超过的部分这里内存地址最高位就是第9位
    //这里应该是取内存地址的最高位放在了总线地址的C位传输
    // char ah = (addr & 0x0100) >> 8;
    //也就是1010AB(ah)+W/R;,  w=0
    if (ah) {
        mssp_i2c_write(0xA2);
    } else {
        mssp_i2c_write(0xA0);
    }

    //告诉EEPROM要操作的内存地址（要读取该地址的数据）
    mssp_i2c_write(addr & 0xFF); //发送内存地址


    //重新发送启动信号，这里是要变更连接方式
    mssp_i2c_start();
    //    发送 eeprom总线地址，24C04的总线地址是1010xxx+W/R;,  w=1
    if (ah) {
        mssp_i2c_write(0xA3);
    } else {
        mssp_i2c_write(0xA1);
    }
    //读取信息
    result = mssp_i2c_read(1);
    mssp_i2c_stop();
    return result;

}