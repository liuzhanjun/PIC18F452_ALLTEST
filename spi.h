//
// Created by YH31 on 2020/5/26.
//

#ifndef PIC18F452_ALLTEST_SPI_H
#define PIC18F452_ALLTEST_SPI_H
#include <xc.h>
#define SPI_SCK_TRIS TRISCbits.RC3
#define SPI_SDO_TRIS TRISCbits.RC5
#define SPI_SDI_TRIS TRISCbits.RC4
#define SPI_SS_TRIS TRISAbits.RA5

#define SPI_SCK_PIN PORTCbits.RC3
#define SPI_SDO_PIN PORTCbits.RC5
#define SPI_SDI_PIN PORTCbits.RC4
#define SPI_SS_PIN PORTAbits.SS

void spi_Master_init();
void spi_Slave_init();
char spi_recive_bt();
void spi_send_bt(char data);
#endif //PIC18F452_ALLTEST_SPI_H
