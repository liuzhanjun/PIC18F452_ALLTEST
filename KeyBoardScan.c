//
// Created by YH31 on 2020/5/25.
//

#include "KeyBoardScan.h"
#include "Usart.h"

unsigned char scan_keyBoard_Listener() {

        char keys  []={'0','1','2','3','4','5','6','7','8','9','*','#'};
        char tips  []={0x0D,0x46,0x45,0x43,0x26,0x25,0x23,0x16,0x15,0x13,0x0E,0x0C};
    //流程 依次将横向引脚的电平拉低，然后读取纵向引脚阵列的值

    //将纵向引脚设置为高电平
    H_KEY_PIN = 0x00;
    H_KEY_TRIS = 0x07; //将B0-B2配置为输入模式,设置为输入模式不会影响到RB2/INT2按钮对该引脚的影响
    H_KEY_PIN = 0x07; //将B0-B2配置为高电平

    //将横向引脚也设置为低电平
    L_KEY_PIN = 0x00;
    L_KEY_TRIS = 0xF0; //注意这里会受到LCD的LCD_E使能位影响，因为他们共用了一部分的PORTD，所以在扫描箭头时应该关闭LCD_E
    L_KEY_PIN = 0xF0; //将D0-D3配置为低电平

    char result = 0x07; //初始值，高<6:3>位为低电平阵列，低三位为高电平阵列
    char is_press = 1; //是否被按下 1，没有，0被按下了
    while (is_press) {
        char h_key_temp = (H_KEY_PIN & 0x07);
        //等待高电平阵列的变化
        if (h_key_temp < 0x07) {
            //说明高电平阵列有变化，有按键被按下了
            before_keyBoard_Shake(); //消除抖动
            //读取高电平阵列的值
            h_key_temp = (H_KEY_PIN & 0x07);
            is_press = 0;
            result = h_key_temp; //将值赋予结果的低位  可以确定按下按钮对应的高电平阵列

            //依次将横向阵列的电平拉高，扫描纵向阵列是否全高电平，
            for (int i = 0; i < 4; ++i) {
                L_KEY_PIN |= (0x01 << i); //输出高电平
                //判断纵向阵列是否全为1
                __delay_us(100); //延迟一定时间，由横向引脚引起的纵向引脚从低电平变到高电平需要一定时间，
                h_key_temp = (H_KEY_PIN & 0x07);
                if (h_key_temp == 0x07) {

                    result |= ((L_KEY_PIN & 0x0F) << 3);

                    L_KEY_PIN &= (0x00 << i); //恢复成低电平

                    //这里返回
                }

                L_KEY_PIN &= (0x00 << i); //恢复成低电平

            }

            //消除后抖动
            after_keyBoard_shake();
            for (int j = 0; j <12 ; ++j) {
                if(tips[j]==result){
                    return keys[j];
                }
            }
        

        }


    }

  

}

/**
 * 前抖动
 */
void before_keyBoard_Shake() {
    //取高电平阵列的16个稳定值
    uint16_t status = 0x0000;
    while (status != 0xFFFF) {
        for (int i = 0; i < 16; ++i) {
            char key = (H_KEY_PIN & 0x07);
            status <<= 1;
            if (key < 0x07) {
                status |= 1;
            }
        }
    }
}


//消除后抖动

void after_keyBoard_shake() {
    uint16_t status = 0x0000;
    while (status != 0xFFFF) {
        for (int i = 0; i < 16; ++i) {
            char key = (H_KEY_PIN & 0x07);
            status <<= 1;
            if (key == 0x07) {
                status |= 1;
            }
        }
    }
}


