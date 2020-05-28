//
// Created by YH31 on 2020/5/22.
//

#include "delay.h"

//延迟多少秒，
//这里Fosc是晶振频率，单位是Mhz
//计算公式
//Tosc=(1/Fosc)*4  //单位u秒
//1s=1000000us
//1秒钟需要多少个NOP count=1000000/Tosc
//实际时间会有误差
//并且值太大可能会导致溢出
void delay_200ms() {
    //下面大概是延迟200ms HS模式下 8Mhz
//    for(int i=0;i<116;i++){
//        for(int j=0;j<200;j++){
//           
//            NOP();
//        }
//    }

    __delay_ms(200);


}

void delay_4Nop() {
    NOP();
    NOP();
    NOP();
    NOP();

}




