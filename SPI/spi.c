#include "spi.h"
#include "stdint.h"
#include "rcc.h"
#include "error.h"
#include "tool.h"

#define SPI_LOW_POWER   0

static spi_def *spi_reg;
 
uint32_t spi_init(SPIX spix){
    uint32_t ret = failed(SPI_E);
    switch (spix){
         case SPI_2:
            spi_reg = (spi_def*)SPI2_BASE_ADDRESS;
            peripheral_clock_enable_register(SPI2);
            break;
        case SPI_3:
            spi_reg = (spi_def*)SPI3_BASE_ADDRESS;
            peripheral_clock_enable_register(SPI3);
            break;
        case SPI_1:
            spi_reg = (spi_def*)SPI1_BASE_ADDRESS;
            peripheral_clock_enable_register(SPI1);
            break;
#if SPI_LOW_POWER
        case SPI_4:
            spi_reg = (spi_def*)SPI4_BASE_ADDRESS;
            break;
        case SPI_5:
            spi_reg = (spi_def*)SPI5_BASE_ADDRESS;
            break;
        case SPI_6:
            spi_reg = (spi_def*)SPI6_BASE_ADDRESS;
            break;
#endif
        default:
            ret = failed(SPI_E);
    }
    spi_reg->SPI_CR1 = 0;
    spi_reg->SPI_CR2 = 0;
    /*
      CR1 bits we set:
      - SPI_CR1_MSTR : master mode
      - SPI_CR1_SSM  : software slave management
      - SPI_CR1_SSI  : internal slave select (set when SSM=1 to keep master mode active)
      - SPI_CR1_BR   : baud rate; here choose fPCLK/16 (BR = 0b011 -> (3<<3))
      - CPOL = 0, CPHA = 0 (Mode 0) by default; change if your peripheral needs different mode
      - DFF default 8-bit (DFF bit in CR1 for 16-bit; keep 0)
    */
    spi_reg->SPI_CR1 = (MSTR | SSM | SSI);
    spi_reg->SPI_CR1 |= BR(fPCLK_16);
    spi_reg->SPI_CR1 |= SPE;
    return ret;

}
uint32_t spi_transmit(uint8_t tx){

}
