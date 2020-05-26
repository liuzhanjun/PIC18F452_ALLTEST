//
// Created by YH31 on 2020/5/22.
//

#ifndef PIC18F452_ALLTEST_LED_LIGHTS_H
#define PIC18F452_ALLTEST_LED_LIGHTS_H

#include <pic18f452.h>
#include "xc.h"

#define LED1_LIGHTS_OUT_SET TRISD
#define LED1_LIGHTS_OUT_PIN PORTD

#define LED2_LIGHTS_OUT_SET TRISB
#define LED2_LIGHTS_OUT_PIN PORTB

void led1_light_up(char number);
void led2_light_up(char number);

#endif //PIC18F452_ALLTEST_LED_LIGHTS_H
