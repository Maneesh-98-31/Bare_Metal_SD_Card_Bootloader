#ifndef _SPI_H_
#define _SPI_H_

#include "stdint.h"

#define SPI1_BASE_ADDRESS               0x40013000



typedef struct {
    volatile uint32_t SPI_CR1;          //0x0
    volatile uint32_t SPI_CR2;          //0x4
    volatile uint32_t SPI_SR;           //0x8
    volatile uint32_t SPI_DR;           //0xC
    volatile uint32_t SPI_CRCPR;        //0X10
    volatile uint32_t SPI_RXCRCR;       //0X14
    volatile uint32_t SPI_TXCRCR;       //0X18
    volatile uint32_t SPI_I2SCFGR;      //0X1C
    volatile uint32_t SPI_I2SPR;        //0X20
}spi_def;



#endif