//
// Created by YH31 on 2020/5/28.
//


#include "mssp_i2c_master.h"
#include "Usart.h"

void mssp_i2c_init() {
    //选择主模式
    SSPCON1bits.SSPM3 = 1;
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 0;

    //SDL和SCL由硬件控制
//    SCL_TRIS = 1;
//    SDA_TRIS = 1;


    //初始化状态寄存器
//    SSPSTATbits.SMP = 1; //使用标准100Khz到1Mhz之间
     SSPSTAT = 0x80;
    //
    //配置时钟频率Fclock=Fosc/(4*(SSPADD+1))
    //这里我们假设用I2C时钟频率100Khz,单片机时钟频率Fosc=8Mhz

    SSPADD = 0x13;
    //初始化SSPCON2
    SSPCON2 = 0x00;
    //中断使能（下面是开启中断，需要开启的时候开启）
        GIE = 1;
        PEIE = 1;
        SSPIE = 1;
    //清除中断标志
    PIR1bits.SSPIF = 0;
    SSPCON1bits.SSPEN = 1; //SSP使能，将RC3,RC4作为串口引脚
    BCLIF = 0;
}

void mssp_i2c_start() {



    //使能启动条件 产生 I2C 启动信号
    //需要判断MSSP是否处于空闲
    //使用SSPSTAT下的RW和SEN,RSEN,PEN,RCEN或 ACKEN进行或运算的结果表示MSSP是否处于活动模式
    while (SSPSTATbits.R_nW | SSPCON2bits.SEN); //判断MSSP是否处于空闲状态

    SSPCON2bits.SEN = 1; //开始之前SEN置1，表示要发送一个启动条件
    //不知道什么鬼PIC18F452在这里不能发送起始信号
    serial_tx('b');
//    while (SSPCON2bits.SEN == 1); //等待启动完毕，
    while(SSPIF==0);
    serial_tx('a');
    //图中SEN=0，就会产生中断，所以要手动清除中断
    //当启动完毕后SEN=0会发生中断SSPIF=1
    PIR1bits.SSPIF = 0; //软件清零中断位
}

//发送数据,在Start和Stop中间多次调用该函数连续发送多个字节

char mssp_i2c_write(uint8_t data) {
    //从图中看出将发送地址其实就是数据放入SSPBUF中，
    //在BF为0，表示SSPBUF处于空闲状态
    while (SSPSTATbits.BF); //等待BF为0
    SSPBUF = data; //写入完毕后BF=1
   
    while (SSPIF == 0);
    //发生中断，表示数据传输完毕，并读取ACK
    char ack = 1;
    ack = SSPCON2bits.ACKDT;
    //清除中断标记
    SSPIF = 0; //软件清零
    return ack;
}

//停止信号,图中的Stop信号

void mssp_i2c_stop() {
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN == 1); //等待停止为完成
    SSPIF = 0;
}

char mssp_i2c_read(char ack) {

    char result = 0;
    //等到SSP空闲
    while (SSPSTATbits.R_nW | SSPCON2bits.RCEN);
    //使能接收位
    SSPCON2bits.RCEN = 1;
    //等待接收完毕
    while (!BF) {
    };
    result = SSPBUF;
    while (SSPIF) {
        SSPIF = 0;
    }
    //发送ACK
    SSPCON2bits.ACKDT = ack;
    while (SSPIF) {
        SSPIF = 0;
    }

    return result;
}

void close_mssp() {
    SSPCON1bits.SSPEN = 0;
}
