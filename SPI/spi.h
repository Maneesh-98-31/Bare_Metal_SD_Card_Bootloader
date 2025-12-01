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
uint32_t spi_transmit(uint8_t);
uint32_t spi_transmit(uint8_t);

#define fPCLK_2                         0
#define fPCLK_4                         1
#define fPCLK_8                         2
#define fPCLK_16                        3
#define fPCLK_32                        4
#define fPCLK_64                        5
#define fPCLK_128                       6
#define fPCLK_256                       7


#define CPHA                            (1<<0)
#define CPOL                            (1<<1)
#define MSTR                            (1<<2)
#define BR(val)                         (val<<3)
#define SPE                             (1<<6)
#define LSBFIRST                        (1<<7)
#define SSI                             (1<<8)
#define SSM                            (1<<9)
#define RXONLY                          (1<<10)
#define DFF                             (1<<11)
#define CRCNEXT                         (1<<12)
#define CRCEN                           (1<<13)
#define BIDIOE                          (1<<14)
#define BIDIMODE                        (1<<15)


#define TXEIE                           (1<<7)
#define RXNEIE                          (1<<6)
#define ERRIE                           (1<<5)
#define FRF                             (1<<4)
#define SSOE                            (1<<2)
#define TXDMAEN                         (1<<1)
#define RXDMAEN                         (1<<0)


#define FRE                             (1<<8)
#define BSY                             (1<<7)
#define OVR                             (1<<6)
#define MODF                            (1<<5)
#define CRC_ERR                         (1<<4)
#define UDR                             (1<<3)
#define CHSIDE                          (1<<2)
#define TXE                             (1<<1)
#define RXNE                            (1<<0)


#define DR                              (1<<0)

#define CRCPOLY                         (1<<0)

#define RXCRC                           (1<<0)


#define TXCRC                           (1<<0)


#endif