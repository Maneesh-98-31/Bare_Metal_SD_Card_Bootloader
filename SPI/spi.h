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
uint8_t spi_received(void);

#define fPCLK_2                         0
#define fPCLK_4                         1
#define fPCLK_8                         2
#define fPCLK_16                        3
#define fPCLK_32                        4
#define fPCLK_64                        5
#define fPCLK_128                       6
#define fPCLK_256                       7


#define SPI_CPHA                            (1 << (uint32_t)0U)
#define SPI_CPOL                            (1<<(uint32_t)1U)
#define SPI_MSTR                            (1<<(uint32_t)2U)
#define SPI_BR(val)                         (val<<(uint32_t)3U)
#define SPI_SPE                             (1<<(uint32_t)6U)
#define SPI_LSBFIRST                        (1<<(uint32_t)7U)
#define SPI_SSI                             (1<<(uint32_t)8U)
#define SPI_SSM                            (1<<(uint32_t)9U)
#define SPI_RXONLY                          (1<<(uint32_t)10U)
#define SPI_DFF                             (1<<(uint32_t)11U)
#define SPI_CRCNEXT                         (1<<(uint32_t)12U)
#define SPI_CRCEN                           (1<<(uint32_t)13U)
#define SPI_BIDIOE                          (1<<(uint32_t)14U)
#define SPI_BIDIMODE                        (1<<(uint32_t)15U)


#define SPI_TXEIE                           (1<<7)
#define SPI_RXNEIE                          (1<<6)
#define SPI_ERRIE                           (1<<5)
#define SPI_FRF                             (1<<4)
#define SPI_SSOE                            (1<<2)
#define SPI_TXDMAEN                         (1<<1)
#define SPI_RXDMAEN                         (1<<0)


#define SPI_FRE                             (1<<8)
#define SPI_BSY                             (1<<7)
#define SPI_OVR                             (1<<6)
#define SPI_MODF                            (1<<5)
#define SPI_CRC_ERR                         (1<<4)
#define SPI_UDR                             (1<<3)
#define SPI_CHSIDE                          (1<<2)
#define SPI_TXE                             (1<<1)
#define SPI_RXNE                            (1<<0)


#define SPI__DR                              (1<<0)

#define SPI__CRCPOLY                         (1<<0)

#define SPI__RXCRC                           (1<<0)


#define SPI__TXCRC                           (1<<0)


#endif