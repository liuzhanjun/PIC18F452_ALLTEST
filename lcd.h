//
// Created by YH31 on 2020/5/22.
//

#ifndef PIC18F452_ALLTEST_LCD_H
#define PIC18F452_ALLTEST_LCD_H

#include <xc.h>
#include "delay.h"
#define LCD_RS PORTEbits.RE2 //该引脚位数据/指令选择
#define LCD_RS_TRIS TRISE2
//#define LCD_RW 0  //该引脚位读/写选择 ，本例该引脚接地，可以不做处理

#define LCD_E PORTEbits.RE1 //使能位
#define LCD_E_TRIS TRISE1

#define LCD_DATA PORTD //数据传输引脚
#define LCD_DATA_TRIS TRISD
//#define LED_+ 0 //背光电源，本例悬空
//#define LED_- 0 //背光电源，本例悬空

void lcd_CMD(char cmd);
void init_lcd();
void setPostion1(int x);
void setPostion(int x, int y);
void lcdWriteData(char data);
void showLcd_char(char data,int x);
void showLcd(char * a, int x, int y);
void showLcd_1(char *a, int x);
void close_lcd();
void restart_lcd();
#endif //PIC18F452_ALLTEST_LCD_H
