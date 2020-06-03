/*
 * File:   main.c
 * Author: YH31
 *
 * Created on May 18, 2020, 3:26 PM
 */

//使用HS 高速晶体/谐振器   频率为8Mhz
#pragma config OSC = HS       // Oscillator Selection bits (RC oscillator w/ OSC2 configured as RA6)
#pragma config OSCS = OFF       //振荡器切换使能（OFF:使用主振荡器，ON:可在主振荡器和Timer振荡器间切换）

// CONFIG2L
#pragma config PWRT = OFF       // 上电延时定时器使能位
#pragma config BOR = ON         // 欠压复位使能
#pragma config BORV = 20        // 欠压复位电压设置 (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF         //看门狗使能位 (WDT enabled) 关闭了看门狗
#pragma config WDTPS = 128      // 看门狗后分频选择 (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     //CCP2复用位 (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // 堆栈满/或溢出复位使能位 (Stack Full/Underflow will cause RESET)
#pragma config LVP = ON         // 低电压ICSP使能位 (Low Voltage ICSP enabled)

// CONFIG5L                      //代码保护
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H                     
#pragma config CPB = OFF        // 引导地址块代码保护位 (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // 数据EEPROM 代码保护位 Code Protection bit (Data EEPROM not code protected)

// CONFIG6L                     //写保护位
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // 配置寄存器写保护位 (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // 引导块写保护位 (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       //EEPROM写保护位 (Data EEPROM not write protected)

// CONFIG7L                     //地址块读保护位                               
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      //引导块读保护位 (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

#include <xc.h>
#include <stdio.h>
#include "Buzzer.h"
#include "LED_lights.h"
#include "lcd.h"
#include "Usart.h"
#include "KeyBoardScan.h"
#include "spi.h"
#include "i2c.h"
#include "eeprom_ext.h"
#include "mssp_i2c_master.h"
#include "STK3311_x.h"
//蜂鸣器调用

void buzzer_function() {
    buzzer_init();
    buzzer_pwm();
}

//LED灯点亮调用

void light() {

    led2_light_up(0);
    delay_200ms();
    led2_light_up(1);
    delay_200ms();
    led2_light_up(2);
    delay_200ms();
    led2_light_up(3);
    delay_200ms();
    led2_light_up(4);
    delay_200ms();
    led2_light_up(5);
    delay_200ms();
    led2_light_up(6);
    delay_200ms();
    led2_light_up(7);
    delay_200ms();


}

void lcdSHOW() {
    init_lcd();
    char *a = "hello world88888_123456789ABCDEF";
    showLcd_1(a, 0);
    close_lcd();
}

void Usart() {
    init_lcd(); //初始化LCD
    setBaud(9600); //设置波特率
    send_Config(); //发送配置
    receive_Config(); //接收配置
    char *data = "hello world HHBBC";
    serial_tx_str(data); //发送字符串
    char getData = 0;
    int index = 0;
    while (1) {

        if (PIR1bits.RCIF) {//判断是否接收到数据
            getData = serial_rx();
            if (getData != 0) {
                //显示在LCD上
                showLcd_1(&getData, index);
                getData = 0;
                index++;
            }
        }

    }
}

/**
 * 键盘扫描
 * 将该函数放置在main函数的while循环中
 * 在之前需要调用LCD的init_lcd();
 */
void key_board() {
    close_lcd(); //
    unsigned char result = scan_keyBoard_Listener();
    restart_lcd();
    //显示在LCD上
    showLcd_char(result, 0);
    close_lcd(); //
}

void i2c_by_io_eeprom() {
    init_lcd();
    i2c_init();
    write_eeprom(0x1F0, 'N');
    write_eeprom(0x01, 'B');
    unsigned char result = read_eeprom(0x00);
    unsigned char result2 = read_eeprom(0x01F0);
    showLcd_char(result2, 0);
}

void mssp_i2c_eeprom() {
    init_lcd();
    mssp_i2c_init();
    char result = mssp_read_eeprom(0x00);
    ////    char result=mssp_read_eeprom(0x110);
    showLcd_char(result, 0);
}


void __interrupt() tcIntx(void){
    if(SSPIF){
        serial_tx('N');
    }
}

void main(void) {
    setBaud(9600); //设置波特率
    send_Config(); //发送配置
    receive_Config(); //接收配置
//    init_lcd();
//    
    mssp_i2c_init();
    mssp_write_eeprom(0x00,0x88);


   
 
    while (1) {
      
    };
    return;

}


