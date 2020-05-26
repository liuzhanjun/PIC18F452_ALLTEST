//
// Created by YH31 on 2020/5/22.
//

#ifndef PIC18F452_ALLTEST_USART_H
#define PIC18F452_ALLTEST_USART_H

#include <xc.h>
#include <stdint.h>
#include "configration.h"
#define USART_RX PORTCbits.RC7
#define USART_RX_TRIS TRISCbits.RC7
#define USART_TX PORTCbits.RC6
#define USART_TX_TRIS TRISCbits.RC6

void setBaud(uint24_t baud);
void send_Config();
void receive_Config();
void interrup_config();
void serial_tx(unsigned char val);
void serial_tx_str(const char* val);
unsigned char serial_rx();
#endif //PIC18F452_ALLTEST_USART_H
