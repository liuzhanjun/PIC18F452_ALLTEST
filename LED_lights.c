//
// Created by YH31 on 2020/5/22.
//

#include "LED_lights.h"

void led1_light_up(char number) {
    LED1_LIGHTS_OUT_SET = 0x00;//全部设置为输出
    LED1_LIGHTS_OUT_PIN = 0x00;//默认闭所有的灯
    LED1_LIGHTS_OUT_SET |= (0x01 << number);//将对应的灯的引脚设置为输入模式
    LED1_LIGHTS_OUT_PIN |= (0x01 << number);
}

void led2_light_up(char number) {
    LED2_LIGHTS_OUT_SET = 0x00;//全部设置为输出
    LED2_LIGHTS_OUT_PIN = 0x00;//默认闭所有的灯
    LED2_LIGHTS_OUT_SET |= (0x01 << number);//将对应的灯的引脚设置为输入模式
    LED2_LIGHTS_OUT_PIN |= (0x01 << number);
}



