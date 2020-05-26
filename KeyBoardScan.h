//
// Created by YH31 on 2020/5/25.
//

#ifndef PIC18F452_ALLTEST_KEYBOARDSCAN_H
#define PIC18F452_ALLTEST_KEYBOARDSCAN_H

#include <xc.h>
#include <stdint.h>
#include "configration.h"
#define H_KEY_PIN PORTB  //纵向引脚
#define H_KEY_TRIS TRISB //此/纵向引脚阵列的数据方向（控制输出还是输入）

#define L_KEY_PIN PORTD  //横向引脚
#define L_KEY_TRIS TRISD //此为横向引脚阵列的数据方向（控制输出还是输入）
unsigned char scan_keyBoard_Listener();

void before_keyBoard_Shake();
void after_keyBoard_shake();
#endif //PIC18F452_ALLTEST_KEYBOARDSCAN_H
