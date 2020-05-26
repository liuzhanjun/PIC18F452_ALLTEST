//
// Created by YH31 on 2020/5/22.
//

#include "lcd.h"

//写指令函数
void lcd_CMD(char cmd) {

    //这里延时40us,可替换成忙位检测
    __delay_us(40);
    LCD_RS = 0; //RS指令模式
    //RW=0,因为接地，所以不许要设置了
    LCD_DATA = cmd;
    //LCD_E引脚的一个周期内写入完毕
    LCD_E = 1; //将设置写入
    LCD_E = 0; //写入完毕
}

/**
 * 初始化LCD
 */
void init_lcd() {
    //将RS,E和数据引脚设置为输出模式
    LCD_RS_TRIS = 0;
    LCD_DATA_TRIS = 0;
    LCD_E_TRIS = 0;
    //延迟15ms
    __delay_ms(15);
    //    写指令38//功能设置 8位数据接口，两行显示，5x7点阵
    lcd_CMD(0x38);
    //延迟5ms
    __delay_ms(5);
    //写指令38
    lcd_CMD(0x38);
    //延迟5ms
    __delay_ms(5);
    //写指令38
    lcd_CMD(0x38);
    //写指令0E显示设置
    lcd_CMD(0x0E);
    //写指令06
    lcd_CMD(0x06);
    //写指令01:清屏
    lcd_CMD(0x01);
}

/**
 * 设置写入数据的开始位置
 * 可设置大于屏幕的地址
 * 会换算成屏幕内地址
 *
 * @param x
 */
void setPostion1(int x) {

    if (x > 31) {
        x %= 32;
        //发送清屏命令
        if (x == 0) {
            lcd_CMD(0x01);
            //延时2ms
            __delay_ms(2);
        }
    }
    char postion = x;
    if (x > 15) {
        postion = (0x40 + (x % 16));
    }
    //发送指令设置坐标
    lcd_CMD(postion | 0x80);
}

/**
 * 写单个字符
 * @param data
 */
void lcdWriteData(char data) {
    __delay_us(40);  //这里延时40us,可替换成忙位检测
    LCD_RS = 1;//RS写数据模式
    //RW=0,因为接地，所以不许要设置了
    LCD_DATA = data;
    //LCD_E引脚的一个周期内写入完毕
    LCD_E = 1;
    LCD_E = 0;
}

/**
 * 设置坐标
 * @param x  横坐标 从0开始
 * @param y  第几行 从0开始
 */
void setPostion(int x, int y) {
    char postion = (0x40 * y + x);
    //发送指令设置坐标
    lcd_CMD(postion | 0x80);
}

/**
 * 显示字符串
 * @param a
 * @param x
 * @param y
 */
void showLcd(char *a, int x, int y) {
    //设置DDRAM的坐标
    setPostion(x, y);
    while (*a != '\0') {
        lcdWriteData(*a++);
    }
}

/**
 * 显示字符串
 * 此方法会超过一行会自动换行
 * 超过屏幕容量会清除屏幕显示剩下的字符
 * @param a
 * @param x
 */
void showLcd_1(char *a, int x) {
    setPostion1(x);
    int count = 0;
    while (*a != '\0') {
        if (count == 16) {
            setPostion1(16);
        }
        if (count == 32) {
            setPostion1(32);
        }
        lcdWriteData(*a++);
        count++;
    }
}


void close_lcd() {
    LCD_RS_TRIS = 1;
    LCD_DATA_TRIS = 1;
    LCD_E_TRIS = 1;
}

void restart_lcd(){
     LCD_RS_TRIS = 0;
    LCD_DATA_TRIS = 0;
    LCD_E_TRIS = 0;
    LCD_DATA=0x00;
}

void showLcd_char(char data,int x) {
    setPostion1(x);
    lcdWriteData(data);
}


