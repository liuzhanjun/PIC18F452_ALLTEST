/*
 * File:   Buzzer.c
 * Author: YH31
 *
 * Created on May 21, 2020, 3:26 PM
 */

#include "Buzzer.h"

void buzzer_init() {
    BUZZER_OUT_SET = 0;//将引脚设置为输出模式
}

void buzzer_pwm() {
    BUZZER_OUT_PIN = 1;
}
