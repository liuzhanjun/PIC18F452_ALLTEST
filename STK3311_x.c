//
// Created by YH31 on 2020/5/29.
//

#include "STK3311_x.h"

void stk_write_Cmd(unsigned char regAddr, unsigned char regValue) {
    //发送起始条件
    i2c_start();
    //发送设备地址0x48+w
    i2c_sendByte(0x90);
    //发送寄存器地址
    i2c_sendByte(regAddr);
    //发送寄存器的值
    i2c_sendByte(regValue);
    //发送结束条件
    i2c_stop();
}

unsigned char stk_read_Data(unsigned char regAddr) {
    unsigned char result=0;
    //发送起始条件
    i2c_start();
    //发送设备地址0x48+w
    i2c_sendByte(0x90);
    //发送寄存器地址
    i2c_sendByte(regAddr);
    //发送结束条件
    i2c_stop();
    //发送起始条件
    i2c_start();
    //发送设备地址0x48+R
    i2c_sendByte(0x91);

    //读取数据
    result=i2c_readByte(1);
    //发送结束条件
    i2c_stop();
    return result;
}

void STK_PS_Ready() {

//    配置状态寄存器
    //将EN_PS=1 开启PS,无等待时间 关闭ALS
    STATES_ADDR->EN_PS=1;
    //启用中断
    STATES_ADDR->EN_IRO=1;
    //DATA_PS<15:0>中的值为ADC采样值减去DATA_OFFSET<15:0>的值
    STATES_ADDR->EN_ASO=1;

    //    配置PS控制寄存器 这里使用默认值，所以不用配置
    //配置LED
    //LED占空比，工作时间
    LEDCTRL_ADDR->DT_LED=0;
    //LED驱动电流 12.5ms
    LEDCTRL_ADDR->IRDR=0;

    //配置中断
    //DATA_PS[15:0] 小于 THDL_PS[15:0]产生中断  接近传感器产生中断
    INT_ADDR->INT_PS=0x06;
    //关闭环境光感应器中断
    INT_ADDR->INT_ALS=0;
//    如果(FLG_ALSINT||FLG_PSINT==1)设置/INT引脚为低电平
    INT_ADDR->INT_CTRL=0;

    //通过I2c将值写入STK3311
    stk_write_Cmd(STATES_ADDR, STK_REG_t->STATE);
    stk_write_Cmd(LEDCTRL_ADDR,STK_REG_t->LEDCTRL);
    stk_write_Cmd(INT_ADDR,STK_REG_t->INT);


//

}

//传感器进入待机模式
void STK_StandBy() {
    STATES_ADDR->EN_PS=0;
    STATES_ADDR->EN_ALS=0;
    STATES_ADDR->EN_WAIT=0;
    stk_write_Cmd(STATES_ADDR,STK_REG_t->STATE);
}

//该函数应该在读取PS数据后调用
// 清除PS中断标记
void clean_PSINT() {

    //本例中不去读取FLAG寄存器 所以FLG_NF=1
    //因为INT_PS=6，所以这个FLG_NF一直为1
    FLAG_ADDR->FLG_NF=1;
    //清除PS中断标记位   清除后 /INT=1
    FLAG_ADDR->FLG_PSINT=0;
    FLAG_ADDR->FLG_ALSINT=0;
    stk_write_Cmd(FLAG_ADDR,STK_REG_t->FLAG);
}



