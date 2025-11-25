#ifndef _SPI_H_
#define _SPI_H_

#include "stdint.h"
#include "rcc.h"

typedef enum{
    SPI_1,
    SPI_2,
    SPI_3,
    SPI_4,
    SPI_5,
    SPI_6
} SPIX;

#define SPI1_BASE_ADDRESS               0x40013000
#define SPI2_BASE_ADDRESS               0x40003800
#define SPI3_BASE_ADDRESS               0x40003c00
#define SPI4_BASE_ADDRESS               0x40013800
#define SPI5_BASE_ADDRESS               0x40015000
#define SPI6_BASE_ADDRESS               0x40015400


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

uint32_t spi_init(SPIX);

#endif