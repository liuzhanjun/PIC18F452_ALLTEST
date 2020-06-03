//
// Created by YH31 on 2020/5/29.
//

#ifndef PIC18F452_ALLTEST_STK3311_X_H
#define PIC18F452_ALLTEST_STK3311_X_H

#include <xc.h>
#include "i2c.h"

typedef struct {
    unsigned char STATE;
    unsigned char PSCTRL;
    unsigned char ALSCTRL;
    unsigned char LEDCTRL;
    unsigned char INT;
    unsigned char WAIT;
    unsigned char THDH1_PS;
    unsigned char THDH2_PS;
    unsigned char THDL1_PS;
    unsigned char THDL2_PS;

    unsigned char THDH1_ALS;
    unsigned char THDH2_ALS;
    unsigned char THDL1_ALS;
    unsigned char THDL2_ALS;
    unsigned char;
    unsigned char;
    unsigned char FLAG;
    unsigned char DATA1_PS;
    unsigned char DATA2_PS;
    unsigned char DATA1_ALS;
    unsigned char DATA2_ALS;

    unsigned char DATA1_OFFSET;
    unsigned char DATA2_OFFSET;

    unsigned char DATA1_IR;
    unsigned char DATA2_IR;

} STK_REG;
unsigned char PDT_ID;
#define  PDT_ID_ADDR 0x3E
#define SOFT_RESET_ADDR 0x80
unsigned char SOFT_RESET;

#define  STK_REG_t (( STK_REG *)0x00)

typedef struct {
    unsigned EN_PS:1;
    unsigned EN_ALS:1;
    unsigned EN_WAIT:1;
    unsigned :1;
    unsigned EN_IRO:1;
    unsigned EN_ASO:1;
    unsigned :1;
    unsigned EN_IRS:1;
} STATEbits_t;
extern STATEbits_t *STATES_ADDR = &(STK_REG_t->STATE);

typedef struct {
    unsigned IT_PS:4;
    unsigned GAIN_PS:2;
    unsigned PRS_PS:2;
} PSCTRLBits_t;
extern PSCTRLBits_t *PSCTRL_ADDR = &(STK_REG_t->PSCTRL);

typedef struct {
    unsigned IT_ALS:4;
    unsigned GAIN_ALS:2;
    unsigned PRS_ALS:2;
} ALSCTRLbits_t;
extern ALSCTRLbits_t *ALSCTRL_ADDR = &(STK_REG_t->ALSCTRL);

typedef struct {
    unsigned DT_LED:6;
    unsigned IRDR:2;

} LEDCTRLbits_t;
extern LEDCTRLbits_t *LEDCTRL_ADDR = &(STK_REG_t->LEDCTRL);

typedef struct {
    unsigned INT_PS:3;
    unsigned INT_ALS:1;
    unsigned INT_OUI:1;
    unsigned :1;
    unsigned :1;
    unsigned INT_CTRL:1;
} INTbits_t;
extern INTbits_t *INT_ADDR = &(STK_REG_t->INT);

#define WAIT_ADDR  &(STK_REG_t->WAIT)

typedef struct {
    unsigned FLG_NF:1;
    unsigned FLG_IR_RDY:1;
    unsigned FLG_OUI:1;
    unsigned :1;
    unsigned FLG_PSINT:1;
    unsigned FLG_ALSINT:1;
    unsigned FLG_PSDR:1;
    unsigned FLG_ALSDR:1;
} FLAGbits_t;
extern FLAGbits_t *FLAG_ADDR = &(STK_REG_t->FLAG);

#define DATA1_PS_ADDR  &(STK_REG_t->DATA1_PS)
#define DATA2_PS_ADDR  &(STK_REG_t->DATA2_PS)
#define DATA1_OFFSET_ADDR  &(STK_REG_t->DATA1_OFFSET)
#define DATA2_OFFSET_ADDR  &(STK_REG_t->DATA2_OFFSET)
#define DATA1_IR_ADDR  &(STK_REG_t->DATA1_IR)
#define DATA2_IR_ADDR  &(STK_REG_t->DATA2_IR)

#define  THDH1_PS_ADDR &(STK_REG_t->THDH1_PS)
#define  THDH2_PS_ADDR &(STK_REG_t->THDH2_PS)
#define  THDL1_PS_ADDR &(STK_REG_t->THDL1_PS)
#define  THDL2_PS_ADDR &(STK_REG_t->THDL2_PS)

#define  THDH1_ALS_ADDR &(STK_REG_t->THDH1_ALS)
#define  THDH2_ALS_ADDR &(STK_REG_t->THDH2_ALS)
#define  THDL1_ALS_ADDR &(STK_REG_t->THDL1_ALS)
#define  THDL2_ALS_ADDR &(STK_REG_t->THDL2_ALS)




void stk_write_Cmd(unsigned char regAddr, unsigned char regValue);

unsigned char stk_read_Data(unsigned char regAddr);



void STK_PS_Ready();
void STK_StandBy();
void clean_PSINT();
#endif //PIC18F452_ALLTEST_STK3311_X_H
