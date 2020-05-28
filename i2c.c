//
// Created by YH31 on 2020/5/26.
//

#include <pic18f452.h>
#include "i2c.h"

void i2c_init() {
    SDA_TRIS = 0; //数据线为输出
    SCL_TRIS = 0; //时钟线为输出
    SDA_PIN = 1; //空闲时为高电平
    SCL_PIN = 1; //空闲时为高电平
}

void i2c_start() {
    //在时钟线为高电平的时候SDA产生一个下降沿
    SCL_PIN = 1;
    SDA_PIN = 1;
    delay_4Nop();
    SDA_PIN = 0;
    delay_4Nop();
}

void i2c_stop() {
    //在时钟线为高电平的时候SDA产生一个上升沿
    SCL_PIN = 1;
    SDA_PIN = 0;
    delay_4Nop();
    SDA_PIN = 1;
    delay_4Nop();
}

//char i2c_write(char byte){
//    char ack=0;
//    SDA_PIN=0;
//}
//char accI2cAddress(char addr){
//
//    i2c_start();
//    char ack=i2c_write(addr);
//    i2c_stop();
//    return ack;
//}

/**
 * 读取数据
 * @param ack
 */
unsigned char i2c_readByte(char ack) {
    //这里是SCL为下降沿采样SDA
    //数据位从高位到低位依次发送
    unsigned char result = 0x00;//内存内的默认值是FF
    SCL_PIN = 0; //开始为低电平，因为Start之后SCL还处于高电平，必须拉低,为下一次高电平数据有效做准备

    SDA_PIN = 1; //释放SDA
    SDA_TRIS=1;//读取数据应该是输入模式
    
    for (int i = 7; i >= 0; i--) {
        //读取数据是在高电平期间数据有效
        SCL_PIN = 1;
        delay_4Nop();
        result |= (SDA_PIN << i);
        SCL_PIN = 0;
    }
    //释放SDA
    SDA_PIN = 1;
    SDA_TRIS = 0;//向从期间发送ACK，感觉应该是输出模式

    //发送ACK
    SDA_PIN = ack; //在SCL为低电平期间数据变化
    SCL_PIN = 1;
    delay_4Nop();//高电平期间数据有效在此期间会被采样，ACk就被发送出去了
    SCL_PIN = 0;

    //释放SDA数据线(SDA空闲)
    SDA_PIN = 1;
    delay_4Nop();
    return result;
}

unsigned char i2c_sendByte(char data) {
    //将SDA的数据放在高电平
    unsigned char ack = 0;
    SCL_PIN = 0; //在SCL为低电平才能变化

    for (int i = 7; i >= 0; i--) {
        SDA_PIN = ((data >> i)&0x01); //SCL为低电平时变化
        //在SCL为低电平才能变化
        SCL_PIN = 1;
        delay_4Nop(); //高电平期间数据有效在此期间会被采样
        SCL_PIN = 0;
    }



    //    //释放SDA数据线（因为SDA空闲的时候为高电平，所以叫做释放）
    SDA_PIN = 1;
    SDA_TRIS = 1;
    delay_4Nop();
    SCL_PIN = 1;
    ack = SDA_PIN;
    delay_4Nop();
    SCL_PIN = 0;
    //释放SDA数据线(SDA空闲)
    SDA_PIN = 1;
    SDA_TRIS = 0;
    delay_4Nop();
    return ack;

}


