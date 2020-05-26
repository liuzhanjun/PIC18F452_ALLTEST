//
// Created by YH31 on 2020/5/26.
//


#include <pic18f452.h>
#include "spi.h"

void spi_Master_init() {
    //将RC3/SCK/SCL  RC4/SDI/SDA  RC5/SDO，配置成串口引脚
    //使能串口，并将SCK,SDO,SDI和SS配置为串口引脚
    SSPCON1bits.SSPEN = 0;
    SSPCON1bits.SSPEN = 1;
    //    主控模式 clock=Fosc/16 =8000000/16=500Khz //SCK作为时钟输出
    SSPCON1bits.SSPM3 = 0;
    SSPCON1bits.SSPM2 = 0; //
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 1; //

    //选择时钟极性(SCK在空闲时时低电平还是高电平)
    //配置SCK空闲时为高电平
    SSPCON1bits.CKP = 1;

    //时钟沿（在时钟沿输出数据）
    //在哪个沿输出数据受到CKP影响
    //在SCK为下降沿的时候SDO发送数据
    SSPSTATbits.CKE = 1;


    //输入数据采样相位
    //在SDO数据输出（数据发送变化后稳定时间）的末尾采样SDI输入数据
    //如果SDO在下降沿发送数据，
    //在中间采样，本质上就是在SCK的下降沿采样数据
    //在末尾采样，本质上就是在SCK的上升沿采样数据
    //如果SDO在上升沿发送数据，
    //在中间采样，本质上就是在SCK的上升沿采样数据
    //在末尾采样，本质上就是在SCK的下降沿采样数据
    SSPSTATbits.SMP = 1;

    //主控模式将SCK,SDO配置为输出
    //从动模式SCK输入，SDO输出
    //如果使用了RA5/SS 应该将RC4设置为输入
    //如果只作为接收器，那么SDO为输入模式
    SPI_SCK_TRIS = 0;
    SPI_SDO_TRIS = 0;

    //所以此处初始化为
    //主控模式，SCK空闲为高电平，在下降沿发送数据，在上升沿采样接收数据

}

//接收数据
///接收数据：SSPSR接收完一个字节后将其写入SSPBUF,同时产生中断SSPIF置1
char spi_recive_bt() {
    char result = 0;
    if (SSPIF || BF) {
        result = SSPBUF;
    }
    return result;
}

void spi_send_bt(char data) {

    if (SSPCON1bits.WCOL) {
        SSPCON1bits.WCOL = 0;
    }

    if (SSPSTATbits.BF) {
        char k = SSPBUF;//在发送数据下一个数据前清空SSPBUF
    }
    SSPBUF = data;
    while (SSPSTATbits.BF);//等待被接收完毕
}

/**
 * 从动模式初始化
 */
void spi_Slave_init() {
    //将RC3/SCK/SCL  RC4/SDI/SDA  RC5/SDO，配置成串口引脚
    //使能串口，并将SCK,SDO,SDI和SS配置为串口引脚
    SSPCON1bits.SSPEN = 0;
    SSPCON1bits.SSPEN = 1;


    //从动模式 SCK作为时钟输入 并使能RA5/SS引脚
    SSPCON1bits.SSPM3 = 0;
    SSPCON1bits.SSPM2 = 1; //
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 0; //

    //选择时钟极性(SCK在空闲时时低电平还是高电平)
    //配置SCK空闲时为高电平
    SSPCON1bits.CKP = 1;


    //时钟沿（在时钟沿输出数据）
    //在哪个沿输出数据受到CKP影响
    //在SCK为下降沿的时候SDO发送数据
    SSPSTATbits.CKE = 1;

    //从动模式下SMP必须清零
    SSPSTATbits.SMP = 0;


    //主控模式将SCK,SDO配置为输出
    //从动模式SCK输入，SDO输出
    //如果使用了RA5/SS 应该将RC4设置为输入
    //如果只作为接收器，那么SDO为输入模式
    SPI_SCK_TRIS = 1;
    SPI_SDO_TRIS = 0;
    SPI_SDI_TRIS = 1;

    //如果使能了RA5/SS那么该引脚应该作为输入模式
    //当SS为低电平的时候使能数据的发送和接收
    //当SS为高电平的时候，即时在数据发送的过程中SDO引脚不会被驱动，将视为悬空
    SPI_SS_TRIS=1;
}
