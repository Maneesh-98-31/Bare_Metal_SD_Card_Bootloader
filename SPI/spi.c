#include "spi.h"
#include "stdint.h"
#include "rcc.h"
#include "error.h"
#include "tool.h"


static spi_def *spi_reg;

uint32_t spi_init(SPIX spix){
    uint32_t ret = failed(SPI_E);
    switch (spix){
        case SPI_1:
            spi_reg = (spi_def*)SPI1_BASE_ADDRESS;
            break
        case SPI_2:
            spi_reg = (spi_def*)SPI2_BASE_ADDRESS;
            break
        case SPI_3:
            spi_reg = (spi_def*)SPI3_BASE_ADDRESS;
            break
        case SPI_4:
            spi_reg = (spi_def*)SPI4_BASE_ADDRESS;
            break
        case SPI_5:
            spi_reg = (spi_def*)SPI5_BASE_ADDRESS;
            break
        case SPI_6:
            spi_reg = (spi_def*)SPI6_BASE_ADDRESS;
            break
        default:
            ret = failed(SPI_E);
    }

}

